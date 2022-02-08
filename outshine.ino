/*
          _      _                _          _            _       _     _          _             _
        /\ \   /\_\             /\ \       / /\         / /\    / /\  /\ \       /\ \     _    /\ \
       /  \ \ / / /         _   \_\ \     / /  \       / / /   / / /  \ \ \     /  \ \   /\_\ /  \ \
      / /\ \ \\ \ \__      /\_\ /\__ \   / / /\ \__   / /_/   / / /   /\ \_\   / /\ \ \_/ / // /\ \ \
     / / /\ \ \\ \___\    / / // /_ \ \ / / /\ \___\ / /\ \__/ / /   / /\/_/  / / /\ \___/ // / /\ \_\
    / / /  \ \_\\__  /   / / // / /\ \ \\ \ \ \/___// /\ \___\/ /   / / /    / / /  \/____// /_/_ \/_/
   / / /   / / // / /   / / // / /  \/_/ \ \ \     / / /\/___/ /   / / /    / / /    / / // /____/\
  / / /   / / // / /   / / // / /    _    \ \ \   / / /   / / /   / / /    / / /    / / // /\____\/
 / / /___/ / // / /___/ / // / /    /_/\__/ / /  / / /   / / /___/ / /__  / / /    / / // / /______
/ / /____\/ // / /____\/ //_/ /     \ \/___/ /  / / /   / / //\__\/_/___\/ / /    / / // / /_______\
\/_________/ \/_________/ \_\/       \_____\/   \/_/    \/_/ \/_________/\/_/     \/_/ \/__________/

 * OUTSHINE - LED Controller
 * Brooke Chalmers, 2021
 *
 * Handles receiving commands over I2C or UART
 * and displaying colors and animations on the LED strip.
 *
 * Commands contain 4 bytes:
 *
 * 3 bytes: Active Color
 *    1 byte: red channel
 *    1 byte: green channel
 *    1 byte: blue channel
 *
 * 1 byte: Active Animation
 *    0x0X -- Basics
 *      0x00: Off
 *      0x01: Solid Color
 *
 *    0x1X -- Flashes
 *      0x10: Basic Flash
 *      0x11: Long Flash (long period on, short period off)
 *      0x12: Fast Flash
 *      0x13: Strobe
 *      0x14: Complex Flash (short period on, then long period on)
 *
 *    0x2X -- Fades
 *      0x20: Basic Simultaneous Fade In/Out
 *      0x21: Wipe/Fade
 *
 *    0x3X -- Wipes
 *      0x30: Basic Color Wipe
 *      0x31: Fast Color Wipe
 *      0x32: Larson Scanner
 *      0x33: Inverted Larson Scanner
 *
 *    0x4X -- Twinkles
 *      0x40: Basic Theater Chase
 *      0x41: Running Lights / Wide Theater Chase
 *      0x42: Random Sparkle
 *      0x43: Inverted Random Sparkle / Snow Twinkles
 *      0x44: Paparazzi
 *
 *    0x5X -- Rainbows
 *      0x50: Rainbow Circle
 *      0x51: Rainbow Theater Chase
 *
 * CONFIGURATION
 *
 * ENABLE_UART     Enable operation over UART/serial.
 * ENABLE_I2C      Enable operation as an I2C slave.
 * I2C_ADDR        Address for operation as an I2C slave.
 *
 * LED_PIN         GPIO pin which the NeoPixels are connected to.
 * LED_COUNT       Number of LEDs connected to that pin.
 * LED_BRIGHTNESS  [0-255] Brightness of the entire LED strip.
 */

#define ENABLE_UART     1
#define ENABLE_I2C      1
#define I2C_ADDR        0x04

#define LED_PIN 26
#define LED_COUNT 20
#define LED_BRIGHTNESS  255



#include <Wire.h>

#ifdef ARDUINO_ARCH_RP2040
  #include <Adafruit_NeoPXL8.h>
#else
  #include <Adafruit_NeoPixel.h>
#endif


#ifdef ARDUINO_ARCH_RP2040
  int8_t pins[] = {LED_PIN, -1, -1, -1, -1, -1, -1, -1};
  Adafruit_NeoPXL8 strip(LED_COUNT, pins, NEO_GRB);
#else
  Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);
#endif

uint32_t framebuffer[LED_COUNT] = { 0 };
uint8_t led_index = 0;
uint8_t tick_index = 0;
uint32_t active_color = 0x00FF0000;

