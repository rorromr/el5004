/**
 * @brief Dynamixel Servo
 * @author Rodrigo Muñoz
 * @date 2016
 *
 * @TODO
 *
 */

#ifndef DXL_SERVO_H
#define DXL_SERVO_H

#include <DynamixelSerial1.h>
#include <stdint.h>

namespace GoKart
{
  class DxlServo
  {
    public:
  
      DxlServo(DynamixelClass& dxl, const uint8_t id);
  
      void config(const uint16_t min, const uint16_t max, const uint16_t zero);

      void move(const int16_t target);
  
    private:
      // Dynamixel lib
      DynamixelClass* dxl_;

      // Motor id
      uint8_t id_;
      // Min position
      uint16_t min_;
      // Max position
      uint16_t max_;
      // Zero position
      uint16_t zero_;
  };
}

#endif
