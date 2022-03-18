#ifndef WIPES_H
#define WIPES_H

#include <Arduino.h>
#include "../core/animation.h"

void tickColorWipe(uint32_t framebuffer[], AnimState *state);
void tickFastColorWipe(uint32_t framebuffer[], AnimState *state);
void tickLarsonScanner(uint32_t framebuffer[], AnimState *state);
void tickInvertedLarsonScanner(uint32_t framebuffer[], AnimState *state);
void tickCircularScanner(uint32_t framebuffer[], AnimState *state);
void tickInvertedCircularScanner(uint32_t framebuffer[], AnimState *state);

#endif
