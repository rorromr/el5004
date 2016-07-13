#include "lcd.h"
#include "Arduino.h"

namespace GoKart
{
  LCD::LCD():
    lcd_(GOKART_LCD_RS, GOKART_LCD_EN, GOKART_LCD_DB4, GOKART_LCD_DB5, GOKART_LCD_DB6, GOKART_LCD_DB7),
    servoCount_(0U),
    servoSelected_(0U),
    potPos_(0U),
    potCW_(0U),
    potCCW_(0U)
  {}

  bool LCD::init()
  {
    lcd_.begin(GOKART_LCD_COLS, GOKART_LCD_ROWS);
    return true;
  }

  void LCD::updatePot()
  {
    potPos_ = analogRead(A0);
    potCW_ = analogRead(A1);
    potCCW_ = analogRead(A2);
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

  void LCD::test()
  {
    ButtonState btn = getButton();
    updatePot();
    char btn_name[7] = "NONE  ";
    switch(btn)
    {
    case BTN_NONE:
      strcpy(btn_name, "NONE  ");
      break;
    case BTN_UP:
      strcpy(btn_name, "UP    ");
      break;     
    case BTN_LEFT:
      strcpy(btn_name, "LEFT  ");
      break;   
    case BTN_RIGHT:
      strcpy(btn_name, "RIGHT ");
      break;  
    case BTN_DOWN:
      strcpy(btn_name, "DOWN  ");
      break;   
    case BTN_SELECT:
      strcpy(btn_name, "SELECT");
      break;
    }
    // Print pot values
    // @TODO Check print
    lcd_.setCursor(0,0);
    lcd_.print(potPos_);
    lcd_.setCursor(5,0);
    lcd_.print(potCW_);
    lcd_.setCursor(11,0);
    lcd_.print(potCCW_);

    lcd_.setCursor(0,1);      // Move to the begining of the second row
    lcd_.print(btn_name);
    lcd_.setCursor(8,1);      // Move cursor to second line "1" and 9 spaces over
    lcd_.print(millis()/1000);// Display seconds elapsed since power-up
  }

  void LCD::printConfig(void *data)
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
    servo->cwLimit = servo->servo->getCWLimit();
    servo->ccwLimit = servo->servo->getCCWLimit();
    
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

  void LCD::printCommand(void *data)
  {
    DataSerialization::GoKartCommand* cmd = (DataSerialization::GoKartCommand*) data;
    // First row: steering wheel and emergency
    lcd_.setCursor(0, 0);
    lcd_.print("SW: ");
    lcd_.print(cmd->stwheel.data);
    lcd_.setCursor(8, 0);
    lcd_.print("E: ");
    lcd_.print(cmd->emergency.data);

    // Second row: brake and throttle
    lcd_.setCursor(0, 1);
    lcd_.print("BK: ");
    lcd_.print(cmd->brake.data);
    lcd_.setCursor(8, 1);
    lcd_.print("TH:");
    lcd_.print(cmd->throttle.data); 
  }

  void LCD::printConfigMotor(void *data)
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
    servo->cwLimit = servo->servo->getCWLimit();
    servo->ccwLimit = servo->servo->getCCWLimit();

    // Update potenciometer value
    updatePot();
    
    // Map values
    uint16_t pos = 4*potPos_;
    uint16_t cw = 4*potCW_;
    uint16_t ccw = 4*potCCW_;

    // First row: Name and position
    lcd_.setCursor(0, 0);
    lcd_.print(servo->name);
    lcd_.setCursor(5, 0);
    lcd_.print("Pos:");
    lcd_.setCursor(9, 0);
    lcd_.print(pos);
    // Second row: CW and CCW limit
    lcd_.setCursor(0, 1);
    lcd_.print("CW:");
    lcd_.setCursor(3, 1);
    lcd_.print(cw);
    lcd_.setCursor(8, 1);
    lcd_.print("CCW:");
    lcd_.setCursor(11, 1);
    lcd_.print(ccw);

    btn = getButton();
    if (btn == BTN_SELECT)
    {
      uint16_t result;
      lcd_.clear();
      lcd_.setCursor(0, 0);
      lcd_.print("Save config");
      servo->servo->move(pos);
      result = servo->servo->setCWLimit(cw);
      result += servo->servo->setCCWLimit(ccw);
      delay(500);
      lcd_.clear();
      lcd_.setCursor(0, 0);
      if (result) lcd_.print("Fail!");
      else lcd_.print("Done!");
      delay(500);
    }
  }

  void LCD::clear()
  {
    lcd_.clear();
  }

}

