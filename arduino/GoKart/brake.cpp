#include "brake.h"

namespace GoKart
{
  Brake::Brake(DynamixelClass& dxl, const uint8_t id):
    DxlServo(dxl,id)
  {
    ;    
  }
    
  void Brake::full()
  {
    dxl_->move(id_,max_);
  }

  void Brake::release()
  {
    dxl_->move(id_,zero_);
  }

}

