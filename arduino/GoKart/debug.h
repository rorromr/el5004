#ifdef DEBUG_GOKART

#ifndef GOKART_DEBUG_H
#define GOKART_DEBUG_H

#define __ASSERT_USE_STDERR
#include <assert.h>

#include "Arduino.h"

#ifdef DEBUG_GOKART
#define DEBUG_PRINT(...) Serial.print(__VA_ARGS__)
#define DEBUG_PRINTLN(...) Serial.println(__VA_ARGS__)
#else
#define DEBUG_PRINT(...)
#define DEBUG_PRINTLN(...)
#endif

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

#endif
#endif