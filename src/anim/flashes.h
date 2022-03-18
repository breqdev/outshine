#ifndef FLASHES_H
#define FLASHES_H

#include <Arduino.h>
#include "../core/animation.h"

void tickFlash(uint32_t framebuffer[], AnimState *state);
void tickLongFlash(uint32_t framebuffer[], AnimState *state);
void tickFastFlash(uint32_t framebuffer[], AnimState *state);
void tickStrobe(uint32_t framebuffer[], AnimState *state);
void tickComplexFlash(uint32_t framebuffer[], AnimState *state);

#endif
