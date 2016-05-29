/**
 * @brief Throttle
 * @author Rodrigo Muñoz
 * @date 2016
 *
 * @TODO
 *
 */

#ifndef GOKART_THROTTLE_H
#define GOKART_THROTTLE_H

#include "dxl_servo.h"

namespace GoKart
{
  class Throttle: public DxlServo
  {
    public:
      Throttle(DynamixelClass& dxl, const uint8_t id);
      
      void full();

      void release();

  };
}

#endif
