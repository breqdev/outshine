#include "driver.h"

#ifdef NEOPXL8
  int8_t pins[] = {LED_PIN, -1, -1, -1, -1, -1, -1, -1};
  Adafruit_NeoPXL8 strip(LED_COUNT, pins, NEO_GRB);
#endif

#ifdef ZERODMA
  Adafruit_NeoPixel_ZeroDMA strip(LED_COUNT, LED_PIN, NEO_GRB);
#endif

#ifdef NEOPIXEL
  Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);
#endif

void initStrip() {
  strip.begin();
  strip.show();
  strip.setBrightness(LED_BRIGHTNESS);
}

void blit(uint32_t framebuffer[]) {
  for (uint8_t i = 0; i < LED_COUNT; ++i) {
    strip.setPixelColor(i, framebuffer[i]);
  }
  strip.show();
}
