#ifndef ANIMATION_H
#define ANIMATION_H

#include <Arduino.h>


struct AnimState {
  // The currently active animation ID.
  uint8_t animation;

  // The position of the "active" LED in the animation.
  // (The meaning of this is animation-dependent.)
  uint8_t led_index;

  // The number of LEDs in the strip.
  uint8_t led_count;

  // The number of cycles that have elapsed.
  // (complete runs of the active LED index through the strip)
  uint16_t cycles_count;

  // The number of frames that have elapsed.
  uint16_t frame_count;

  // The current active color of the animation.
  // (The meaning of this is animation-dependent.)
  uint32_t color;
};

#endif
