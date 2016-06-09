#ifndef GOKART_DEBUG_H
#define GOKART_DEBUG_H

#include "Arduino.h"

#define DEBUG_GOKART
#ifdef DEBUG_GOKART
#define DEBUG_PRINT(...) Serial.print(__VA_ARGS__)
#define DEBUG_PRINTLN(...) Serial.println(__VA_ARGS__)
#else
#define DEBUG_PRINT(...)
#define DEBUG_PRINTLN(...)
#endif


#endif

