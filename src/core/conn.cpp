#include "conn.h"
#include "../util/colors.h"

AnimState *animState;
ConnState *connState;

void handleMessageByte(uint8_t message, AnimState *state, ConnState *conn) {
  Serial.printf("Got %02X\n", message);

  uint8_t prefix = message >> 6;

  Serial.printf("Prefix: %02X\n", prefix);


  if (prefix == 0b01) {
    Serial.println("Got a TX start byte");


    // Start Transaction
    uint8_t anim = (message & 0x38) << 1;
    anim |= message & 0x07;

    Serial.printf("Anim: %02X\n", anim);

    conn->transaction = true;
    conn->animation = anim;
    memset(conn->colors, 0, sizeof(conn->colors));
    conn->color_count = 0;
    conn->draft_color = 0;

  } else if (prefix == 0b10) {
    Serial.println("Got a draft color");

    // Push Color Data
    uint8_t data = message & 0x3F;
    conn->draft_color <<= 6;
    conn->draft_color |= data;

    Serial.printf("Color: %02X\n", conn->draft_color);


  } else if (prefix == 0b11) {
    Serial.println("Got a draft color to push");


    // Push and Commit Color Data
    uint8_t data = message & 0x3F;
    conn->draft_color <<= 6;
    conn->draft_color |= data;

    Serial.printf("Color: %02X\n", conn->draft_color);

    conn->colors[conn->color_count] = conn->draft_color;
    conn->color_count += 1;
    conn->draft_color = 0;

  } else if (prefix == 0b00) {
    Serial.println("Got a TX end byte");


    // End Transaction
    conn->transaction = false;

    state->animation = conn->animation;
    memcpy(state->colors, conn->colors, sizeof(state->colors));
    state->color_count = conn->color_count;

    conn->animation = 0xFF;
    memset(conn->colors, 0, sizeof(conn->colors));
    conn->color_count = 0;
    conn->draft_color = 0;

  } else {
    // Unknown Message
    Serial.printf("Unknown Message! %02X\n", message);
  }
}

#if ENABLE_BLE
  // BLE Services
  BLEDfu bledfu; // DFU Service
  BLEDis bledis; // Device Information Service
  BLEUart bleuart; // UART over BLE Service
  BLEBas blebas; // Battery Service
#endif

#if ENABLE_I2C
void handleReceive(int bytes) {
  for (int i = 0; i < bytes; ++i) {
    handleMessageByte(Wire.read(), animState, connState);
  }
}
#endif

void initPeripherals(AnimState *state, ConnState *conn) {
  animState = state;
  connState = conn;

#if ENABLE_I2C
  Wire.begin(I2C_ADDR);
  Wire.onReceive(handleReceive);
#endif

#if ENABLE_UART
  Serial.begin(9600);
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

void handlePeripherals(AnimState *state, ConnState *conn) {
#if ENABLE_UART
  while (Serial.available()) {
    uint8_t message = Serial.read();
    handleMessageByte(message, state, conn);
  }
#endif

#if ENABLE_BLE
  while (bleuart.available() > 1) {
    uint8_t message = bleuart.read();
    handleMessageByte(message, state, conn);
  }
#endif
}
