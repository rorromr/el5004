#include "brake.h"

namespace GoKart
{
  Brake::Brake(DynamixelClass& dxl, const uint8_t id):
    DxlServo(dxl,id)
  {
    ;    
  }

  bool Brake::init()
  {
    return DxlServo::init(GOKART_BRAKE_CW_ENCODER, GOKART_BRAKE_CCW_ENCODER, GOKART_BRAKE_CENTER_ENCODER);
  }

  void Brake::move(const uint8_t pos_target)
  {
    // Map values
    int16_t encoder_target = min_ + ((int16_t) (GOKART_BRAKE_COMMAND_FACTOR * max_ * pos_target));
    dxl_->moveSpeed(id_, encoder_target, GOKART_BRAKE_DEFAULT_SPEED);
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

