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

#define GOKART_LCD_BUTTON_PIN A15

#define GOKART_LCD_D4 30
#define GOKART_LCD_D5 31
#define GOKART_LCD_D6 32
#define GOKART_LCD_D7 33
#define GOKART_LCD_RS 34
#define GOKART_LCD_EN 35
#define GOKART_LCD_BLC 36

#define GOKART_LCD_COLS 16
#define GOKART_LCD_ROWS 2

#define GO_KART_LCD_MAX_SERVO 3

namespace GoKart
{

  typedef struct ServoInfo_
  {
    DxlServo *servo;
    char name[4];
    uint16_t pos;
    uint16_t cwLimit;
    uint16_t ccwLimit;
  } ServoInfo;

  typedef enum
  {
    BTN_NONE   = 0U,
    BTN_UP     = 1U,
    BTN_LEFT   = 2U,
    BTN_RIGHT  = 3U,
    BTN_DOWN   = 4U,
    BTN_SELECT = 5U
  } ButtonState;

  class LCD
  {
    public:
      LCD();

      bool init();

      ButtonState getButton();

      bool addServo(DxlServo *s, const char *name);

      void print();

      void printButton();

    private:
      LiquidCrystal lcd_;
      uint8_t servoCount_;
      uint8_t servoSelected_;
      ServoInfo servoInfo_[GO_KART_LCD_MAX_SERVO];

  };
}

#endif
