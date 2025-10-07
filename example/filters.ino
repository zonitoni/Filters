#include "Filters.h"

unsigned long lastTick = 0;
int tickCounter = 0;

FilteredValue filt1;
FilteredValue filt2;

void setup() {
  Serial.begin(1000000);
  Serial.println("Let's Go");

  filt1 = FilteredValue();
  filt2 = FilteredValue();

  filt1.doLPF(true);
  filt1.setLPFConstant(0.85);
  filt1.doFloatingAverage(true);
  filt1.setShiftRegisterSize(50);
  filt1.doHPF(true);
  filt1.setHPFConstant(0.85);

  filt2.doLPF(true);
  filt2.setLPFConstant(0.95);
  filt2.doFloatingAverage(true);
  filt2.setShiftRegisterSize(100);
  filt2.doHPF(true);
  filt2.setHPFConstant(0.35);
}

float meas1;
float meas2;

void loop() {
  unsigned long currentTick = millis();
  static float measurement;
  tickCounter++;
  if (tickCounter > 10000) {
    meas1 = 25.0 + (random(-400, 400) / (float)100);
    meas2 = -25.0 + (random(-400, 400) / (float)100);
    filt1.updateSample(meas1);
    filt2.updateSample(meas2);
  }


  if (currentTick - lastTick > 10) {
    lastTick = currentTick;
    printDataSerial(filt1.xn, filt1.lpf, filt1.floatingAverage, filt1.hpf, filt2.xn, filt2.lpf, filt2.floatingAverage, filt2.hpf);
  }
}

void printDataSerial(float val1, float val2, float val3, float val4, float val5, float val6, float val7, float val8) {
  float data[] = { val1, val2, val3, val4, val5, val6, val7, val8 };
  int maxIteration = sizeof(data) / sizeof(float);
  for (int i = 0; i < maxIteration; i++) {
    Serial.print(data[i]);
    if (i == maxIteration - 1) Serial.println();
    else Serial.print(",");
  }
}
