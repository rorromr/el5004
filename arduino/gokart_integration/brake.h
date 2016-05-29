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

namespace GoKart
{
  class Brake: public DxlServo
  {
    public:
      Brake(DynamixelClass& dxl, const uint8_t id);
      
      void full();

      void release();

  };
}

#endif
