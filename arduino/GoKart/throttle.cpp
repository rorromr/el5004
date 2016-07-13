#include "throttle.h"

namespace GoKart
{
  Throttle::Throttle(DynamixelClass& dxl, const uint8_t id):
    DxlServo(dxl,id)
  {
    ;    
  }

  bool Throttle::init()
  {
    return DxlServo::init(GOKART_THROTTLE_CW_ENCODER, GOKART_THROTTLE_CCW_ENCODER, GOKART_THROTTLE_CENTER_ENCODER);
  }

  void Throttle::move(const uint8_t pos_target)
  {
    // Map values
    int16_t encoder_target = min_ + ((int16_t) (GOKART_THROTTLE_COMMAND_FACTOR * max_ * pos_target));
    dxl_->moveSpeed(id_, encoder_target, GOKART_THROTTLE_DEFAULT_SPEED);
  }
    
  void Throttle::full()
  {
    dxl_->move(id_,max_);
  }

  void Throttle::release()
  {
    dxl_->move(id_,min_);
  }

}

