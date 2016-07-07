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
  gokart.lcd.test();
  delay(50);
}
