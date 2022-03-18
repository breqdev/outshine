#ifndef CONN_H
#define CONN_H

#include "../core/animation.h"
#include "../../config.h"

#if ENABLE_I2C
  #include <Wire.h>
#endif

#if ENABLE_BLE
  #include <bluefruit.h>

  // BLE Services
  BLEDfu bledfu; // DFU Service
  BLEDis bledis; // Device Information Service
  BLEUart bleuart; // UART over BLE Service
  BLEBas blebas; // Battery Service
#endif

void initConn(AnimState *state);

void handleCommands(AnimState *state);

#endif
