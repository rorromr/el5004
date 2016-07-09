#define DEBUG_GOKART
#include "LiquidCrystal.h"
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
}

void loop()
{
  servo.check();
  Serial.print("Pos: "); Serial.println(servo.getPosition());
  delay(100); 
  while (true){
  	servo.move(1400);
  	delay(2000); 
  	Serial.print("Pos: "); Serial.println(servo.getPosition());

  	servo.move(800);
  	delay(2000); 
  	Serial.print("Pos: "); Serial.println(servo.getPosition());
  }
  
}

