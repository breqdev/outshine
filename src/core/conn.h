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

struct ConnState {
  // Whether a transaction is underway.
  bool transaction;

  // The currently selected animation ID.
  uint8_t animation;

  // The currently selected colors.
  uint32_t colors[16];

  // The number of active colors.
  uint8_t color_count;

  // The color currently being recieved.
  uint32_t draft_color;
};

void initPeripherals(AnimState *state, ConnState *conn);

void handlePeripherals(AnimState *state, ConnState *conn);

void handleMessageByte(uint8_t message, AnimState *state, ConnState *conn);

#endif
