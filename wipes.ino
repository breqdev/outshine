void tickColorWipe(uint8_t rate) {
  for (uint8_t i = led_index; i < led_index + rate; ++i) {
    framebuffer[i % LED_COUNT] = active_color;
  }
}

void tickLarsonScanner(bool invert) {
  uint8_t scan_index = (cycles_count & 0b1) ? led_index : (LED_COUNT - led_index);
  if (scan_index < 3) {
    scan_index = 3;
  }
  if (scan_index + 3 >= LED_COUNT) {
    scan_index = LED_COUNT - 4;
  }

  if (invert) {
    tickSolid();

    framebuffer[scan_index - 3] = dim(active_color, 128);
    framebuffer[scan_index - 2] = dim(active_color, 64);
    framebuffer[scan_index - 1] = dim(active_color, 0);
    framebuffer[scan_index + 0] = dim(active_color, 0);
    framebuffer[scan_index + 1] = dim(active_color, 0);
    framebuffer[scan_index + 2] = dim(active_color, 64);
    framebuffer[scan_index + 3] = dim(active_color, 128);
  } else {
    tickOff();

    framebuffer[scan_index - 3] = dim(active_color, 128);
    framebuffer[scan_index - 2] = dim(active_color, 192);
    framebuffer[scan_index - 1] = dim(active_color, 255);
    framebuffer[scan_index + 0] = dim(active_color, 255);
    framebuffer[scan_index + 1] = dim(active_color, 255);
    framebuffer[scan_index + 2] = dim(active_color, 192);
    framebuffer[scan_index + 3] = dim(active_color, 128);
  }
}
