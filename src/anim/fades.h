#ifndef FADES_H
#define FADES_H

#include <Arduino.h>
#include "../core/animation.h"

void tickFadeInOut(uint32_t framebuffer[], AnimState *state);
void tickWipeFade(uint32_t framebuffer[], AnimState *state);

#endif
