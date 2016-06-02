/**
 * @brief RF Interface with 2.4 GHz receiver
 * @author Matias Silva, Sebastián Piña, Rodrigo Muñoz
 * @date 2016
 *
 * RF Interface
 * ------------
 *
 * @TODO
 *
 */

#ifndef RF_INTERFACE_H
#define RF_INTERFACE_H

#include <stdint.h>
#include "gokart_msgs.h"

#define RF_INTERFACE_MAX_CH 8

// RF
#define GOKART_RF_CH_NUM 3
#define GOKART_RF_CH1_PIN 5
#define GOKART_RF_CH2_PIN 6
#define GOKART_RF_CH3_PIN 7

namespace GoKart
{
  class RFInterface
  {
    public:
  
      RFInterface(const uint8_t ch_num);
  
      /**
       * @brief Add channel to RFInterface
       * 
       * @param ch Channel number
       * @param port Pin connection
       * 
       * @return True if the channel was successfully added
       */
      /*inline bool addChannel(const uint8_t ch, const uint8_t port)
      {
        ports_[ch] = port;
      }
      /*
      
      /**
       * @brief Update all channels.
       * Usually you call this method in your control loop.
       */
      void update();
  
      /**
       * @brief Get last channel uptime.
       * Usually called before update() method.
       * 
       * @param ch Channel
       * @return Channel uptime (pulse duration)
       */
      inline uint32_t getChannel(const uint8_t ch)
      {
        return uptime_[ch];
      }

      void getCommand (DataSerialization::GoKartCommand &command);
  
    private:
      // Total number of channels
      uint8_t ch_num_;
  
      // Array of ports
      uint8_t ports_[RF_INTERFACE_MAX_CH];
  
      // Array of uptime (pulse durations)
      uint32_t uptime_[RF_INTERFACE_MAX_CH];
  };
}

#endif
