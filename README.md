# outshine

NeoPixel controller for Arduino, displaying effects on a NeoPixel strand based on commands received over UART or I2C.

Commands take this 4-byte form:

```
[1 byte] Red channel
[1 byte] Green channel
[1 byte] Blue channel
[1 byte] Animation command
```

The following animations are available:

```
0x0X -- Basics
  0x00: Off
  0x01: Solid Color

0x1X -- Flashes
  0x10: Basic Flash
  0x11: Long Flash (long period on, short period off)
  0x12: Fast Flash
  0x13: Strobe
  0x14: Complex Flash (short period on, then long period on)

0x2X -- Fades
  0x20: Basic Simultaneous Fade In/Out
  0x21: Wipe/Fade

0x3X -- Wipes
  0x30: Basic Color Wipe
  0x31: Fast Color Wipe
  0x32: Larson Scanner
  0x33: Inverted Larson Scanner
  0x34: Circular Scanner
  0x35: Inverted Circular Scanner

0x4X -- Twinkles
  0x40: Basic Theater Chase
  0x41: Running Lights / Wide Theater Chase
  0x42: Random Sparkle
  0x43: Inverted Random Sparkle / Snow Twinkles
  0x44: Paparazzi

0x5X -- Rainbows
  0x50: Rainbow Circle
  0x51: Rainbow Theater Chase
```
