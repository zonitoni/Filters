#include "Filters.h"


FilteredValue::FilteredValue() {
  a_lpf1 = 0.85;
  a_hpf1 = 0.85;
  isActivelpf1 = false;
  isActivehpf1 = false;
}
void FilteredValue::updateSample(float sample) {
  xn = sample;
  isActivelpf1? lpf1 = this->LPF1() : lpf1 = FLOAT_MIN;
  isActivehpf1? hpf1 = this->HPF1() : hpf1 = FLOAT_MIN;
}
void FilteredValue::setLPF1Constant(float a){
  a_lpf1 = a;
}
void FilteredValue::setHPF1Constant(float val){
  a_hpf1 = val;
}
void FilteredValue::doLPF1(bool isActive){
  isActivelpf1 = isActive;
}
void FilteredValue::doHPF1(bool isActive){
  isActivehpf1 = isActive;
}
float FilteredValue::LPF1() {
  float yn = (1-a_lpf1) * xn + (a_lpf1) * this->getOldValueLPF1();
  this->setOldValueLPF1(yn);
  return yn;
}
void FilteredValue::setOldValueLPF1(float val) {
  yn_1_lpf1 = val;
}
float FilteredValue::getOldValueLPF1() {
  return yn_1_lpf1;
}
float FilteredValue::HPF1(){

  float bn = (a_hpf1) * xn + (1-a_hpf1)*this->getOldValueHPF1();
  float yn = xn - bn;
  this->setOldValueHPF1(bn);
  return yn;
}
void FilteredValue::setOldValueHPF1(float val){
  bn_1 = val;
}
float FilteredValue::getOldValueHPF1(){
  return bn_1;
}


