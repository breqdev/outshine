#include "twinkles.h"
#include "basics.h"
#include "../util/colors.h"

void tickTheaterChase(uint32_t framebuffer[], AnimState *state) {
  tickOff(framebuffer, state);

  for (uint8_t i = ((state->frame_count >> 2) % 3); i < state->led_count; i += 3) {
    framebuffer[i] = state->color;
  }
}

void tickRunningLights(uint32_t framebuffer[], AnimState *state) {
  for (uint8_t i = 0; i < state->led_count; ++i) {
    uint8_t brightness = sine8(((state->led_index + i) % 15) * 256 / 15.0);
    framebuffer[i] = dim(state->color, brightness);
  }
}

void tickSparkle(uint32_t framebuffer[], AnimState *state, bool inverted, uint8_t rate) {
  if (state->frame_count & (rate - 1)) {
    return;
  }

  if (inverted) {
    tickSolid(framebuffer, state);
  } else {
    tickOff(framebuffer, state);
  }

  for (uint8_t i = 0; i <= (state->led_count >> 4); ++i) {
    uint8_t rand_idx = random(state->led_count);
    framebuffer[rand_idx] = inverted ? 0 : state->color;
  }
}

void tickRandomSparkle(uint32_t framebuffer[], AnimState *state) {
  tickSparkle(framebuffer, state, false, 4);
}

void tickInvertedRandomSparkle(uint32_t framebuffer[], AnimState *state) {
  tickSparkle(framebuffer, state, true, 4);
}

void tickPaparazzi(uint32_t framebuffer[], AnimState *state) {
  tickSparkle(framebuffer, state, false, 1);
}
