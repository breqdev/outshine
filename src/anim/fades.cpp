#include "fades.h"
#include "../util/colors.h"

void tickFadeInOut(uint32_t framebuffer[], AnimState *state) {
  uint8_t brightness = sine8(state->frame_count << 2);
  uint32_t pixel = dim(state->color, brightness);

  for (uint8_t i = 0; i < state->led_count; ++i) {
    framebuffer[i] = pixel;
  }
}

void tickWipeFade(uint32_t framebuffer[], AnimState *state) {
  for (uint8_t i = 0; i < state->led_count; ++i) {
    uint32_t pixel = framebuffer[i];

    framebuffer[i] = dim(pixel, 200);
  }
  framebuffer[state->led_index] = state->color;
}
