void tickFadeInOut() {
  uint8_t brightness = strip.sine8(tick_index << 2);
  uint32_t pixel = dim(active_color, brightness);

  for (uint8_t i = 0; i < LED_COUNT; ++i) {
    framebuffer[i] = pixel;
  }
}

void tickWipeFade() {
  for (uint8_t i = 0; i < LED_COUNT; ++i) {
    uint32_t pixel = framebuffer[i];
    
    framebuffer[i] = dim(pixel, 200);
  }
  framebuffer[led_index] = active_color;
}
