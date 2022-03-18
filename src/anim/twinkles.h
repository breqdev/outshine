#ifndef TWINKLES_H
#define TWINKLES_H

#include <Arduino.h>
#include "../core/animation.h"

void tickTheaterChase(uint32_t framebuffer[], AnimState *state);
void tickRunningLights(uint32_t framebuffer[], AnimState *state);
void tickRandomSparkle(uint32_t framebuffer[], AnimState *state);
void tickInvertedRandomSparkle(uint32_t framebuffer[], AnimState *state);
void tickPaparazzi(uint32_t framebuffer[], AnimState *state);

#endif
