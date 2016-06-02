/**
 * @brief Data serialization
 * @author Rodrigo Munoz
 * @date 2016
 *
 * Gokart Messages
 * ===============
 * 
 * Command message
 * ---------------
 * 
 * | Field      | Type     | Size (bytes) | Offset | Description             |
 * |------------|----------|--------------|--------|-------------------------|
 * | stwheel    | int8_t   | 4            | 0      | Steering wheel command  |
 * | brake      | uint8_t  | 4            | 4      | Brake command           |
 * | throttle   | uint8_t  | 4            | 8      | Throttle command        |
 * | emergency  | uint8_t  | 4            | 12     | Set emergency state     |
 * 
 * 
 * Status message
 * --------------
 * 
 * | Field       | Type     | Size (bytes) | Offset | Description                |
 * |-------------|----------|--------------|--------|----------------------------|
 * | stwheel_err | uint8_t  | 4            | 0      | Steering wheel error code  |
 * | brake_err   | uint8_t  | 4            | 4      | Brake error code           |
 * | throttle_err| uint8_t  | 4            | 8      | Throttle error code        |
 * | global_err  | uint8_t  | 4            | 12     | Global error code          |
 *  
 * 
 */

#ifndef GOKART_MSGS_H
#define GOKART_MSGS_H

#include "data_serialization.h"

namespace DataSerialization
{

  class GoKartCommand : public Message
  {
    public:
      Int8 stwheel;
      UInt8 brake;
      UInt8 throttle;
      UInt8 emergency;

      virtual uint8_t serialize(uint8_t *outbuffer) const
      {
        uint8_t offset = 0U;
        offset += this->stwheel.serialize(outbuffer + offset);
        offset += this->brake.serialize(outbuffer + offset);
        offset += this->throttle.serialize(outbuffer + offset);
        offset += this->emergency.serialize(outbuffer + offset);
        return offset;
      }

      virtual uint8_t deserialize(uint8_t *inbuffer)
      {
        uint8_t offset = 0U;
        offset += this->stwheel.deserialize(inbuffer + offset);
        offset += this->brake.deserialize(inbuffer + offset);
        offset += this->throttle.deserialize(inbuffer + offset);
        offset += this->emergency.deserialize(inbuffer + offset);
        return offset;
      } 
  };


  class GoKartStatus : public Message
  {
    public:
      UInt8 stwheel_err;
      UInt8 brake_err;
      UInt8 throttle_err;
      UInt8 global_err;

      virtual uint8_t serialize(uint8_t *outbuffer) const
      {
        uint8_t offset = 0U;
        offset += this->stwheel_err.serialize(outbuffer + offset);
        offset += this->brake_err.serialize(outbuffer + offset);
        offset += this->throttle_err.serialize(outbuffer + offset);
        offset += this->global_err.serialize(outbuffer + offset);
        return offset;
      }

      virtual uint8_t deserialize(uint8_t *inbuffer)
      {
        uint8_t offset = 0U;
        offset += this->stwheel_err.deserialize(inbuffer + offset);
        offset += this->brake_err.deserialize(inbuffer + offset);
        offset += this->throttle_err.deserialize(inbuffer + offset);
        offset += this->global_err.deserialize(inbuffer + offset);
        return offset;
      } 
  };

}

#endif
