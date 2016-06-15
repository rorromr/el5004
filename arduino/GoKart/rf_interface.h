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
#include "ICommunication.h"

 // RF
#define GOKART_RF_CH_NUM 3

#define GOKART_RF_CH1_PIN 5
#define GOKART_RF_CH2_PIN 6
#define GOKART_RF_CH3_PIN 7
#define RF_INTERFACE_MAX_CH 8

#define GOKART_RF_EMERGENCY_MIN 900
#define GOKART_RF_EMERGENCY_MAX 1900

#define GOKART_RF_STWHEEL_MIN 990
#define GOKART_RF_STWHEEL_MAX 1965
#define GOKART_RF_STWHEEL_DELTA 100

#define GOKART_RF_BRAKE_THROTTLE_MIN 1000
#define GOKART_RF_BRAKE_THROTTLE_MAX 1960
#define GOKART_RF_BRAKE_THROTTLE_DELTA 150

namespace GoKart
{
  class RFInterface: public ICommunication
  {
    public:
      RFInterface(const uint8_t ch_num);

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

      virtual void getCommand(DataSerialization::GoKartCommand& cmd);

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
