#define __ASSERT_USE_STDERR
#include <assert.h>

#include "DynamixelSerial1.h"
#include "gokart.h"

DataSerialization::GoKartCommand cmd1, cmd2;
DataSerialization::GoKartStatus status;

uint8_t buffer[10];

union {
  int8_t real;
  uint8_t base;
} u_data;

void setup()
{
  Serial.begin(115200);
  
}

void loop()
{
  Serial.println("TEST: Deserialize Status");
  // Set buffer
  buffer[0]=10;
  buffer[1]=15;
  buffer[2]=8;
  buffer[3]=12;
  assert(status.deserialize(buffer) == 4);
  assert(status.stwheel_err.data == 10);
  assert(status.brake_err.data == 15);
  assert(status.throttle_err.data == 8);
  assert(status.global_err.data == 12);
  Serial.println("  [OK]");

  Serial.println("TEST: Serialize Status");
  // Set status
  status.stwheel_err.data = 17;
  status.brake_err.data = 26;
  status.throttle_err.data = 6;
  status.global_err.data = 248;
  assert(status.serialize(buffer) == 4);
  assert(buffer[0] == 17);
  assert(buffer[1] == 26);
  assert(buffer[2] == 6);
  assert(buffer[3] == 248);
  Serial.println("  [OK]");

  Serial.println("TEST: Command");
  cmd1.stwheel.data = -10;
  cmd1.brake.data = 26;
  cmd1.throttle.data = 6;
  cmd1.emergency.data = 248;
  assert(cmd1.serialize(buffer) == 4);
  assert(cmd2.deserialize(buffer) == 4);
  assert(cmd2.stwheel.data = -10);
  assert(cmd2.brake.data = 26);
  assert(cmd2.throttle.data = 6);
  assert(cmd2.emergency.data = 248);
   
  delay(1000);
}


void __assert(const char *__func, const char *__file, int __lineno, const char *__sexp) {
  // transmit diagnostic informations through serial link.
  Serial.println(__func);
  Serial.println(__file);
  Serial.println(__lineno, DEC);
  Serial.println(__sexp);
  Serial.flush();
  // abort program execution.
  abort();
}
