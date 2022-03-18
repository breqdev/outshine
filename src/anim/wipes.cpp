#include "wipes.h"
#include "basics.h"
#include "../util/colors.h"

void tickColorWipeRate(uint32_t framebuffer[], AnimState *state, uint8_t rate) {
  for (uint8_t i = state->led_index; i < state->led_index + rate; ++i) {
    framebuffer[i % state->led_count] = state->color;
  }
}

void tickColorWipe(uint32_t framebuffer[], AnimState *state) {
  tickColorWipeRate(framebuffer, state, 1);
}

void tickFastColorWipe(uint32_t framebuffer[], AnimState *state) {
  tickColorWipeRate(framebuffer, state, 5);
}

void tickLarsonScanner(uint32_t framebuffer[], AnimState *state) {
  uint8_t scan_index = (state->cycles_count & 0b1)
    ? state->led_index
    : (state->led_count - state->led_index);

  if (scan_index < 3) {
    scan_index = 3;
  }
  if (scan_index + 3 >= state->led_count) {
    scan_index = state->led_count - 4;
  }

  tickOff(framebuffer, state);

  framebuffer[scan_index - 3] = dim(state->color, 128);
  framebuffer[scan_index - 2] = dim(state->color, 192);
  framebuffer[scan_index - 1] = dim(state->color, 255);
  framebuffer[scan_index + 0] = dim(state->color, 255);
  framebuffer[scan_index + 1] = dim(state->color, 255);
  framebuffer[scan_index + 2] = dim(state->color, 192);
  framebuffer[scan_index + 3] = dim(state->color, 128);
}

void tickInvertedLarsonScanner(uint32_t framebuffer[], AnimState *state) {
  uint8_t scan_index = (state->cycles_count & 0b1)
    ? state->led_index
    : (state->led_count - state->led_index);

  if (scan_index < 3) {
    scan_index = 3;
  }
  if (scan_index + 3 >= state->led_count) {
    scan_index = state->led_count - 4;
  }

  tickSolid(framebuffer, state);

  framebuffer[scan_index - 3] = dim(state->color, 128);
  framebuffer[scan_index - 2] = dim(state->color, 64);
  framebuffer[scan_index - 1] = dim(state->color, 0);
  framebuffer[scan_index + 0] = dim(state->color, 0);
  framebuffer[scan_index + 1] = dim(state->color, 0);
  framebuffer[scan_index + 2] = dim(state->color, 64);
  framebuffer[scan_index + 3] = dim(state->color, 128);
}

void tickCircularScanner(uint32_t framebuffer[], AnimState *state) {
  tickOff(framebuffer, state);

  framebuffer[(state->led_index + 0) % state->led_count] = dim(state->color, 128);
  framebuffer[(state->led_index + 1) % state->led_count] = dim(state->color, 192);
  framebuffer[(state->led_index + 2) % state->led_count] = dim(state->color, 255);
  framebuffer[(state->led_index + 3) % state->led_count] = dim(state->color, 255);
  framebuffer[(state->led_index + 4) % state->led_count] = dim(state->color, 255);
  framebuffer[(state->led_index + 5) % state->led_count] = dim(state->color, 192);
  framebuffer[(state->led_index + 6) % state->led_count] = dim(state->color, 128);
}

void tickInvertedCircularScanner(uint32_t framebuffer[], AnimState *state) {
  tickSolid(framebuffer, state);

  framebuffer[(state->led_index + 0) % state->led_count] = dim(state->color, 128);
  framebuffer[(state->led_index + 1) % state->led_count] = dim(state->color, 64);
  framebuffer[(state->led_index + 2) % state->led_count] = dim(state->color, 0);
  framebuffer[(state->led_index + 3) % state->led_count] = dim(state->color, 0);
  framebuffer[(state->led_index + 4) % state->led_count] = dim(state->color, 0);
  framebuffer[(state->led_index + 5) % state->led_count] = dim(state->color, 64);
  framebuffer[(state->led_index + 6) % state->led_count] = dim(state->color, 128);
}
