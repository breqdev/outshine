void tickOff() {
  memset(framebuffer, 0, sizeof(framebuffer));
}

void tickSolid() {
  for (uint8_t i = 0; i < LED_COUNT; ++i) {
    framebuffer[i] = active_color;
  }
}
