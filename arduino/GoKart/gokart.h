#include "brake.h"
#include "steering_wheel.h"
#include "throttle.h"
#include "ICommunication.h"
#include "rf_interface.h"
#include "gokart_msgs.h"
#include "Arduino.h"

// Dynamixel protocol
#define GOKART_DXL_BAUDRATE 1000000
#define GOKART_DXL_CTRL_PIN 2

// Actuators IDs
#define GOKART_BRAKE_ID 2
#define GOKART_THROTTLE_ID 3
#define GOKART_STEERINGWHEEL_ID 1  //era 4 pero para probar le puse 1




namespace GoKart
{
  class GoKartHW
  {
    public:
      GoKartHW(DynamixelClass& dxl, ICommunication &com);

      void init();

      uint8_t getErrorCode();

      void setEmergencyState();

      void setCommunication(ICommunication &com);

      void updateCommand();

      void printCommand();

      //void setSerial();

    private:
      DynamixelClass* dxl_;

    public:
      ICommunication* com_;
      DataSerialization::GoKartCommand cmd_;
      Brake brake;
      Throttle thr;
      SteeringWheel sw;

  };
}
