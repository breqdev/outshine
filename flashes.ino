void tickFlash(uint8_t period, uint8_t highCycle) {
  if ((tick_index & (period - 1)) < highCycle) {
    tickSolid();
  } else {
    tickOff();
  }
}

void tickComplexFlash() {
  if ((tick_index & 63) < 16) {
    tickSolid();
  } else {
    if ((tick_index & 15) < 8) {
      tickSolid();
    } else {
      tickOff();
    }
  }
}
