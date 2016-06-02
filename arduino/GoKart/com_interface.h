/**
 * @brief Communication interface
 * @author Rodrigo Muñoz
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
  class ComInterface
  {
  public:
    virtual void getCommand(DataSerialization::GoKartCommand& cmd) = 0;
  };
}

#endif
