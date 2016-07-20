/**
 * @brief LCD
 * @author Rodrigo Muñoz
 * @date 2016
 *
 * @TODO
 *
 */

#ifndef GOKART_LCD_H
#define GOKART_LCD_H

#include "LiquidCrystal.h"
#include "dxl_servo.h"
#include "gokart_msgs.h"

#define GOKART_LCD_BUTTON_PIN A15

#define GOKART_LCD_DB4 30  // 4 Shield
#define GOKART_LCD_DB5 31  // 5 Shield
#define GOKART_LCD_DB6 32  // 6 Shield
#define GOKART_LCD_DB7 33  // 7 Shield
#define GOKART_LCD_RS 34   // 8 Shield
#define GOKART_LCD_EN 35   // 9 Shield
#define GOKART_LCD_BLC 36  // 10 Shield

#define GOKART_LCD_COLS 16
#define GOKART_LCD_ROWS 2

#define GOKART_POT1_PIN A0
#define GOKART_POT2_PIN A1
#define GOKART_POT3_PIN A2

#define GO_KART_LCD_MAX_SERVO 3

namespace GoKart
{

  typedef struct ServoInfo_
  {
    DxlServo *servo;
    char name[4];
    int16_t pos;
    int16_t load;
    int16_t cwLimit;
    int16_t ccwLimit;
  } ServoInfo;

  typedef enum
  {
    BTN_NONE   = 1U << 0U,
    BTN_UP     = 1U << 1U,
    BTN_LEFT   = 1U << 2U,
    BTN_RIGHT  = 1U << 3U,
    BTN_DOWN   = 1U << 4U,
    BTN_SELECT = 1U << 5U
  } ButtonState;

  typedef struct ButtonBit_
  {
    uint8_t BIT_NONE  : 1;
    uint8_t BIT_UP    : 1;
    uint8_t BIT_LEFT  : 1;
    uint8_t BIT_RIGHT : 1;
    uint8_t BIT_DOWN  : 1;
    uint8_t BIT_SELECT: 1;
    uint8_t BIT_B6 : 1;
    uint8_t BIT_B7 : 1;
  } ButtonBit;

  typedef union ButtonStateUnion_
  {
  	uint8_t value;
    ButtonBit button;
  } ButtonStateUnion;
    
  class Keypad
  {
    public:
      Keypad(uint8_t buttonPin);

      void update();

      ButtonState getPressedButton();

      inline ButtonStateUnion getPressed()
      {
        return current_;
      }

      inline ButtonStateUnion getRising()
      {
        return rising_;
      }

      inline ButtonStateUnion getFalling()
      {
        return falling_;
      }

      inline bool pressed(const ButtonState btn)
      {
        return rising_.value == btn;
      }

      inline bool rising(const ButtonState btn)
      {
        return rising_.value == btn;
      }

      inline bool falling(const ButtonState btn)
      {
        return falling_.value == btn;
      }
    
    private:
      uint8_t pin_;
      ButtonStateUnion current_;
      ButtonStateUnion rising_;
      ButtonStateUnion falling_;
  };

  class LCD
  {
    public:
      LCD();

      bool init();

      ButtonState getButton();

      void updatePot();

      bool addServo(DxlServo *s, const char *name);

      void printMenu(void *data);

      void printCommand(void *data);

      void printMotorInfo(void *data);

      void printMotorConfig(void *data);

      void printTest(void *data);

      void clear();

      typedef void (*printMenuFcn)(void *data);

    private:
      LiquidCrystal lcd_;
      uint8_t servoCount_;
      uint8_t servoSelected_;
      ServoInfo servoInfo_[GO_KART_LCD_MAX_SERVO];
      // Keypad
      Keypad keypad;
      // Potenciometer value
      uint16_t potPos_;
      uint16_t potCW_;
      uint16_t potCCW_;
      uint8_t menuSelected_;
  };

  class LCDMenu
  {
    public:
      LCDMenu(LiquidCrystal &lcd):
        lcd_(&lcd)
      {
      }

      virtual void printStatic() = 0;

      virtual void print() = 0;

    private:
      LiquidCrystal *lcd_;
  };

}

#endif
