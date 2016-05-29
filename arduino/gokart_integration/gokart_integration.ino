#include "DynamixelSerial1.h"
#include "gokart.h"

// Dynamixel protocol
#define GOKART_DXL_BAUDRATE 200000
#define GOKART_DXL_CTRL_PIN 2

GoKart::GoKartHW gokart(Dynamixel);

void setup()
{
  Dynamixel.begin(GOKART_DXL_BAUDRATE,GOKART_DXL_CTRL_PIN);
  gokart.init();
}

void loop()
{
  gokart.rf.update();
  // Print values
  Serial.print("Ch1: "); Serial.println(gokart.rf.getChannel(1));
  Serial.print("Ch2: "); Serial.println(gokart.rf.getChannel(2));
  Serial.print("Ch3: "); Serial.println(gokart.rf.getChannel(3));

  gokart.brake.full();
  delay(1500);
  gokart.brake.release();
  delay(1500);
}

