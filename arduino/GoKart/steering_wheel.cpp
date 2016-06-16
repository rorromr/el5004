#include "steering_wheel.h"

namespace GoKart
{
  SteeringWheel::SteeringWheel(DynamixelClass& dxl, const uint8_t id):
    DxlServo(dxl,id),
    speed_(GOKART_STEERINGWHEEL_DEFAULT_SPEED)
  {
    ;
  }
  
  void SteeringWheel::move(const int8_t pos_target)
  {
    // Map values
    int16_t encoder_target = (pos_target < 0) ? (GOKART_STEERINGWHEEL_CENTER_ENCODER-pos_target*NEGATIVE_MAP_FACTOR) : (GOKART_STEERINGWHEEL_CENTER_ENCODER-pos_target*POSITIVE_MAP_FACTOR);
    dxl_->moveSpeed( id_, encoder_target, speed_);
  }

  void SteeringWheel::center()
  {
    dxl_->moveSpeed( id_, zero_, GOKART_STEERINGWHEEL_DEFAULT_SPEED);
  }

  void SteeringWheel::setSpeed(const uint16_t speed)
  {
    speed_ = speed > 1023 ? 1023 : speed;
  }

}

