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

namespace GoKart
{
  class CommInterface
  {
    public:

      virtual bool update() = 0;

      virtual void getCommand(DataSerialization::GoKartCommand& cmd) = 0;

      virtual bool init() = 0;

  };
}

#endif
