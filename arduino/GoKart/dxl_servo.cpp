#include "dxl_servo.h"

namespace GoKart
{
  
  DxlServo::DxlServo(DynamixelClass& dxl, const uint8_t id):
    dxl_(&dxl),
    id_(id)
  {
    
    // @TODO
    // Assert dxl null
  }

  void DxlServo::config(const uint16_t min, const uint16_t max, const uint16_t zero)
  {
    min_ = min;
    max_ = max;
    zero_ = zero;
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
    uint8_t attemps = 0;
    uint8_t check_status = 0;
    DEBUG_PRINTLN("Init servo check");

    // Ping check
    while(check_status == 0)
    {
      switch(check_status)
      {
        case 0:
          check_status = dxl_->ping(id_) == -1 ? 0 : 1;
          ++attemps;
          check_status = attemps > DXL_SERVO_PING_ATTEMPTS ? 2 : check_status;
          break;
        case 1:
          set_error(&status_, DXL_SERVO_OK);
          break;
        case 2:
          set_error(&status_, DXL_SERVO_NOT_FOUND);
          DEBUG_PRINTLN("Servo not found");
          break;
      }
    }
    if (check_error(&status_)) return false;

    // Check angles
    uint16_t pos = dxl_->readPosition(id_);
    if (pos > max_)
    {
      DEBUG_PRINTLN("Servo max angle CW");
      set_error(&status_, DXL_SERVO_MAX_ANGLE_CW);
      return false;
    }
    else if (pos < min_)
    {
      DEBUG_PRINTLN("Servo max angle CCW");
      set_error(&status_, DXL_SERVO_MAX_ANGLE_CCW);
      return false;
    }

    return true;


  }
  
}

