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
    int16_t cwLimit;
    int16_t ccwLimit;
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

      void updatePot();

      bool addServo(DxlServo *s, const char *name);

      void printConfig(void *data);

      void printCommand(void *data);

      void printConfigMotor(void *data);

      void clear();

      void test();

    private:
      LiquidCrystal lcd_;
      uint8_t servoCount_;
      uint8_t servoSelected_;
      ServoInfo servoInfo_[GO_KART_LCD_MAX_SERVO];
      // Potenciometer value
      uint16_t potPos_;
      uint16_t potCW_;
      uint16_t potCCW_;

  };
}

#endif