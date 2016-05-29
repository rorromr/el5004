#include "dxl_servo.h"

namespace GoKart
{
  
  DxlServo::DxlServo(DynamixelClass& dxl, const uint8_t id):
    dxl_(&dxl),
    id_(id)
  {
    // @TODO
    // Assert dxl null
    ;
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
  
}

