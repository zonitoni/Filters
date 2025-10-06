#include "Filters.h"

unsigned long lastTick = 0;
int tickCounter = 0;

FilteredValue filt1;
FilteredValue filt2;

void setup() {
  filt1.doLPF1(true);
  filt2.doLPF1(true);

  filt1.doHPF1(true);
  filt2.doHPF1(true);
  
  Serial.begin(1000000);
  Serial.println("Let's Go");
}

float meas1;
float meas2;

float constantRef = 10;

void loop() {
  unsigned long currentTick = millis();
  static float measurement;
  if (currentTick - lastTick > 10) {
    lastTick = currentTick;
    tickCounter++;

    if (tickCounter > 100) {
      meas1 = 25.0 + (random(-400, 400) / (float)100);
      meas2 = -25.0 + (random(-400, 400) / (float)100);
    }

    filt1.updateSample(meas1);
    filt2.updateSample(meas2);

    if (tickCounter % 10 == 0) {
      printDataSerial(filt1.xn, filt1.lpf1, filt1.hpf1, filt2.xn, filt2.lpf1, filt2.hpf1);
    }
  }
}

void printDataSerial(float val1, float val2, float val3, float val4, float val5, float val6) {
  float data[] = { val1, val2, val3, val4, val5, val6 };
  int maxIteration = sizeof(data) / sizeof(float);
  for (int i = 0; i < maxIteration; i++) {
    Serial.print(data[i]);
    if (i == maxIteration - 1) Serial.println();
    else Serial.print(",");
  }
}
