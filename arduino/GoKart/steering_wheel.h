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

namespace GoKart
{
  class SteeringWheel: public DxlServo
  {
    public:
      SteeringWheel(DynamixelClass& dxl, const uint8_t id);
      
      void center();

  };
}

#endif
