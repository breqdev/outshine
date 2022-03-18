#include "conn.h"
#include "../util/colors.h"

AnimState *animState;

#if ENABLE_I2C
void handleReceive(int bytes) {
  if (bytes != 4) {
    return; // malformed message
  }

  uint8_t red = Wire.read();
  uint8_t green = Wire.read();
  uint8_t blue = Wire.read();

  animState->color = color(red, green, blue);
  animState->animation = Wire.read();
}
#endif

void initConn(AnimState *state) {
  animState = state;

#if ENABLE_I2C
  Wire.begin(I2C_ADDR);
  Wire.onReceive(handleReceive);
#endif

#if ENABLE_UART
  Serial.begin(9600);
  Serial.setTimeout(100);
#endif

#if ENABLE_BLE
  Bluefruit.autoConnLed(true);
  Bluefruit.configPrphBandwidth(BANDWIDTH_MAX);
  Bluefruit.begin();
  Bluefruit.setTxPower(4);
  Bluefruit.setName("Outshine");

  // Start services
  bledfu.begin();

  bledis.setManufacturer("Brooke Chalmers");
  bledis.setModel("Bluefruit");
  bledis.setSerialNum("80085");
  bledis.begin();

  bleuart.begin();

  blebas.begin();
  blebas.write(100);

  // Start advertising
  Bluefruit.Advertising.addFlags(BLE_GAP_ADV_FLAGS_LE_ONLY_GENERAL_DISC_MODE);
  Bluefruit.Advertising.addTxPower();

  Bluefruit.Advertising.addService(bleuart);
  Bluefruit.Advertising.addName();

  Bluefruit.Advertising.restartOnDisconnect(true);
  Bluefruit.Advertising.setInterval(32, 244);
  Bluefruit.Advertising.setFastTimeout(30);
  Bluefruit.Advertising.start(0);
#endif
}

#if ENABLE_BLE
String bleReadStringUntil(char delim) {
  String result = "";

  int start = millis();

  while (true) {
    while (bleuart.available()) {
      char c = bleuart.read();
      if (c == delim) {
        return result;
      }
      result += c;
    }

    if (millis() - start > 10) {
      return result;
    }

    delay(1);
  }
}
#endif

void handleCommands(AnimState *state) {

#if ENABLE_UART
  while (Serial.available() > 1) {
    String command = Serial.readStringUntil('\n');

    if (command.length() < 4) {
      return;
    }

    uint8_t red = command[0];
    uint8_t green = command[1];
    uint8_t blue = command[2];

    state->color = color(red, green, blue);
    state->animation = command[3];
  }
#endif

#if ENABLE_BLE
  while (bleuart.available() > 1) {
    String command = Serial.readStringUntil('\n');

    if (command.length() < 4) {
      return;
    }

    uint8_t red = command[0];
    uint8_t green = command[1];
    uint8_t blue = command[2];

    state->color = color(red, green, blue);
    state->animation = command[3];
  }
#endif
}
