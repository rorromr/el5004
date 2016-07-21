/**
 * @brief Steering Wheel
 * @author Rodrigo Muñoz
 * @date 2016
 *
 * @TODO
 *
 */

#ifndef GOKART_STEERINGWHEEL_H
#define GOKART_STEERINGWHEEL_H

#include "dxl_servo.h"

#define GOKART_SW_CW_ENCODER (900)
#define GOKART_SW_CCW_ENCODER (3200)
#define GOKART_SW_CENTER_ENCODER (2048)
#define GOKART_SW_DEFAULT_SPEED (180)
#define GOKART_SW_COMMAND_FACTOR (1.0f/128.0f)
#define GOKART_SW_POS_MAP_FACTOR ((GOKART_SW_CENTER_ENCODER-GOKART_SW_CW_ENCODER)*GOKART_SW_COMMAND_FACTOR)
#define GOKART_SW_NEG_MAP_FACTOR ((GOKART_SW_CCW_ENCODER-GOKART_SW_CENTER_ENCODER)*GOKART_SW_COMMAND_FACTOR)

namespace GoKart
{
  class SteeringWheel: public DxlServo
  {
    public:
      SteeringWheel(DynamixelClass& dxl, const uint8_t id);

      bool init();
      
      void move(const int8_t pos_target);

      void center();

      void setSpeed(const uint16_t speed);

    private:
      uint16_t speed_;

  };
}

#endif
