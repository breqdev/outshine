#include "fades.h"
#include "../util/colors.h"

void tickFadeInOut(uint32_t framebuffer[], AnimState *state) {
  uint8_t brightness = sine8(state->frame_count << 2);

  for (uint8_t i = 0; i < state->led_count; ++i) {
    uint32_t color = positional(state, i);
    framebuffer[i] = dim(color, brightness);
  }
}

void tickWipeFade(uint32_t framebuffer[], AnimState *state) {
  for (uint8_t i = 0; i < state->led_count; ++i) {
    uint32_t pixel = framebuffer[i];

    framebuffer[i] = dim(pixel, 200);
  }
  framebuffer[state->led_index] = positional(state, state->led_index);
}
