#include "gokart.h"

namespace GoKart
{
  GoKartHW::GoKartHW(DynamixelClass& dxl, ICommunication &com):
    dxl_(&dxl),
    brake(dxl, GOKART_BRAKE_ID),
    thr(dxl, GOKART_THROTTLE_ID),
    sw(dxl, GOKART_STEERINGWHEEL_ID)
  {
    setCommunication(com);
  }


  void GoKartHW::init()
  {
    // Add RF channels
    //rf.addChannel(1, GOKART_RF_CH1_PIN); // Channel 1 connected on 6 pin
    //rf.addChannel(2, GOKART_RF_CH2_PIN); // Channel 2 connected on 7 pin
    //rf.addChannel(3, GOKART_RF_CH3_PIN); // Channel 3 connected on 8 pin
  }

  uint8_t GoKartHW::getErrorCode()
  {
    return 0U;
  }

  void GoKartHW::setEmergencyState()
  {
    ;
  }

  void GoKartHW::setCommunication(ICommunication &com)
  {
    com_ = &com;
  }

  void GoKartHW::updateCommand(){
    com_->getCommand(cmd_);
  }

  void GoKartHW::printCommand(){
    updateCommand();
    Serial.println("COMANDOS");
    Serial.print("  Direccion: "); Serial.println(cmd_.stwheel.data);
    Serial.print("  Freno: "); Serial.println(cmd_.brake.data);
    Serial.print("  Acelerador: "); Serial.println(cmd_.throttle.data);
    Serial.print("  Emergencia: "); Serial.println(cmd_.emergency.data);
    Serial.println();
  }


  /*
  void setSerial()
  {
    SerialInterface se();
    com_ = &se;

  }*/

}
