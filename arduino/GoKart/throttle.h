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

#define GOKART_THROTTLE_CW_ENCODER (100U)
#define GOKART_THROTTLE_CCW_ENCODER (3995U)
#define GOKART_THROTTLE_CENTER_ENCODER (3995U)
#define GOKART_THROTTLE_DEFAULT_SPEED (400U)
#define GOKART_THROTTLE_COMMAND_FACTOR (1.0f/255.0f)

namespace GoKart
{
  class Throttle: public DxlServo
  {
    public:
      Throttle(DynamixelClass& dxl, const uint8_t id);

      bool init();

      void move(const uint8_t pos_target);
      
      void full();

      void release();

  };
}

#endif
