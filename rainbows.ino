// Taken from Adafruit NeoPixel strandtest example

void tickRainbowCircle() {
  int firstPixelHue = tick_index * 256;
  for(int i=0; i < LED_COUNT; i++) { // For each pixel in strip...
    // Offset pixel hue by an amount to make one full revolution of the
    // color wheel (range of 65536) along the length of the strip
    // (strip.numPixels() steps):
    int pixelHue = firstPixelHue + (i * 65536L / LED_COUNT);
    // strip.ColorHSV() can take 1 or 3 arguments: a hue (0 to 65535) or
    // optionally add saturation and value (brightness) (each 0 to 255).
    // Here we're using just the single-argument hue variant. The result
    // is passed through strip.gamma32() to provide 'truer' colors
    // before assigning to each pixel:
    framebuffer[i] = strip.gamma32(strip.ColorHSV(pixelHue));
  }
}

// Rainbow-enhanced theater marquee. Pass delay time (in ms) between frames.
void tickRainbowTheaterChase() {
  int firstPixelHue = tick_index * 256;
  tickOff();
  for(int c=((tick_index >> 2) % 3); c < LED_COUNT; c += 3) {
    // hue of pixel 'c' is offset by an amount to make one full
    // revolution of the color wheel (range 65536) along the length
    // of the strip (strip.numPixels() steps):
    int      hue   = firstPixelHue + c * 65536L / LED_COUNT;
    uint32_t color = strip.gamma32(strip.ColorHSV(hue)); // hue -> RGB
    framebuffer[c] = color; // Set pixel 'c' to value 'color'
  }
}
