#include "DynamixelSerial1.h"
#include "LiquidCrystal.h"
#include "gokart.h"

GoKart::RFInterface rf(GOKART_RF_CH_NUM);
DataSerialization::GoKartCommand cmd;

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  rf.update();
  // Print values
  Serial.print("Ch1: "); Serial.println(rf.getChannel(0));
  Serial.print("Ch2: "); Serial.println(rf.getChannel(1));
  Serial.print("Ch3: "); Serial.println(rf.getChannel(2));
  Serial.println("---------");
  rf.getCommand(cmd);
  Serial.print("Direccion: "); Serial.println(cmd.stwheel.data);
  Serial.print("Freno: "); Serial.println(cmd.brake.data);
  Serial.print("Acelerador: "); Serial.println(cmd.throttle.data);
  Serial.print("Emergencia: "); Serial.println(cmd.emergency.data);

  Serial.println("---------");
  Serial.println("---------");
  Serial.println("---------");
  
  delay(1000);
}
