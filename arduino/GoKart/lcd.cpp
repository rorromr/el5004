#include "lcd.h"
#include "Arduino.h"

namespace GoKart
{
  LCD::LCD():
    lcd_(GOKART_LCD_RS, GOKART_LCD_EN, GOKART_LCD_D4, GOKART_LCD_D5, GOKART_LCD_D6, GOKART_LCD_D7),
    servoCount_(0U),
    servoSelected_(0U)
  {}

  bool LCD::init()
  {
    lcd_.begin(GOKART_LCD_COLS, GOKART_LCD_ROWS);
    return true;
  }

  ButtonState LCD::getButton()
  {
    // Read the value from the sensor
    uint16_t adc_val = analogRead(GOKART_LCD_BUTTON_PIN);

    if (adc_val > 1000U) return BTN_NONE;
    if (adc_val < 50U)   return BTN_RIGHT;  
    if (adc_val < 250U)  return BTN_UP; 
    if (adc_val < 450U)  return BTN_DOWN; 
    if (adc_val < 650U)  return BTN_LEFT; 
    else return BTN_SELECT; //(adc_val < 850U)
  }

  bool LCD::addServo(DxlServo *s, const char *name)
  {
    if (strlen(name)>4) return false;
    if (s == NULL) return false;
    ServoInfo* servo = &servoInfo_[servoCount_++];
    
    servo->servo = s; // Set servo ptr
    strcpy(servo->name, name); // Set name
    servo->pos = 0U;
    servo->cwLimit = 0U;
    servo->ccwLimit = 0U;
  }

  void LCD::printButton()
  {
    ButtonState btn = getButton();
    String btn_name = "NONE";
    switch(btn)
    {
    case BTN_NONE:
      btn_name = "NONE";
      break;
    case BTN_UP:
      btn_name = "UP";
      break;     
    case BTN_LEFT:
      btn_name = "LEFT";
      break;   
    case BTN_RIGHT:
      btn_name = "RIGHT";
      break;  
    case BTN_DOWN:
      btn_name = "DOWN";
      break;   
    case BTN_SELECT:
      btn_name = "SELECT";
      break;
    }
    Serial.println(btn_name);
  }

  void LCD::print()
  {
    if (servoCount_ == 0U) return;

    ButtonState btn = getButton();

    switch(btn)
    {
      case BTN_LEFT:
        servoSelected_ = (servoSelected_+1U) > (servoCount_-1U) ? servoSelected_ : (servoSelected_+1U);
        break;
      case BTN_RIGHT:
        servoSelected_ = servoSelected_ > 0 ? (servoSelected_-1U) : 0U;
        break;
    }

    ServoInfo* servo = &servoInfo_[servoSelected_];
    // Update values
    servo->pos = servo->servo->getPosition();
    servo->cwLimit = servo->servo->getPosition();// @TODO
    servo->ccwLimit = servo->servo->getPosition();// @TODO
    
    // First row: Name and position
    lcd_.setCursor(0, 0);
    lcd_.print(servo->name);
    lcd_.setCursor(5, 0);
    lcd_.print("Pos:");
    lcd_.setCursor(9, 0);
    lcd_.print(servo->pos);
    // Second row: CW and CCW limit
    lcd_.setCursor(0, 1);
    lcd_.print("CW:");
    lcd_.setCursor(3, 1);
    lcd_.print(servo->cwLimit);
    lcd_.setCursor(8, 1);
    lcd_.print("CCW:");
    lcd_.setCursor(11, 1);
    lcd_.print(servo->ccwLimit);
    

  }

}

