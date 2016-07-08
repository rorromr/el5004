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
#include "debug.h"

#define DXL_SERVO_PING_ATTEMPTS 4
#define DXL_SERVO_DEFAULT_SPEED 300

namespace GoKart
{
  /// Dynamixel servo error definition
  typedef enum {
    ///< No error
    DXL_SERVO_OK            = HW_STATUS_OK,
    ///< Not found
    DXL_SERVO_NOT_FOUND     = HW_STATUS_ERROR | (1 << 1),

    DXL_SERVO_MAX_ANGLE_CW  = HW_STATUS_ERROR | (2 << 1),

    DXL_SERVO_MAX_ANGLE_CCW = HW_STATUS_ERROR | (3 << 1),

    DXL_SERVO_ERROR_CONFIG  = HW_STATUS_ERROR | (4 << 1),

    DXL_SERVO_NULL_INTERFACE= HW_STATUS_ERROR | (5 << 1)
    
  } dxl_status_type;

  class DxlServo
  {
    public:
  
      DxlServo(DynamixelClass& dxl, const uint8_t id);
  
      virtual bool init(const uint16_t min, const uint16_t max, const uint16_t zero);

      virtual bool init()
      {
        return true;
      }

      void move(const int16_t pos_target, const int16_t vel_target = DXL_SERVO_DEFAULT_SPEED);

      int16_t getPosition();

      int16_t getCCWLimit();

      int16_t getCWLimit();

      int16_t setCCWLimit(uint16_t limit);

      int16_t setCWLimit(uint16_t limit);

      void moveToZero();

      bool check();
  
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
