#include "brake.h"
#include "steering_wheel.h" 
#include "throttle.h" 
#include "ICommunication.h"
#include "gokart_msgs.h" 

// Dynamixel protocol
#define GOKART_DXL_BAUDRATE 200000
#define GOKART_DXL_CTRL_PIN 2

// Actuators IDs
#define GOKART_BRAKE_ID 2
#define GOKART_THROTTLE_ID 3
#define GOKART_STEERINGWHEEL_ID 4




namespace GoKart
{
  class GoKartHW
  {
    public:
      GoKartHW(DynamixelClass& dxl);

      void init();
      
      uint8_t getErrorCode();

      void setEmergencyState();

      void setRF();

      //void setSerial();

    private:
      DynamixelClass* dxl_;

    public:
      ICommunication* com_;
      Brake brake;
      Throttle thr;
      SteeringWheel sw;

  };
}



