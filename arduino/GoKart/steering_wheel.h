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

#define GOKART_STEERINGWHEEL_CW_ENCODER (100)
#define GOKART_STEERINGWHEEL_CCW_ENCODER (3995)
#define GOKART_STEERINGWHEEL_CENTER_ENCODER (2048)
#define GOKART_STEERINGWHEEL_DEFAULT_SPEED (256)
#define COMMAND_FACTOR (1.0f/128.0f)
#define POSITIVE_MAP_FACTOR ((GOKART_STEERINGWHEEL_CENTER_ENCODER-GOKART_STEERINGWHEEL_CW_ENCODER)*COMMAND_FACTOR)
#define NEGATIVE_MAP_FACTOR ((GOKART_STEERINGWHEEL_CCW_ENCODER-GOKART_STEERINGWHEEL_CENTER_ENCODER)*COMMAND_FACTOR)

namespace GoKart
{
  class SteeringWheel: public DxlServo
  {
    public:
      SteeringWheel(DynamixelClass& dxl, const uint8_t id);
      
      void move(const int8_t pos_target);

      void center();

      void setSpeed(const uint16_t speed);

    private:
      uint16_t speed_;

  };
}

#endif
