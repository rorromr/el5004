#include "Arduino.h"
#include "rf_interface.h"

GoKart::RFInterface rf(3);

void setup()
{
  rf.addChannel(1,6); // Channel 1 connected on 6 pin
  rf.addChannel(2,7); // Channel 2 connected on 6 pin
  rf.addChannel(3,8); // Channel 3 connected on 6 pin
}

void loop()
{
  rf.update();
  // Print values
  Serial.print("Ch1: "); Serial.println(rf.getChannel(1));
  Serial.print("Ch2: "); Serial.println(rf.getChannel(2));
  Serial.print("Ch3: "); Serial.println(rf.getChannel(3));
}

