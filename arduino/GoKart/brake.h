/**
 * @brief Brake
 * @author Rodrigo Muñoz
 * @date 2016
 *
 * @TODO
 *
 */

#ifndef GOKART_BRAKE_H
#define GOKART_BRAKE_H

#include "dxl_servo.h"

#define BRAKE_COMMAND_FACTOR (1.0f/255.0f)

namespace GoKart
{
  class Brake: public DxlServo
  {
    public:
      Brake(DynamixelClass& dxl, const uint8_t id);

      void move(const uint8_t pos_target);
      
      void full();

      void release();

  };
}

#endif
