#include "DynamixelSerial1.h"
#include "gokart.h"
#include <stdio.h>

GoKart::SerialInterface serialCom(Serial);
GoKart::GoKartHW gokart(Dynamixel, serialCom);
char print_buffer[30];

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
   * AVOID TO USE PRINT IN MAIN LOOP!
   * 
  */
  /*
  // Brake
  sprintf(print_buffer, "BR %4d | %4d\n", gokart.cmd_.brake.data, gokart.brake.getPosition());
  Serial.print(print_buffer);
  // Steering wheel
  sprintf(print_buffer, "SW %4d | %4d\n", gokart.cmd_.stwheel.data, gokart.sw.getPosition());
  Serial.print(print_buffer);
  // Throttle
  sprintf(print_buffer, "TH %4d | %4d\n", gokart.cmd_.throttle.data, gokart.thr.getPosition());
  Serial.print(print_buffer);
  */
}
