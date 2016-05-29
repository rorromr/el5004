#include <DynamixelSerial1.h>

// Dynamixel protocol
#define GOKART_DXL_BAUDRATE 200000
#define GOKART_DXL_CTRL_PIN 2

#define MOTOR_ID 2

int voltage, position; 

void setup()
{
  // Begin Serial Comunication
  Serial.begin(9600);
  // Inicialize the servo at 200k and Pin Control 2
  Dynamixel.begin(GOKART_DXL_BAUDRATE, GOKART_DXL_CTRL_PIN);
  delay(1000);
}

void loop()
{
  voltage = Dynamixel.readVoltage(MOTOR_ID);  // Get voltage
  position = Dynamixel.readPosition(MOTOR_ID);// Get position 
  // Print values
  Serial.print(voltage);
  Serial.print(" | ");
  Serial.println(position);
  
  delay(1000);
}
