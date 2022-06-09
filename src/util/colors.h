#ifndef COLORS_H
#define COLORS_H

#include <Arduino.h>
#include "../core/animation.h"

uint32_t dim(uint32_t pixel, uint8_t amount);
uint8_t sine8(uint8_t angle);
uint32_t wheel(int pos);
uint32_t color(uint8_t red, uint8_t green, uint8_t blue);
uint32_t positional(AnimState* state, uint8_t position);

#endif
