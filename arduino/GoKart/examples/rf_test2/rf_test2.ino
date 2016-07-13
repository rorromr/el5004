#include "DynamixelSerial1.h"
#include "LiquidCrystal.h"
#include "gokart.h"

GoKart::RFInterface rf(GOKART_RF_CH_NUM);
DataSerialization::GoKartCommand cmd;

void setup()
{
  Serial.begin(115200);
  rf.enableFilter(true);
}

void loop()
{
  rf.update();
  rf.getCommand(cmd);
  // Print values
  Serial.print("Ch1: "); Serial.print(rf.getChannel(0));
  Serial.print(" | "); Serial.println(cmd.stwheel.data);
  
  Serial.print("Ch2: "); Serial.print(rf.getChannel(1));
  Serial.print(" | "); Serial.print(cmd.brake.data);
  Serial.print(" | "); Serial.println(cmd.throttle.data);
  
  Serial.print("Ch3: "); Serial.print(rf.getChannel(2));
  Serial.print(" | "); Serial.println(cmd.emergency.data);
  
  Serial.print("error counter: "); Serial.println(rf.counter_error);
  Serial.print("funcion update Consistency: "); Serial.println(rf.updateConsistencyError( rf.getChannel(0),  rf.getChannel(1),  rf.getChannel(2) ));
  
  Serial.print("flag cH1: "); Serial.println(rf.flagInterruptCH1);
  Serial.print("flag cH2: "); Serial.println(rf.flagInterruptCH2);
  Serial.print("flag cH3: "); Serial.println(rf.flagInterruptCH3);
  
  delay(50);
}
