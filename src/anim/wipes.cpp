#include "wipes.h"
#include "basics.h"
#include "../util/colors.h"

void tickColorWipeRate(uint32_t framebuffer[], AnimState *state, uint8_t rate) {
  for (uint8_t i = state->led_index; i < state->led_index + rate; ++i) {
    framebuffer[i % state->led_count] = positional(state, i % state->led_count);
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

  for (int8_t offset = -3; offset <= 3; ++offset) {
    uint8_t dimTo;
    if (abs(offset) <= 1) {
      dimTo = 255;
    } else {
      dimTo = 255 - (abs(offset) - 1) * 64;
    }

    framebuffer[scan_index + offset] = dim(
      positional(state, scan_index + offset), dimTo);
  }
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

  for (int8_t offset = -3; offset <= 3; ++offset) {
    uint8_t dimTo;
    if (abs(offset) <= 1) {
      dimTo = 0;
    } else {
      dimTo = (abs(offset) - 1) * 64;
    }

    framebuffer[scan_index + offset] = dim(
      positional(state, scan_index + offset), dimTo);
  }
}

void tickCircularScanner(uint32_t framebuffer[], AnimState *state) {
  tickOff(framebuffer, state);

  const uint8_t dimTable[] = {128, 192, 255, 255, 255, 192, 128};

  for (int8_t offset = 0; offset <= 6; ++offset) {
    uint8_t dimTo = dimTable[offset];
    uint8_t index = (state->led_index + offset) % state->led_count;
    uint32_t color = positional(state, index);
    framebuffer[index] = dim(color, dimTo);
  }
}

void tickInvertedCircularScanner(uint32_t framebuffer[], AnimState *state) {
  tickSolid(framebuffer, state);

  const uint8_t dimTable[] = {128, 64, 0, 0, 0, 64, 128};

  for (int8_t offset = 0; offset <= 6; ++offset) {
    uint8_t dimTo = dimTable[offset];
    uint8_t index = (state->led_index + offset) % state->led_count;
    uint32_t color = positional(state, index);
    framebuffer[index] = dim(color, dimTo);
  }
}
