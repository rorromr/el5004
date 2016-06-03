#include "rf_interface.h"
#include "Arduino.h"

namespace GoKart
{
  RFInterface::RFInterface(const uint8_t ch_num):
    ch_num_(ch_num)
  {
    // @TODO
    // Assert ch_num > RF_INTERFACE_MAX_CH
    ports_[0] = GOKART_RF_CH1_PIN;
    ports_[1] = GOKART_RF_CH2_PIN;
    ports_[2] = GOKART_RF_CH3_PIN;

    // Config ports
    pinMode(GOKART_RF_CH1_PIN, INPUT); //I connected this to Chan1 of the Receiver
    pinMode(GOKART_RF_CH2_PIN, INPUT); //I connected this to Chan3 of the Receiver
    pinMode(GOKART_RF_CH3_PIN, INPUT); //I connected this to Chan6 of the Receiver

    uptime_[0] = 0UL;
    uptime_[1] = 0UL;
    uptime_[2] = 0UL;
  }

  void RFInterface::update()
  {
    uptime_[0] = pulseIn(GOKART_RF_CH1_PIN, HIGH, 21000);
    uptime_[1] = pulseIn(GOKART_RF_CH2_PIN, HIGH, 21000);
    uptime_[2] = pulseIn(GOKART_RF_CH3_PIN, HIGH, 21000);
  }


  void RFInterface::getCommand(DataSerialization::GoKartCommand& cmd)
  {
    //Stwheel match
    int medium_stwheel= round((GOKART_RF_STWHEEL_MIN + GOKART_RF_STWHEEL_MAX)/2);
    int left_max= medium_stwheel - round(GOKART_RF_STWHEEL_DELTA/2);
    int right_min= medium_stwheel + round(GOKART_RF_STWHEEL_DELTA/2);
    if (uptime_[0]<= left_max){
      cmd.stwheel.data = uptime_[0]<GOKART_RF_STWHEEL_MIN ? (uint8_t) -128 : (uint8_t) map(uptime_[0], GOKART_RF_STWHEEL_MIN, left_max, -128, 0);
    }
    else if (uptime_[0]>= throttle_min){
      cmd.stwheel.data = uptime_[0]>GOKART_RF_STWHEEL_MAX ? (uint8_t) 128 : (uint8_t) map(uptime_[0], throttle_min, GOKART_RF_STWHEEL_MAX, 0, 128);
    }
    else{
      cmd.stwheel.data = (uint8_t) 0;
    }

    //Brake & Throttle match
    int medium_brake_throttle= round((GOKART_RF_BRAKE_THROTTLE_MIN + GOKART_RF_BRAKE_THROTTLE_MAX)/2);
    int brake_max= medium_brake_throttle - round(GOKART_RF_BRAKE_THROTTLE_DELTA/2);
    int throttle_min= medium_brake_throttle + round(GOKART_RF_BRAKE_THROTTLE_DELTA/2);
    if (uptime_[1]<= brake_max){
      cmd.brake.data = uptime_[1]<GOKART_RF_BRAKE_THROTTLE_MIN ? (uint8_t) 255 : (uint8_t) map(uptime_[1], GOKART_RF_BRAKE_THROTTLE_MIN, brake_max, 255, 0);
      cmd.throttle.data = (uint8_t) 0;
    }
    else if (uptime_[1]>= throttle_min){
      cmd.throttle.data = uptime_[1]>GOKART_RF_BRAKE_THROTTLE_MAX ? (uint8_t) 255 : (uint8_t) map(uptime_[1], throttle_min, GOKART_RF_BRAKE_THROTTLE_MAX, 0, 255);
      cmd.brake.data = (uint8_t) 0;
    }
    else{
      cmd.throttle.data = (uint8_t) 0;
      cmd.brake.data = (uint8_t) 0;
    }

    //Emergency match
    int medium_emergency= (GOKART_RF_EMERGENCY_MIN + GOKART_RF_EMERGENCY_MAX)/2;
    if ( uptime_[2]>medium_emergency ){
      cmd.emergency.data = (uint8_t) 1;
    }
    else{
      cmd.emergency.data = (uint8_t) 0;
    }
  }
}
