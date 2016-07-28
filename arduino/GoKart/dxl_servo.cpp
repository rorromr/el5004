#include "dxl_servo.h"

namespace GoKart
{
  
  DxlServo::DxlServo(DynamixelClass& dxl, const uint8_t id):
    dxl_(&dxl),
    id_(id)
  {
    if (!dxl_)
    {
      ERROR_PRINT_NAMED("DxlServo/config", "Null interface "); ERROR_PRINTLN_RAW(id_);
      set_error(&status_, DXL_SERVO_NULL_INTERFACE);
    }
  }

  bool DxlServo::init(const uint16_t min, const uint16_t max, const uint16_t zero, const uint16_t speed)
  {
    min_ = min;
    max_ = max;
    zero_ = zero;
    speed_ = speed;

    if (!dxl_)
    {
      ERROR_PRINT_NAMED("DxlServo/config", "Null interface "); ERROR_PRINTLN_RAW(id_);
      set_error(&status_, DXL_SERVO_NULL_INTERFACE);
      return false;
    }

    // Set config
    uint8_t error = 0U;
    error = dxl_->setCWLimit(id_, min_);
    error = dxl_->setCCWLimit(id_, max_);
    if (error)
    {
      ERROR_PRINT_NAMED("DxlServo/config", "Servo fail config "); ERROR_PRINTLN_RAW(id_);
      set_error(&status_, DXL_SERVO_ERROR_CONFIG);
      return false;
    }

    set_error(&status_, DXL_SERVO_OK);
    return true;
  }

  void DxlServo::move(const int16_t pos_target, const int16_t speed_target)
  {
    dxl_->moveSpeed( id_, pos_target, speed_target);
  }

  int16_t DxlServo::getPosition()
  {
    return dxl_->readPosition(id_);
  }

  void DxlServo::moveToZero()
  {
    dxl_->move(id_,zero_);
  }
  
  int16_t DxlServo::getCCWLimit()
  {
    return dxl_->readCCWLimit(id_);
  }

  int16_t DxlServo::getCWLimit()
  {
    return dxl_->readCCWLimit(id_);
  }

  int16_t DxlServo::setCCWLimit(uint16_t limit)
  {
    return dxl_->setCCWLimit(id_, limit);
  }

  int16_t DxlServo::setCWLimit(uint16_t limit)
  {
    return dxl_->setCWLimit(id_, limit);
  }

  int16_t DxlServo::torqueEnable(bool torque_enable)
  {
    return dxl_->torqueStatus(id_, torque_enable);
  }

  int16_t DxlServo::getLoad()
  {
    return dxl_->readLoad(id_);
  }

  int16_t DxlServo::setSpeed(uint16_t speed)
  {
    speed_ = speed > 1023 ? 1023 : speed;
    return 0;
  }


  bool DxlServo::check()
  {
    DEBUG_PRINTLN_NAMED("dxl_servo/check","check");
    // Ping check
    uint8_t ping_attempts = 0U;
    uint8_t ping_status = 0U;
    while(!ping_status && ping_attempts < DXL_SERVO_PING_ATTEMPTS)
    {
      DEBUG_PRINT_NAMED("dxl_servo/check","ping attempt with servo "); DEBUG_PRINTLN_RAW(id_);
      ping_status = dxl_->ping(id_) == -1 ? 0U : 1U;
      ++ping_attempts;
    }
    if (!ping_status)
    {
      ERROR_PRINT_NAMED("dxl_servo/check", "Servo not found "); ERROR_PRINTLN_RAW(id_);
      set_error(&status_, DXL_SERVO_NOT_FOUND);
      return false;
    }
    // Check angles
    uint16_t pos = dxl_->readPosition(id_);
    if (pos > max_)
    {
      ERROR_PRINT_NAMED("dxl_servo/check","Servo max angle CCW "); ERROR_PRINTLN_RAW(id_);
      set_error(&status_, DXL_SERVO_MAX_ANGLE_CW);
      return false;
    }
    else if (pos < min_)
    {
      ERROR_PRINT_NAMED("dxl_servo/check","Servo max angle CW "); ERROR_PRINTLN_RAW(id_);
      set_error(&status_, DXL_SERVO_MAX_ANGLE_CCW);
      return false;
    }

    set_error(&status_, DXL_SERVO_OK);
    return true;
  }
  
}

