#include "DynamixelSerial1.h"
#include "gokart.h"

GoKart::SerialInterface serial_iface(Serial);
DataSerialization::GoKartCommand cmd;

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  serial_iface.update();
  serial_iface.getCommand(cmd);
  // Print values
  Serial.print("st: "); Serial.print(cmd.stwheel.data);
  Serial.print(" | brk: "); Serial.print(cmd.brake.data);
  Serial.print(" | thr: "); Serial.print(cmd.throttle.data);
  Serial.print(" | em: "); Serial.println(cmd.emergency.data);
  
  delay(50);
}
