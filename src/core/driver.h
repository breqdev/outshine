#ifndef DRIVER_H
#define DRIVER_H

#include <Arduino.h>
#include "../../config.h"

#if defined(ARDUINO_ARCH_RP2040)
  #define NEOPXL8
// #elif defined(ARDUINO_ARCH_SAMD)
//   #define ZERODMA
#else
  #define NEOPIXEL
#endif


#ifdef NEOPXL8
  #include <Adafruit_NeoPXL8.h>

  extern Adafruit_NeoPXL8 strip;
#endif

#ifdef ZERODMA
  #include <Adafruit_NeoPixel_ZeroDMA.h>

  extern Adafruit_NeoPixel_ZeroDMA strip;
#endif

#ifdef NEOPIXEL
  #include <Adafruit_NeoPixel.h>

  extern Adafruit_NeoPixel strip;
#endif

void initStrip();
void blit(uint32_t framebuffer[]);

#endif
