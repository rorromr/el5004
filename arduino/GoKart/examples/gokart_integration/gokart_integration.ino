#include "DynamixelSerial1.h"
#include "gokart.h"

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

  gokart.sw.move((gokart.cmd_.stwheel.data+500)*3);
}
