// CONFIGURATION

// Interfaces

// Accept commands over UART/Serial.
// Usually this is a virtual port over USB.
#define ENABLE_UART 1

// Accept commands over I2C as a slave device at the given address.
#define ENABLE_I2C 1
#define I2C_ADDR 0x04

// Accept commands over BLE (on Bluefruit boards).
#define ENABLE_BLE 1

// Connected LEDs
#define LED_PIN PIN_NEOPIXEL
#define LED_COUNT 1

// Driving Mode
#define LED_BRIGHTNESS 255
