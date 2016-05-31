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
#include "error_code.h"

namespace GoKart
{
  /// Dynamixel servo error definition
  typedef enum {
    ///< No error
    DXL_SERVO_OK            = HW_STATUS_OK,
    ///< Not found
    DXL_SERVO_NOT_FOUND     = HW_STATUS_ERROR | (1 << 1),

    DXL_SERVO_MAX_ANGLE_CW  = HW_STATUS_ERROR | (2 << 1),

    DXL_SERVO_MAX_ANGLE_CWW = HW_STATUS_ERROR | (3 << 1)
  } dxl_status_type;

  class DxlServo
  {
    public:
  
      DxlServo(DynamixelClass& dxl, const uint8_t id);
  
      void config(const uint16_t min, const uint16_t max, const uint16_t zero);

      void move(const int16_t target);

      void moveToZero();
  
    protected:
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

      // Error status
      hw_status status_;
  };
}

#endif
