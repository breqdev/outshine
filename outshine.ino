#include "config.h"
#include "src/core/animation.h"
#include "src/core/conn.h"
#include "src/core/driver.h"
#include "src/anim/mapping.h"

// Select required interface libraries

AnimState state = {
  0x21, // fade wipe animation
  0x00, // start at LED 0
  LED_COUNT,
  0, // 0 cycles elapsed
  0, // 0 frames elapsed
  0x00FF0000, // red
};

ConnState conn = {
  false, // no transaction
  0xFF, // no animation selected
  {0}, // no colors selected
  0x00, // no colors selected
  0x00, // no color draft
};

uint32_t framebuffer[LED_COUNT] = { 0 };

void setup() {
  initMapping();
  initStrip();
  initPeripherals(&state, &conn);
}


void loop() {
  handlePeripherals(&state, &conn);

  state.led_index += 1;
  if (state.led_index >= state.led_count) {
    state.led_index = 0;
    state.cycles_count += 1;
  }

  state.frame_count += 1;

  void (*animation)(uint32_t[], AnimState*) = animations[state.animation];

  if (animation == nullptr) {
    animation = tickOff;
  }

  animation(framebuffer, &state);

  blit(framebuffer);

  delay(20);
}
