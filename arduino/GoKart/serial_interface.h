/**
 * @brief Serial communication interface
 * @author Rodrigo Muñoz
 * @date 2016
 *
 * Serial interface
 * ----------------
 *
 * @TODO
 *
 */

#ifndef SERIAL_INTERFACE_H
#define SERIAL_INTERFACE_H

#include <stdint.h>
#include "comm_interface.h"
#include "Arduino.h"

#define GOKART_SERIAL_CMD_BUFFER 16

namespace GoKart
{
  class SerialInterface: public CommInterface
  {
    public:
      SerialInterface(Stream& serial);

      /**
       * @brief Update command.
       * Usually you call this method in your control loop.
       */
      virtual void update();

      void process(uint8_t data);

      
      /**
       * @brief Fill the command using received data.
       * Usually called before update() method.
       *
       * @param cmd Command to fill
       */
      virtual void getCommand(DataSerialization::GoKartCommand& cmd);

      /**
       * @brief Initializate and verify communication.
       *
       * @return true if the interface is available, false otherwise
       */
      virtual bool init();

    private:
      Stream* serial_;
      uint8_t cmdState_;
      uint8_t cmdChecksum_;
      uint8_t cmdFinish_;
      uint8_t cmdIdx_;
      uint32_t lastCall_;
      DataSerialization::GoKartCommand currentCmd_;
      uint8_t cmdBuffer_[GOKART_SERIAL_CMD_BUFFER];
  };
}

#endif
