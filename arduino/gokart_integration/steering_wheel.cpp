#include "steering_wheel.h"

namespace GoKart
{
  SteeringWheel::SteeringWheel(DynamixelClass& dxl, const uint8_t id):
    DxlServo(dxl,id)
  {
    ;    
  }
    

  void SteeringWheel::center()
  {
    dxl_->move(id_,zero_);
  }

}

