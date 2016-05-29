#include "Arduino.h"
#include "DynamixelSerial1.h"
#include "rf_interface.h"
#include "dxl_servo.h" 

// Dynamixel protocol
#define GOKART_DXL_BAUDRATE 200000
#define GOKART_DXL_CTRL_PIN 2

GoKart::RFInterface rf(3);

GoKart::DxlServo brake(Dynamixel, 5);

void setup()
{
  Dynamixel.begin(GOKART_DXL_BAUDRATE,GOKART_DXL_CTRL_PIN);
  brake.config(100, 200, 50);
  
  rf.addChannel(1,6); // Channel 1 connected on 6 pin
  rf.addChannel(2,7); // Channel 2 connected on 7 pin
  rf.addChannel(3,8); // Channel 3 connected on 8 pin
}

void loop()
{
  rf.update();
  // Print values
  Serial.print("Ch1: "); Serial.println(rf.getChannel(1));
  Serial.print("Ch2: "); Serial.println(rf.getChannel(2));
  Serial.print("Ch3: "); Serial.println(rf.getChannel(3));
}

