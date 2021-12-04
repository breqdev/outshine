void tickTheaterChase() {
  tickOff();

  for (uint8_t i = ((tick_index >> 2) % 3); i < LED_COUNT; i += 3) {
    framebuffer[i] = active_color;
  }
}

void tickRunningLights() {
  for (uint8_t i = 0; i < LED_COUNT; ++i) {
    uint8_t brightness = strip.sine8(((led_index + i) % 15) * 256 / 15.0);
    framebuffer[i] = dim(active_color, brightness);
  }
}

void tickSparkle(bool inverted, uint8_t rate) {
  if (tick_index & (rate - 1)) {
    return;
  }
  
  if (inverted) {
    tickSolid();
  } else {
    tickOff();
  }

  for (uint8_t i = 0; i <= (LED_COUNT >> 4); ++i) {
    uint8_t rand_idx = random(LED_COUNT);
    framebuffer[rand_idx] = inverted ? 0 : active_color;
  }
}
