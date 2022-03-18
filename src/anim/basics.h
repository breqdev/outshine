#ifndef BASICS_H
#define BASICS_H

#include <Arduino.h>
#include "../core/animation.h"

void tickOff(uint32_t framebuffer[], AnimState *state);
void tickSolid(uint32_t framebuffer[], AnimState *state);

#endif
