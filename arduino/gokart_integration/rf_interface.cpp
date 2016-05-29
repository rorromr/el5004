#include "rf_interface.h"

namespace GoKart
{
  RFInterface::RFInterface(const uint8_t ch_num):
    ch_num_(ch_num)
  {
    // @TODO
    // Assert ch_num > RF_INTERFACE_MAX_CH
    ;
  }
  
  void RFInterface::update() const
  {
    // @TODO
    // Update uptime_[]
    ;
  }
  
}

