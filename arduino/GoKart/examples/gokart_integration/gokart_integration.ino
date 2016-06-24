#include "DynamixelSerial1.h"
#include "gokart.h"

GoKart::RFInterface rf(GOKART_RF_CH_NUM);
GoKart::GoKartHW gokart(Dynamixel,rf);

void setup()
{
  Serial.begin(115200);
  Dynamixel.begin(GOKART_DXL_BAUDRATE, GOKART_DXL_CTRL_PIN);
  gokart.init();
}

void loop()
{
  gokart.com_->getCommand(gokart.cmd_);
  
  while(gokart.cmd_.emergency.data)
  {
    gokart.setEmergencyState();
    Serial.println("ON EMERGENCY!");
    delay(100);
    gokart.com_->getCommand(gokart.cmd_);
  }

  // Brake
  Serial.print("BR "); Serial.print(gokart.cmd_.brake.data);
  Serial.print(" | "); Serial.println(gokart.brake.getPosition());

  // Steering wheel
  Serial.print("SW "); Serial.print(gokart.cmd_.stwheel.data);
  Serial.print(" | "); Serial.println(gokart.sw.getPosition());

  gokart.sw.move(gokart.cmd_.stwheel.data);
  gokart.brake.move(gokart.cmd_.brake.data); 
}