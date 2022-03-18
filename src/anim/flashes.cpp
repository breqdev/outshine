#include "fades.h"
#include "basics.h"

void tickFlashRate(uint32_t framebuffer[], AnimState *state, uint8_t period, uint8_t highCycle) {
  if ((state->frame_count & (period - 1)) < highCycle) {
    tickSolid(framebuffer, state);
  } else {
    tickOff(framebuffer, state);
  }
}

void tickFlash(uint32_t framebuffer[], AnimState *state) {
  tickFlashRate(framebuffer, state, 64, 32);
}

void tickLongFlash(uint32_t framebuffer[], AnimState *state) {
  tickFlashRate(framebuffer, state, 64, 48);
}

void tickFastFlash(uint32_t framebuffer[], AnimState *state) {
  tickFlashRate(framebuffer, state, 32, 16);
}

void tickStrobe(uint32_t framebuffer[], AnimState *state) {
  tickFlashRate(framebuffer, state, 8, 4);
}

void tickComplexFlash(uint32_t framebuffer[], AnimState *state) {
  if ((state->frame_count & 63) < 16) {
    tickSolid(framebuffer, state);
  } else {
    if ((state->frame_count & 15) < 8) {
      tickSolid(framebuffer, state);
    } else {
      tickOff(framebuffer, state);
    }
  }
}
