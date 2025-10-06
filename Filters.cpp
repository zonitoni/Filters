#include "Filters.h"


FilteredValue::FilteredValue() {
  a_lpf1 = 0.075;
  a_lpf2 = 0.025;
  isActivelpf1 = false;
  isActivelpf2 = false;
}
void FilteredValue::updateSample(float sample) {
  xn = sample;
  isActivelpf1? lpf1 = this->LPF1() : lpf1 = 0;
  isActivelpf2? lpf2 = this->LPF2() : lpf2 = 0;
}

void FilteredValue::setLPF1Constant(float a){
  a_lpf1 = a;
}
void FilteredValue::setLPF2Constant(float a){
  a_lpf2 = a;
}
void FilteredValue::doLPF1(bool isActive){
  isActivelpf1 = isActive;
}
void FilteredValue::doLPF2(bool isActive){
  isActivelpf2 = isActive;
}
float FilteredValue::LPF1() {
  float yn = a_lpf1 * xn + (1 - a_lpf1) * this->getOldValueLPF1();
  this->setOldValueLPF1(yn);
  return yn;
}
float FilteredValue::LPF2() {
  float yn = a_lpf2 * xn + (a_lpf2) * (1 - a_lpf2) * this->getOldXnLPF2() + (1 - a_lpf2) * (1 - a_lpf2) * this->getOldYnLPF2();
  this->setOldValuesLPF2(xn, yn);
  return yn;
}
void FilteredValue::setOldValueLPF1(float val) {
  yn_1_lpf1 = val;
}
float FilteredValue::getOldValueLPF1() {
  return yn_1_lpf1;
}
void FilteredValue::setOldValuesLPF2(float xVal, float yVal) {
  yn_2_lpf2 = yn_1_lpf2;
  yn_1_lpf2 = yVal;
  xn_1_lpf2 = xVal;
}
float FilteredValue::getOldXnLPF2() {
  return xn_1_lpf2;
}
float FilteredValue::getOldYnLPF2() {
  return yn_2_lpf2;
}