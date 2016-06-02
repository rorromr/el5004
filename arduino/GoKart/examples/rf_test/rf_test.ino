#include "DynamixelSerial1.h"
#include "gokart.h"

GoKart::RFInterface rf(GOKART_RF_CH_NUM);
DataSerialization::GoKartCommand cmd;

void setup()
{
  Serial.begin(9600);
  //rf.addChannel(1, GOKART_RF_CH1_PIN); // Channel 1 connected on 6 pin
  //rf.addChannel(2, GOKART_RF_CH2_PIN); // Channel 2 connected on 7 pin
  //rf.addChannel(3, GOKART_RF_CH3_PIN); // Channel 3 connected on 8 pin  
}

void loop()
{
  rf.update();
  // Print values
  Serial.print("Ch1: "); Serial.println(rf.getChannel(0));
  Serial.print("Ch2: "); Serial.println(rf.getChannel(1));
  Serial.print("Ch3: "); Serial.println(rf.getChannel(2));

  rf.getCommand(cmd);
  Serial.print("Direccion: "); Serial.println(cmd.stwheel.data);
  //Serial.print("freno: "); Serial.println(cmd.brake.data);
  //Serial.print("Ch1: "); Serial.println(cmd.throttle.data);
  //Serial.print("Ch1: "); Serial.println(cmd.emergency.data);


  delay(500);
}
