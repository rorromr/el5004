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


  bool GoKartHW::init()
  {
    // Verify motors
    bool result = false;
    // Init brake
    result = brake.init();
    if (!result) DEBUG_PRINTLN("E/GoKart/init/Brake bad initialization");

    // Init steering wheel
    result = sw.init();
    if (!result) DEBUG_PRINTLN("E/GoKart/init/SteeringWheel bad initialization");
    
    // Init throttle
    result = thr.init();
    if (!result) DEBUG_PRINTLN("E/GoKart/init/Throttle bad initialization");

    // Init communication
    result = com_->init();
    if (!result) DEBUG_PRINTLN("E/GoKart/init/Communication bad initialization");

  }

  uint8_t GoKartHW::getErrorCode()
  {
    return 0U;
  }

  void GoKartHW::setEmergencyState()
  {
    // Put the brake full
    brake.full();
    // Center wheels
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

  void GoKartHW::setCommand()
  {
    // Set steering wheel command
    sw.move(cmd_.stwheel.data);
    // Set brake command
    brake.move(cmd_.brake.data);
    // Set throttle
    // @TODO
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
