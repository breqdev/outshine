void tickColorWipe(uint8_t rate) {
  for (uint8_t i = led_index; i < led_index + rate; ++i) {
    framebuffer[i % LED_COUNT] = active_color;
  }
}

void tickLarsonScanner(bool invert) {
  if (invert) {
    tickSolid();

    framebuffer[(led_index + 0) % LED_COUNT] = dim(active_color, 128);
    framebuffer[(led_index + 1) % LED_COUNT] = dim(active_color, 64);
    framebuffer[(led_index + 2) % LED_COUNT] = dim(active_color, 0);
    framebuffer[(led_index + 3) % LED_COUNT] = dim(active_color, 0);
    framebuffer[(led_index + 4) % LED_COUNT] = dim(active_color, 0);
    framebuffer[(led_index + 5) % LED_COUNT] = dim(active_color, 64);
    framebuffer[(led_index + 6) % LED_COUNT] = dim(active_color, 128);
  } else {
    tickOff();

    framebuffer[(led_index + 0) % LED_COUNT] = dim(active_color, 128);
    framebuffer[(led_index + 1) % LED_COUNT] = dim(active_color, 192);
    framebuffer[(led_index + 2) % LED_COUNT] = dim(active_color, 255);
    framebuffer[(led_index + 3) % LED_COUNT] = dim(active_color, 255);
    framebuffer[(led_index + 4) % LED_COUNT] = dim(active_color, 255);
    framebuffer[(led_index + 5) % LED_COUNT] = dim(active_color, 192);
    framebuffer[(led_index + 6) % LED_COUNT] = dim(active_color, 128);
  }
}
