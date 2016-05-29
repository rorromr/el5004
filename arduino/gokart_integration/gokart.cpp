#include "gokart.h"

namespace GoKart
{
  GoKartHW::GoKartHW(DynamixelClass& dxl):
    dxl_(&dxl),
    rf(GOKART_RF_CH_NUM),
    brake(dxl, GOKART_BRAKE_ID),
    thr(dxl, GOKART_THROTTLE_ID),
    sw(dxl, GOKART_STEERINGWHEEL_ID)
  {
    ;
  }


  void GoKartHW::init()
  {
    // Add RF channels
    rf.addChannel(1, GOKART_RF_CH1_PIN); // Channel 1 connected on 6 pin
    rf.addChannel(2, GOKART_RF_CH2_PIN); // Channel 2 connected on 7 pin
    rf.addChannel(3, GOKART_RF_CH3_PIN); // Channel 3 connected on 8 pin  
  }
      
  uint8_t GoKartHW::getErrorCode()
  {
    return 0U;
  }

  void GoKartHW::setEmergencyState()
  {
    ;
  }

}

