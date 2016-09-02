#include "gokart.h"

namespace GoKart
{
  GoKartHW::GoKartHW(DynamixelClass& dxl, CommInterface &com):
    dxl_(&dxl),
    brake(dxl, GOKART_BRAKE_ID),
    thr(dxl, GOKART_THROTTLE_ID),
    sw(dxl, GOKART_STEERINGWHEEL_ID),
    status_(0U)
  {
    setCommunication(com);
  }


  bool GoKartHW::init()
  {
    // Verify motors
    bool result = false;
    // Init brake
    result = brake.init();
    if (!result) ERROR_PRINTLN_NAMED("GoKart/init", "Brake bad initialization");

    // Init steering wheel
    result = sw.init();
    if (!result) ERROR_PRINTLN_NAMED("GoKart/init", "SteeringWheel bad initialization");
    
    // Init throttle
    result = thr.init();
    if (!result) ERROR_PRINTLN_NAMED("GoKart/init", "Throttle bad initialization");

    // Init communication
    result = com_->init();
    if (!result) ERROR_PRINTLN_NAMED("GoKart/init", "Communication bad initialization");

    // Init LCD
    lcd.init();
    // Add servos
    result = lcd.addServo(&brake, "BR");
    if (!result) ERROR_PRINTLN_NAMED("GoKart/init", "Fail to add brake servo to LCD");
    result = lcd.addServo(&thr, "TH");
    if (!result) ERROR_PRINTLN_NAMED("GoKart/init", "Fail to add throttle servo to LCD");
    result = lcd.addServo(&sw, "SW");
    if (!result) ERROR_PRINTLN_NAMED("GoKart/init", "Fail to add stwheel servo to LCD");
    
    DEBUG_PRINTLN_NAMED("GoKart/init", "GoKart init exit");
    // LCD print result
    lcd.clear();
    lcd.print("GoKart init");
    lcd.setCursor(5,1);
    if (result) lcd.print("[OK]");
    else lcd.print("[FAIL]");
    
    // @TODO Hardcoded return
    return true;
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
    // Release throttle
    thr.release();
  }

  void GoKartHW::setCommunication(CommInterface &com)
  {
    com_ = &com;
  }

  void GoKartHW::updateCommand()
  {
    com_->getCommand(cmd_);
  }

  void GoKartHW::setCommand()
  {
    uint32_t actual_time = millis();

    if ((actual_time - cmd_.stamp.data)> GOKART_TIMESTAMP_TIMEOUT){
      GoKartHW::setEmergencyState();
      status_ = 1U;
      lcd.clear();
      lcd.print("Commad timeout");
      delay(1000);
      return;
    }

    // Set steering wheel command
    sw.move(cmd_.stwheel.data);
    // Set brake command
    brake.move(cmd_.brake.data);
    // Set throttle
    thr.move(cmd_.throttle.data);
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

  void GoKartHW::printCommandLCD()
  {
    lcd.clear();
    lcd.printCommand(&cmd_);
  }

}
