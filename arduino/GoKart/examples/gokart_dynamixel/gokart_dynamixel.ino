#define DEBUG_GOKART
#include "DynamixelSerial1.h"
#include "gokart.h"

// Dynamixel protocol
#define GOKART_DXL_BAUDRATE 1000000
#define GOKART_DXL_CTRL_PIN 2

GoKart::DxlServo servo(Dynamixel, 1);

void setup()
{
  Serial.begin(57600);
  Dynamixel.begin(GOKART_DXL_BAUDRATE,GOKART_DXL_CTRL_PIN);
  servo.config(100,3100,1600);
}

void loop()
{
  servo.check();
  Serial.print("Pos: "); Serial.println(servo.getPosition());
  delay(100); 
}

