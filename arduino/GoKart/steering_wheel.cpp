#include "steering_wheel.h"

namespace GoKart
{
  SteeringWheel::SteeringWheel(DynamixelClass& dxl, const uint8_t id):
    DxlServo(dxl,id),
    speed_(GOKART_SW_DEFAULT_SPEED)
  {
    ;
  }

  bool SteeringWheel::init()
  {
    return DxlServo::init(GOKART_SW_CW_ENCODER, GOKART_SW_CCW_ENCODER, GOKART_SW_CENTER_ENCODER);
  }
  
  void SteeringWheel::move(const int8_t pos_target)
  {
    // Map values
    int16_t encoder_target = (pos_target < 0) ? (GOKART_SW_CENTER_ENCODER-pos_target*GOKART_SW_NEG_MAP_FACTOR) : (GOKART_SW_CENTER_ENCODER-pos_target*GOKART_SW_POS_MAP_FACTOR);
    dxl_->moveSpeed( id_, encoder_target, speed_);
  }

  void SteeringWheel::center()
  {
    dxl_->moveSpeed( id_, GOKART_SW_CENTER_ENCODER, GOKART_SW_DEFAULT_SPEED);
  }

  void SteeringWheel::setSpeed(const uint16_t speed)
  {
    speed_ = speed > 1023 ? 1023 : speed;
  }

}

