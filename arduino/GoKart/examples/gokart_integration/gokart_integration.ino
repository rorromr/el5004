#include "DynamixelSerial1.h"
#include "gokart.h"

// Dynamixel protocol
#define GOKART_DXL_BAUDRATE 200000
#define GOKART_DXL_CTRL_PIN 2

GoKart::RFInterface rf(GOKART_RF_CH_NUM);
GoKart::GoKartHW gokart(Dynamixel,rf);

void setup()
{
  Dynamixel.begin(GOKART_DXL_BAUDRATE, GOKART_DXL_CTRL_PIN);
  gokart.init();
}

void loop()
{
  gokart.com_->getCommand(gokart.cmd_);
  gokart.printCommand();

  gokart.brake.full();
  delay(1500);
  gokart.brake.release();
  delay(1500);
}
