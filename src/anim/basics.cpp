#include "basics.h"

void tickOff(uint32_t framebuffer[], AnimState *state) {
  memset(framebuffer, 0, sizeof(uint32_t) * state->led_count);
}

void tickSolid(uint32_t framebuffer[], AnimState *state) {
  for (uint8_t i = 0; i < state->led_count; ++i) {
    framebuffer[i] = state->color;
  }
}
