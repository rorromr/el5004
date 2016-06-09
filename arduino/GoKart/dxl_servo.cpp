#include "dxl_servo.h"

namespace GoKart
{
  
  DxlServo::DxlServo(DynamixelClass& dxl, const uint8_t id):
    dxl_(&dxl),
    id_(id)
  {
    if (!dxl_)
    {
      DEBUG_PRINT("E/DxlServo/config/Null interface "); DEBUG_PRINTLN(id_);
      set_error(&status_, DXL_SERVO_NULL_INTERFACE);
    }
  }

  bool DxlServo::config(const uint16_t min, const uint16_t max, const uint16_t zero)
  {
    min_ = min;
    max_ = max;
    zero_ = zero;

    if (!dxl_)
    {
      DEBUG_PRINT("E/DxlServo/config/Null interface "); DEBUG_PRINTLN(id_);
      set_error(&status_, DXL_SERVO_NULL_INTERFACE);
      return false;
    }

    // Set config
    uint8_t error = 0U;
    error = dxl_->setCWLimit(id_, min_);
    error = dxl_->setCCWLimit(id_, max_);
    if (error)
    {
      DEBUG_PRINT("E/DxlServo/config/Servo fail config "); DEBUG_PRINTLN(id_);
      set_error(&status_, DXL_SERVO_ERROR_CONFIG);
      return false;
    }

    set_error(&status_, DXL_SERVO_OK);
    return true;
  }

  void DxlServo::move(const int16_t target)
  {
    int16_t encoder_target = target;
    // @TODO Map value from -254<target<254 -> encoder position using min_,max_,zero_
    // Move servo using lib
    dxl_->move(id_,encoder_target);
  }

  int16_t DxlServo::getPosition()
  {
    return dxl_->readPosition(id_);
  }

  void DxlServo::moveToZero()
  {
    dxl_->move(id_,zero_);
  }

  bool DxlServo::check()
  {
    DEBUG_PRINTLN("DEBUG/DxlServo/check/");
    // Ping check
    uint8_t ping_attempts = 0U;
    uint8_t ping_status = 0U;
    while(!ping_status && ping_attempts < DXL_SERVO_PING_ATTEMPTS)
    {
      DEBUG_PRINT("D/DxlServo/check/New ping attempt with servo "); DEBUG_PRINTLN(id_);
      ping_status = dxl_->ping(id_) == -1 ? 0U : 1U;
      ++ping_attempts;
    }
    if (!ping_status)
    {
      DEBUG_PRINT("E/DxlServo/check/Servo not found "); DEBUG_PRINTLN(id_);
      set_error(&status_, DXL_SERVO_NOT_FOUND);
      return false;
    }
    // Check angles
    uint16_t pos = dxl_->readPosition(id_);
    if (pos > max_)
    {
      DEBUG_PRINT("E/DxlServo/check/Servo max angle CW "); DEBUG_PRINTLN(id_);
      set_error(&status_, DXL_SERVO_MAX_ANGLE_CW);
      return false;
    }
    else if (pos < min_)
    {
      DEBUG_PRINT("E/DxlServo/check/Servo max angle CCW "); DEBUG_PRINTLN(id_);
      set_error(&status_, DXL_SERVO_MAX_ANGLE_CCW);
      return false;
    }

    set_error(&status_, DXL_SERVO_OK);
    return true;
  }
  
}

