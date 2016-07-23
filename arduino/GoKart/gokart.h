#include "brake.h"
#include "steering_wheel.h"
#include "throttle.h"
#include "comm_interface.h"
#include "rf_interface.h"
#include "serial_interface.h"
#include "gokart_msgs.h"
#include "lcd.h"
#include "Arduino.h"

// Dynamixel protocol
#define GOKART_DXL_BAUDRATE 1000000
#define GOKART_DXL_CTRL_PIN 4

// Actuators IDs
#define GOKART_BRAKE_ID 3
#define GOKART_THROTTLE_ID 2
#define GOKART_STEERINGWHEEL_ID 1

#define GOKART_TIMESTAMP_TIMEOUT 1000

namespace GoKart
{
  class GoKartHW
  {
    public:
      GoKartHW(DynamixelClass& dxl, CommInterface &com);

      bool init();

      uint8_t getErrorCode();

      void setEmergencyState();

      void setCommunication(CommInterface &com);

      void updateCommand();

      void setCommand();

      inline bool isEmergency()
      {
        return (bool) cmd_.emergency.data;
      }

      void update();

      void printCommand();

      void printCommandLCD();

      //void setSerial();

    private:
      DynamixelClass* dxl_;

    public:
      CommInterface* com_;
      DataSerialization::GoKartCommand cmd_;
      Brake brake;
      Throttle thr;
      SteeringWheel sw;
      LCD lcd;
      uint8_t status_;

  };
}
