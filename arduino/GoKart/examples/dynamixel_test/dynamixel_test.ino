#include <DynamixelSerial1.h>

// Dynamixel protocol
#define GOKART_DXL_BAUDRATE 1000000
#define GOKART_DXL_CTRL_PIN 2

#define MOTOR_ID 1

int voltage, position; 

void setup()
{
  // Begin Serial Comunication
  Serial.begin(57600);
  // Inicialize the servo at 200k and Pin Control 2
  Dynamixel.begin(GOKART_DXL_BAUDRATE, GOKART_DXL_CTRL_PIN);
  Dynamixel.ping(MOTOR_ID);
  Dynamixel.ping(MOTOR_ID);
  delay(500);
  Dynamixel.ping(MOTOR_ID);
  Dynamixel.ping(MOTOR_ID);
  int result = Dynamixel.ping(MOTOR_ID);
  if (result == -1)
  {
    Serial.print("FAIL ON "); Serial.println(MOTOR_ID);
  }
  else
  {
    Serial.print("Found at "); Serial.println(MOTOR_ID);
  }
  Serial.print("Error CW "); Serial.println(Dynamixel.setCWLimit(MOTOR_ID, 100));
  Serial.print("Error CCW "); Serial.println(Dynamixel.setCCWLimit(MOTOR_ID, 4000));
  delay(30);

  Serial.print("CCW Limit: "); Serial.println(Dynamixel.readCCWLimit(MOTOR_ID));
  Serial.print("CW Limit: "); Serial.println(Dynamixel.readCWLimit(MOTOR_ID));
  
  delay(1000);
  Dynamixel.move(MOTOR_ID, 1500);
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