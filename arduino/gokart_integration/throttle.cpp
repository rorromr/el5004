#include "throttle.h"

namespace GoKart
{
  Throttle::Throttle(DynamixelClass& dxl, const uint8_t id):
    DxlServo(dxl,id)
  {
    ;    
  }
    
  void Throttle::full()
  {
    dxl_->move(id_,max_);
  }

  void Throttle::release()
  {
    dxl_->move(id_,zero_);
  }

}

