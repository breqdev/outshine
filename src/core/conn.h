#ifndef CONN_H
#define CONN_H

#include "../core/animation.h"
#include "../../config.h"

#if ENABLE_I2C
  #include <Wire.h>
#endif

#if ENABLE_BLE
  #include <bluefruit.h>
#endif

void initConn(AnimState *state);

void handleCommands(AnimState *state);

#endif
