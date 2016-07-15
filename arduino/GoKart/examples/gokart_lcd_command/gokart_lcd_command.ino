#include "DynamixelSerial1.h"
#include "LiquidCrystal.h"
#include "gokart.h"

GoKart::RFInterface rf(GOKART_RF_CH_NUM);
GoKart::GoKartHW gokart(Dynamixel, rf);

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
    gokart.lcd.printMenu(&gokart.cmd_);
  }

  // Set actuators
  gokart.setCommand();
  gokart.lcd.printMenu(&gokart.cmd_);
}
