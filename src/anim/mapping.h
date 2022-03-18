#ifndef MAPPING_H
#define MAPPING_H

#include <Arduino.h>
#include "../core/animation.h"

#include "basics.h"
#include "flashes.h"
#include "fades.h"
#include "wipes.h"
#include "twinkles.h"
#include "rainbows.h"

void (*animations[0x100])(uint32_t framebuffer[], AnimState *state);

void initMapping() {
  // 0x0X - Basics
  animations[0x00] = tickOff;
  animations[0x01] = tickSolid;

  // 0x1X - Flashes
  animations[0x10] = tickFlash;
  animations[0x11] = tickLongFlash;
  animations[0x12] = tickFastFlash;
  animations[0x13] = tickStrobe;
  animations[0x14] = tickComplexFlash;

  // 0x2X - Fades
  animations[0x20] = tickFadeInOut;
  animations[0x21] = tickWipeFade;

  // 0x3X - Wipes
  animations[0x30] = tickColorWipe;
  animations[0x31] = tickFastColorWipe;
  animations[0x32] = tickLarsonScanner;
  animations[0x33] = tickInvertedLarsonScanner;
  animations[0x34] = tickCircularScanner;
  animations[0x35] = tickInvertedCircularScanner;

  // 0x4X - Twinkles
  animations[0x40] = tickTheaterChase;
  animations[0x41] = tickRunningLights;
  animations[0x42] = tickRandomSparkle;
  animations[0x43] = tickInvertedRandomSparkle;
  animations[0x44] = tickPaparazzi;

  // 0x5X - Rainbows
  animations[0x50] = tickRainbowCircle;
  animations[0x51] = tickRainbowTheaterChase;
}

#endif
