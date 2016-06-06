/**
 * @brief Communication interface
 * @author David Gomez
 * @date 2016
 *
 * @TODO
 *
 */

#ifndef GOKART_COM_INTERFACE_H
#define GOKART_COM_INTERFACE_H

#include "gokart_msgs.h"
#include "rf_interface.h"

namespace GoKart
{
  class ICommunication
  {
    public:

    	virtual void update() = 0;

    	virtual inline uint32_t getChannel(const uint8_t ch);

    	virtual void getCommand(DataSerialization::GoKartCommand& cmd) = 0;

    	virtual ~ICommunication(); 
      
  };
}

#endif
