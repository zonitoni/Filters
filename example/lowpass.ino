#include "Filters.h"

unsigned long lastTick = 0;
int tickCounter = 0;

FilteredValue filt1;
FilteredValue filt2;

void setup() {
  filt1.doLPF1(true);
  // filt1.doLPF2(true);
  filt2.doLPF1(true);
  filt2.doLPF2(true);
  filt1.setLPF1Constant(0.5);
  Serial.begin(1000000);
  Serial.println("Let's Go");
}

void loop() {
  unsigned long currentTick = millis();
  static float measurement;
  if (currentTick - lastTick > 10) {
    lastTick = currentTick;
    tickCounter++;
    float meas1 = 25.0 + (random(-400, 400) / (float)100);
    filt1.updateSample(meas1);
    float meas2 = -25.0 + (random(-400, 400) / (float)100);
    filt2.updateSample(meas2);
    if (tickCounter == 50) {
      printDataSerial(filt1.xn, filt1.lpf1, filt1.lpf2, filt2.xn, filt2.lpf1, filt2.lpf2);
      tickCounter = 0;
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
