#include "serial_interface.h"
#include "debug.h"

namespace GoKart
{
  SerialInterface::SerialInterface(Stream& serial):
    serial_(&serial),
    cmdState_(0U),
    cmdChecksum_(0U),
    cmdFinish_(0U),
    lastCall_(0UL)
  {
    // Default command
    currentCmd_.stwheel.data = 0;
    currentCmd_.brake.data = 0U;
    currentCmd_.throttle.data = 0U;
    currentCmd_.emergency.data = 0U;
  }

  bool SerialInterface::update()
  {
    while (serial_->available())
    {
      process(serial_->read());
    }
    return true;
  }

  void SerialInterface::process(uint8_t data)
  {
    // Check message
    uint32_t now = millis();
    if (now - lastCall_ > 100)
    {
      // Reset states
      DEBUG_PRINTLN("W/Serial/Reset serial cmd");
      cmdState_ = 0U;
      cmdChecksum_ = 0U;
      cmdFinish_ = 0U;
      cmdIdx_ = 0U;
    }
    lastCall_ = now;

    // Command receive state machine
    switch(cmdState_)
    {
      case 0: // 0xFF
        cmdState_ = data == 0xFF ? 1 : 0;
        break;
        
      case 1: // 0XFF
        cmdState_ = data == 0xFF ? 2 : 1;
        break;
        
      case 2: // Data
        // Check error
        cmdBuffer_[cmdIdx_++] = data;
        cmdChecksum_ += data;
        cmdState_ = cmdIdx_ >= GOKART_MSGS_SIZE ? 3 : 2;
        break;
      
      case 3: // Finish
        cmdBuffer_[cmdIdx_] = data;
        cmdFinish_ = ((uint8_t)(~cmdChecksum_)) == data;
        cmdState_ = 0;
        cmdIdx_ = 0;
        cmdChecksum_ = 0;
    }
    // Check finish
    if (cmdFinish_)
    {
      // Get command from buffer
      currentCmd_.deserialize(cmdBuffer_);
    }

  }

  void SerialInterface::getCommand(DataSerialization::GoKartCommand& cmd)
  {
    // Copy each field
    cmd.stwheel.data = currentCmd_.stwheel.data;
    cmd.brake.data = currentCmd_.brake.data;
    cmd.throttle.data = currentCmd_.throttle.data;
    cmd.emergency.data = currentCmd_.emergency.data;      
  }

  bool SerialInterface::init()
  {
    // @TODO
    return true;
  }

}
