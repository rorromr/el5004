#include "brake.h"

namespace GoKart
{
  Brake::Brake(DynamixelClass& dxl, const uint8_t id):
    DxlServo(dxl,id)
  {
    ;    
  }

  void Brake::move(const uint8_t pos_target)
  {
    // Map values
    int16_t encoder_target = min_ + 12 * pos_target;
    dxl_->moveSpeed( id_, encoder_target, DXL_SERVO_DEFAULT_SPEED);
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