enum class Animation {
  off = 0x00,
  solid = 0x01,

  basicFlash = 0x10,
  longFlash = 0x11,
  fastFlash = 0x12,
  strobe = 0x13,
  complexFlash = 0x14,

  fadeInOut = 0x20,
  wipeFade = 0x21,

  colorWipe = 0x30,
  fastColorWipe = 0x31,
  larsonScanner = 0x32,
  invertedLarsonScanner = 0x33,

  theaterChase = 0x40,
  runningLights = 0x41,
  randomSparkle = 0x42,
  invertedRandomSparkle = 0x43,
  paparazzi = 0x44,

  rainbowCircle = 0x50,
  rainbowTheaterChase = 0x51,
};

Animation active_animation = Animation::wipeFade;

uint32_t dim(uint32_t pixel, uint8_t amount) {
  double red   = (pixel >> 16) & 0xFF;
  double green = (pixel >> 8) & 0xFF;
  double blue  = pixel & 0xFF;

  red   *= amount / 256.0;
  green *= amount / 256.0;
  blue  *= amount / 256.0;

  return strip.Color(red, green, blue);
}

void handleReceive(int bytes) {
  if (bytes != 4) {
    return; // malformed message
  }

  uint8_t red = Wire.read();
  uint8_t green = Wire.read();
  uint8_t blue = Wire.read();

  active_color = strip.gamma32(strip.Color(red, green, blue));

  // We handle the default case whenever we use this enum
  // Therefore, we don't need to enforce that it's a valid anim
  active_animation = (Animation)Wire.read();
}

void setup() {
  strip.begin();
  strip.show();
  strip.setBrightness(LED_BRIGHTNESS);

#if ENABLE_I2C
  Wire.begin(I2C_ADDR);
  Wire.onReceive(handleReceive);
#endif

#if ENABLE_UART
  Serial.begin(9600);
  Serial.setTimeout(100);
#endif
}

void blit() {
  for (uint8_t i = 0; i < LED_COUNT; ++i) {
    strip.setPixelColor(i, framebuffer[i]);
  }
  strip.show();
}




void tick() {
  led_index += 1;
  led_index %= LED_COUNT;

  tick_index += 1; // will rollover, it's OK

  switch(active_animation) {
    // BASICS
    case (Animation::off):
      tickOff();
      break;
    case (Animation::solid):
      tickSolid();
      break;

    // FLASHES
    case (Animation::basicFlash):
      tickFlash(64, 32);
      break;
    case (Animation::longFlash):
      tickFlash(64, 48);
      break;
    case (Animation::fastFlash):
      tickFlash(32, 16);
      break;
    case (Animation::strobe):
      tickFlash(8, 4);
      break;
    case (Animation::complexFlash):
      tickComplexFlash();
      break;

    // FADES
    case (Animation::fadeInOut):
      tickFadeInOut();
      break;
    case (Animation::wipeFade):
      tickWipeFade();
      break;

    // WIPES
    case (Animation::colorWipe):
      tickColorWipe(1);
      break;
    case (Animation::fastColorWipe):
      tickColorWipe(5);
      break;
    case (Animation::larsonScanner):
      tickLarsonScanner(false);
      break;
    case (Animation::invertedLarsonScanner):
      tickLarsonScanner(true);
      break;

    // TWINKLES
    case (Animation::theaterChase):
      tickTheaterChase();
      break;
    case (Animation::runningLights):
      tickRunningLights();
      break;
    case (Animation::randomSparkle):
      tickSparkle(false, 4);
      break;
    case (Animation::invertedRandomSparkle):
      tickSparkle(true, 4);
      break;
    case (Animation::paparazzi):
      tickSparkle(false, 1);
      break;


    // RAINBOWS
    case (Animation::rainbowCircle):
      tickRainbowCircle();
      break;
    case (Animation::rainbowTheaterChase):
      tickRainbowTheaterChase();
      break;


    default:
      tickOff();
  }

  blit();
}

void readSerialCommand() {
  while (Serial.available() > 1) {
    String command = Serial.readStringUntil('\n');

    if (command.length() < 4) {
      return;
    }

    uint8_t red = command[0];
    uint8_t green = command[1];
    uint8_t blue = command[2];

    active_color = strip.Color(red, green, blue);
    active_animation = (Animation)(command[3]);
  }
}

void loop() {
  tick();

#if ENABLE_UART
  readSerialCommand();
#endif

  delay(20);
}
