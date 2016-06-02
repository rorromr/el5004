#include "rf_interface.h"
#include "Arduino.h"

namespace GoKart
{
  RFInterface::RFInterface(const uint8_t ch_num):
    ch_num_(ch_num)
  {
    // @TODO
    // Assert ch_num > RF_INTERFACE_MAX_CH
    ports_[0]= GOKART_RF_CH1_PIN;
    ports_[1]= GOKART_RF_CH2_PIN;
    ports_[2]= GOKART_RF_CH3_PIN;

    pinMode(GOKART_RF_CH1_PIN, INPUT); //I connected this to Chan1 of the Receiver
    pinMode(GOKART_RF_CH2_PIN, INPUT); //I connected this to Chan3 of the Receiver
    pinMode(GOKART_RF_CH3_PIN, INPUT); //I connected this to Chan6 of the Receiver

    uptime_[0]= 0UL;
    uptime_[1]= 0UL;
    uptime_[2]= 0UL;
  }
  
  void RFInterface::update()
  {
    // @TODO
    // Update uptime_[]

    uptime_[0]=pulseIn(GOKART_RF_CH1_PIN, HIGH, 21000); 
    uptime_[1]=pulseIn(GOKART_RF_CH2_PIN, HIGH, 21000); 
    uptime_[2]=pulseIn(GOKART_RF_CH3_PIN, HIGH, 21000); 
  }
  
  void RFInterface::getCommand (DataSerialization::GoKartCommand &command){

    command.stwheel.data = (uint8_t) map(uptime_[0], 970, 1980, -128, 128);
  }
}

