#include "./colors.h"
#include "../core/driver.h"

uint32_t dim(uint32_t pixel, uint8_t amount) {
  double red   = (pixel >> 16) & 0xFF;
  double green = (pixel >> 8) & 0xFF;
  double blue  = pixel & 0xFF;

  red   *= amount / 256.0;
  green *= amount / 256.0;
  blue  *= amount / 256.0;

  return strip.Color(red, green, blue);
}

uint8_t sine8(uint8_t angle) {
  return strip.sine8(angle);
}

uint32_t wheel(int pos) {
  return strip.gamma32(strip.ColorHSV(pos));
}

uint32_t color(uint8_t red, uint8_t blue, uint8_t green) {
  return strip.gamma32(strip.Color(red, green, blue));
}
