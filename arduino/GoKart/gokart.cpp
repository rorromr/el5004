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
    // @TODO
    // Verify init state of motors and rf
  }

  uint8_t GoKartHW::getErrorCode()
  {
    return 0U;
  }

  void GoKartHW::setEmergencyState()
  {
    brake.full();
    sw.center();
  }

  void GoKartHW::setCommunication(ICommunication &com)
  {
    com_ = &com;
  }

  void GoKartHW::updateCommand()
  {
    com_->getCommand(cmd_);
  }

  void GoKartHW::printCommand()
  {
    updateCommand();
    Serial.println("COMANDOS");
    Serial.print("  Direccion: "); Serial.println(cmd_.stwheel.data);
    Serial.print("  Freno: "); Serial.println(cmd_.brake.data);
    Serial.print("  Acelerador: "); Serial.println(cmd_.throttle.data);
    Serial.print("  Emergencia: "); Serial.println(cmd_.emergency.data);
    Serial.println();
  }

}
