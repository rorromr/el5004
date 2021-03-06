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
#include "comm_interface.h"

 // RF
#define GOKART_RF_CH_NUM 3

#define GOKART_RF_CH1_PIN 2
#define GOKART_RF_CH2_PIN 3
#define GOKART_RF_CH3_PIN 20
#define RF_INTERFACE_MAX_CH 8

//#define RF_INTERFACE_BUFFER_SIZE 10
#define RF_INTERFACE_FIR_NEW_VALUE_WEIGHT 0.2

#define RF_INTERFACE_ERROR_COUNTER_MAX 10

#define RF_INTERFACE_DISCRETIZATION_SCALE 3

#define GOKART_RF_EMERGENCY_MIN 900
#define GOKART_RF_EMERGENCY_MAX 1900
#define GOKART_RF_EMERGENCY_DELTA 100

#define GOKART_RF_STWHEEL_MIN 990
#define GOKART_RF_STWHEEL_MAX 1965
#define GOKART_RF_STWHEEL_DELTA 100

#define GOKART_RF_BRAKE_THROTTLE_MIN 1000
#define GOKART_RF_BRAKE_THROTTLE_MAX 1960
#define GOKART_RF_BRAKE_THROTTLE_DELTA 150

namespace GoKart
{
  class RFInterface: public CommInterface
  {
    public:
      RFInterface(const uint8_t ch_num);

      /**
      * @brief Update all channels.
      * Usually you call this method in your control loop.
      */
      bool update();

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
      bool init();

      /**
      * @brief Get mean.
      *
      * @param buffer Buffer pointer.
      * @return mean of the buffer.
      */
      //uint32_t meanBuffer(uint32_t *buffer);

      uint32_t escalon(uint32_t valorAntiguo, uint32_t valorActual);
      
      static RFInterface* _activeRF;

      static inline void isrMeasureCH1()
      {
        _activeRF->measureCH1();
      }

      static inline void isrMeasureCH2()
      {
        _activeRF->measureCH2();
      }

      static inline void isrMeasureCH3()
      {
        _activeRF->measureCH3();
      }

      void measureCH1();
      void measureCH2();
      void measureCH3();

      bool updateConsistencyError(uint32_t upTimeCH1, uint32_t upTimeCH2, uint32_t upTimeCH3 );
      bool isConsistency();

      void enableFIRFilter(bool enable);

      volatile uint32_t risingTimeCH1;  //Time of front raising
      volatile uint32_t fallingTimeCH1; //Time of front falling
      volatile uint32_t upTimeCH1;      //Time of pulse CH1

      volatile uint32_t risingTimeCH2;  //Time of front raising
      volatile uint32_t fallingTimeCH2; //Time of front falling
      volatile uint32_t upTimeCH2;      //Time of pulse CH2

      volatile uint32_t risingTimeCH3;  //Time of front raising
      volatile uint32_t fallingTimeCH3; //Time of front falling
      volatile uint32_t upTimeCH3;      //Time of pulse CH3

      volatile uint8_t channelFlag;
      
      uint8_t counter_error; //Error counter

      bool overrun;

    private:
      // Total number of channels
      uint8_t ch_num_;

      // Array of ports
      uint8_t ports_[RF_INTERFACE_MAX_CH];

      // Array of uptime (pulse durations)
      uint32_t uptime_[RF_INTERFACE_MAX_CH];

      bool enableFilter_;
  };
}

#endif
