#include "rainbows.h"
#include "basics.h"
#include "../util/colors.h"

// Taken from Adafruit NeoPixel strandtest example

void tickRainbowCircle(uint32_t framebuffer[], AnimState *state) {
  int firstPixelHue = state->frame_count * 256;
  for(int i=0; i < state->led_count; i++) {
    // Offset pixel hue by an amount to make one full revolution of the
    // color wheel (range of 65536) along the length of the strip
    int pixelHue = firstPixelHue + (i * 65536L / state->led_count);
    framebuffer[i] = wheel(pixelHue);
  }
}

void tickRainbowTheaterChase(uint32_t framebuffer[], AnimState *state) {
  int firstPixelHue = state->frame_count * 256;
  tickOff(framebuffer, state);
  for(int c=((state->frame_count >> 2) % 3); c < state->led_count; c += 3) {
    // hue of pixel 'c' is offset by an amount to make one full
    // revolution of the color wheel (range 65536) along the length
    int      hue   = firstPixelHue + c * 65536L / state->led_count;
    uint32_t color = wheel(hue);
    framebuffer[c] = color;
  }
}
