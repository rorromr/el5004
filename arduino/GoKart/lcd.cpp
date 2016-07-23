#include "lcd.h"
#include "Arduino.h"

namespace GoKart
{
  // Keypad
  Keypad::Keypad(uint8_t buttonPin):
    pin_(buttonPin)
  {
    current_.value = BTN_NONE;
    rising_.value = 0U;
    falling_.value = 0U;
  }

  void Keypad::update()
  {
    ButtonStateUnion last = current_;
    current_.value = getPressedButton();
    rising_.value = (~last.value) & current_.value;
    falling_.value = last.value & (~current_.value);
  }

  ButtonState Keypad::getPressedButton()
  {
    // Read the value from the sensor
    uint16_t adc_val = analogRead(pin_);

    if (adc_val > 1000U) return BTN_NONE;
    if (adc_val < 50U)   return BTN_RIGHT;  
    if (adc_val < 250U)  return BTN_UP; 
    if (adc_val < 450U)  return BTN_DOWN; 
    if (adc_val < 650U)  return BTN_LEFT; 
    else return BTN_SELECT; //(adc_val < 850U)
  }

  LCD::LCD():
    lcd_(GOKART_LCD_RS, GOKART_LCD_EN, GOKART_LCD_DB4, GOKART_LCD_DB5, GOKART_LCD_DB6, GOKART_LCD_DB7),
    servoCount_(0U),
    servoSelected_(0U),
    potPos_(0U),
    potCW_(0U),
    potCCW_(0U),
    menuSelected_(0U),
    keypad(GOKART_LCD_BUTTON_PIN)
  {
  }

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

  void LCD::printTest(void *data)
  {
    ButtonState btn = keypad.getPressedButton();
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

    // Test rising
    keypad.update();
    if (keypad.rising(BTN_UP)) Serial.println("rising UP");
    if (keypad.rising(BTN_DOWN)) Serial.println("rising DOWN");
    if (keypad.rising(BTN_LEFT)) Serial.println("rising LEFT");
    if (keypad.rising(BTN_RIGHT)) Serial.println("rising RIGHT");
    if (keypad.rising(BTN_SELECT)) Serial.println("rising SELECT");

    // Test raising
    if (keypad.falling(BTN_UP)) Serial.println("falling UP");
    if (keypad.falling(BTN_DOWN)) Serial.println("falling DOWN");
    if (keypad.falling(BTN_LEFT)) Serial.println("falling LEFT");
    if (keypad.falling(BTN_RIGHT)) Serial.println("falling RIGHT");
    if (keypad.falling(BTN_SELECT)) Serial.println("falling SELECT");
  }

  void LCD::printMotorInfo(void *data)
  {
    if (servoCount_ == 0U) return;

    // Read button and assign selected servo
    ButtonStateUnion keys = keypad.getRising();
    switch(keys.value)
    {
      case BTN_RIGHT:
        servoSelected_ = (servoSelected_+1U) > (servoCount_-1U) ? 0U : (servoSelected_+1U);
        break;
      case BTN_LEFT:
        servoSelected_ = servoSelected_ > 0U ? (servoSelected_-1U) : (servoCount_-1U);
        break;
    }

    ServoInfo* servo = &servoInfo_[servoSelected_];
    // Update values
    servo->pos = servo->servo->getPosition();
    servo->load = servo->servo->getLoad();
    servo->cwLimit = servo->servo->getCWLimit();
    servo->ccwLimit = servo->servo->getCCWLimit();
    
    // First row: Name and position
    lcd_.setCursor(0, 0);
    lcd_.print(servo->name);
    lcd_.setCursor(5, 0);
    lcd_.print("Pos:");
    lcd_.setCursor(9, 0);
    lcd_.print("    ");
    lcd_.setCursor(9, 0);
    lcd_.print(servo->pos);
    // Second row: Load
    lcd_.setCursor(0, 1);
    lcd_.print("L:");
    lcd_.setCursor(3, 1);
    lcd_.print("    ");
    lcd_.setCursor(3, 1);
    lcd_.print(servo->load);
    /*
    // Second row: CW and CCW limit
    lcd_.setCursor(0, 1);
    lcd_.print("CW:");
    lcd_.setCursor(3, 1);
    lcd_.print(servo->cwLimit);
    lcd_.setCursor(8, 1);
    lcd_.print("CCW:");
    lcd_.setCursor(11, 1);
    lcd_.print(servo->ccwLimit);
    */
  }

