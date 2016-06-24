#include "DynamixelSerial1.h"
#include "gokart.h"

GoKart::RFInterface rf(GOKART_RF_CH_NUM);
GoKart::GoKartHW gokart(Dynamixel,rf);

void setup()
{
  Serial.begin(115200);
  Dynamixel.begin(GOKART_DXL_BAUDRATE, GOKART_DXL_CTRL_PIN);
  
  // Check GoKart components
  while(!gokart.init())
  {
    Serial.println("GoKart init fail");
    delay(500);
  }
}

void loop()
{
  // Get command from communication iface
  gokart.updateCommand();
  
  // Check emergency status
  while(gokart.isEmergency())
  {
    gokart.setEmergencyState();
    Serial.println("ON EMERGENCY!");
    delay(100);
    gokart.updateCommand();
  }

  // Set actuators
  gokart.setCommand();

  /*
   * DEBUG COMMAND
  */
  // Brake
  Serial.print("BR "); Serial.print(gokart.cmd_.brake.data);
  Serial.print(" | "); Serial.println(gokart.brake.getPosition());
  // Steering wheel
  Serial.print("SW "); Serial.print(gokart.cmd_.stwheel.data);
  Serial.print(" | "); Serial.println(gokart.sw.getPosition());
}
