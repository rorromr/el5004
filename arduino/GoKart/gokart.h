#include "brake.h"
#include "steering_wheel.h" 
#include "throttle.h" 
#include "rf_interface.h" 

// Dynamixel protocol
#define GOKART_DXL_BAUDRATE 200000
#define GOKART_DXL_CTRL_PIN 2

// Actuators IDs
#define GOKART_BRAKE_ID 2
#define GOKART_THROTTLE_ID 3
#define GOKART_STEERINGWHEEL_ID 4

// RF
#define GOKART_RF_CH_NUM 3
#define GOKART_RF_CH1_PIN 6
#define GOKART_RF_CH2_PIN 7
#define GOKART_RF_CH3_PIN 8


namespace GoKart
{
  class GoKartHW
  {
    public:
      GoKartHW(DynamixelClass& dxl);

      void init();
      
      uint8_t getErrorCode();

      void setEmergencyState();

    private:
      DynamixelClass* dxl_;

    public:
      RFInterface rf;
      Brake brake;
      Throttle thr;
      SteeringWheel sw;

  };
}