  void LCD::printCommand(void *data)
  {
    DataSerialization::GoKartCommand* cmd = (DataSerialization::GoKartCommand*) data;
    // First row: steering wheel and emergency
    lcd_.setCursor(0, 0);
    lcd_.print("SW: ");
    lcd_.setCursor(4, 0);
    lcd_.print("    ");
    lcd_.setCursor(4, 0);
    lcd_.print(cmd->stwheel.data);

    lcd_.setCursor(9, 0);
    lcd_.print("E: ");
    lcd_.setCursor(12, 0);
    lcd_.print("    ");
    lcd_.setCursor(12, 0);
    lcd_.print(cmd->emergency.data);

    // Second row: brake and throttle
    lcd_.setCursor(0, 1);
    lcd_.print("BK: ");
    lcd_.setCursor(4, 1);
    lcd_.print("    ");
    lcd_.setCursor(4, 1);
    lcd_.print(cmd->brake.data);
    
    lcd_.setCursor(8, 1);
    lcd_.print("TH:");
    lcd_.setCursor(12, 1);
    lcd_.print("    ");
    lcd_.setCursor(12, 1);
    lcd_.print(cmd->throttle.data); 
  }

  void LCD::printMotorConfig(void *data)
  {
    if (servoCount_ == 0U) return;

    // Read button and assign selected servo
    ButtonStateUnion keys = keypad.getRising();
    
    switch(keys.value)
    {
      case BTN_RIGHT:
        servoSelected_ = (servoSelected_+1U) > (servoCount_-1U) ? 0U : (servoSelected_+1U);
        break;
      case BTN_LEFT:
        servoSelected_ = servoSelected_ > 0U ? (servoSelected_-1U) : (servoCount_-1U);
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
    lcd_.print("    ");
    lcd_.setCursor(9, 0);
    lcd_.print(pos);
    // Second row: CW and CCW limit
    lcd_.setCursor(0, 1);
    lcd_.print("CW:");
    lcd_.setCursor(3, 1);
    lcd_.print("    ");
    lcd_.setCursor(3, 1);
    lcd_.print(cw);
    lcd_.setCursor(8, 1);
    lcd_.print("CCW:");
    lcd_.setCursor(12, 1);
    lcd_.print("    ");
    lcd_.setCursor(12, 1);
    lcd_.print(ccw);

    if (keys.button.BIT_SELECT)
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
      lcd_.clear();
    }
  }

  void LCD::printMenu(void *data)
  {
    static uint32_t last_call = 0UL;
    if (millis()-last_call<100) return;
    last_call = millis();
    
    if (millis()-last_call<2000) lcd_.clear();

    if (servoCount_ == 0U) return;

    keypad.update();
    ButtonStateUnion keys = keypad.getRising();
    switch (keys.value)
    {
      case BTN_UP:
        menuSelected_ = (menuSelected_+1U) > 2U ? 0U : (menuSelected_+1U);
        lcd_.clear();
        break;
      case BTN_DOWN:
        menuSelected_ = menuSelected_ > 0 ? (menuSelected_-1U) : 2U;
        lcd_.clear();
        break;
    }

    switch(menuSelected_)
    {
      case 0:
        printCommand(data);
        break;
      case 1:
        printMotorInfo(data);
        break;
      case 2:
        printMotorConfig(data);
        break;
    }
  }

  void LCD::clear()
  {
    lcd_.clear();
  }

  void LCD::print(const char* message)
  {
    lcd_.print(message);
  }

  void LCD::setCursor(uint8_t col, uint8_t row)
  {
    lcd_.setCursor(col, row);
  }

}

