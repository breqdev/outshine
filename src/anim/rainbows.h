#ifndef RAINBOWS_H
#define RAINBOWS_H

#include <Arduino.h>
#include "../core/animation.h"

void tickRainbowCircle(uint32_t framebuffer[], AnimState *state);
void tickRainbowTheaterChase(uint32_t framebuffer[], AnimState *state);

#endif
