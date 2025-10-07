#include "Filters.h"
#include <stdlib.h>

FilteredValue::FilteredValue() {
  a_lpf = 0.85;
  a_hpf = 0.85;
  
  isLPF = false;
  isHPF = false;
  isFloatingAverage = false;

  lpf = 0;
  hpf = 0;
  floatingAverage = 0;

  yn_1_lpf = 0;
  bn_1_hpf = 0;

  this->setBufferSize(10);
  this->setShiftRegisterPointer(NULL);
  this->setShiftRegisterSum(0);
}
void FilteredValue::updateSample(float sample) {
  xn = sample;
  isLPF ? lpf = this->LPF() : lpf = FLOAT_MIN;
  isHPF ? hpf = this->HPF() : hpf = FLOAT_MIN;
  isFloatingAverage ? floatingAverage = this->FloatingAverage() : floatingAverage = FLOAT_MIN;
}
void FilteredValue::setLPFConstant(float a) {
  a_lpf = a;
}
void FilteredValue::setHPFConstant(float val) {
  a_hpf = val;
}
void FilteredValue::doLPF(bool isActive) {
  isLPF = isActive;
}
void FilteredValue::doFloatingAverage(bool isActive) {
  isFloatingAverage = isActive;
  if (isFloatingAverage) {
    float* ptr = (float*)malloc(this->getBufferSize() * sizeof(float));
    setShiftRegisterPointer(ptr);
    initShiftRegister();
  }
}
float FilteredValue::FloatingAverage() {
  //add new Value at first location
  resetShiftRegisterSum();
  for (int i = this->getBufferSize() - 1; i > 0; i--) {
    setShiftRegisterSum(*(this->getShiftRegisterPointer() + i));
    *(this->getShiftRegisterPointer() + i) = *(this->getShiftRegisterPointer() + i - 1);
  }
  *(this->getShiftRegisterPointer()) = xn;
  setShiftRegisterSum(*(this->getShiftRegisterPointer()));
  return (this->getShiftRegisterSum() / (float)this->getBufferSize());
}
float* FilteredValue::getShiftRegisterPointer() {
  return this->shiftRegister;
}
void FilteredValue::setBufferSize(int size) {
  this->bufferSize = size;
}
int FilteredValue::getBufferSize() {
  return bufferSize;
}
void FilteredValue::resetShiftRegisterSum(){
  shiftRegisterSum = 0;
}
float FilteredValue::getShiftRegisterSum() {
  return shiftRegisterSum;
}
void FilteredValue::setShiftRegisterSum(float val) {
  shiftRegisterSum += val;
}
void FilteredValue::setShiftRegisterPointer(float* ptr) {
  this->shiftRegister = ptr;
}
void FilteredValue::setShiftRegisterSize(int newSize) {
  float* ptr = (float*)realloc(ptr, newSize * sizeof(float));
  setShiftRegisterPointer(ptr);
  setBufferSize(newSize);
  initShiftRegister();
}
void FilteredValue::initShiftRegister() {
  float* ptr = this->getShiftRegisterPointer();
  int size = this->getBufferSize();
  for (int i = 0; i < size; i++) {
    *(ptr + i) = 0;
  }
}
void FilteredValue::freeShiftRegister() {
  float* ptr = this->getShiftRegisterPointer();
  if (ptr != NULL) free(ptr);
}
void FilteredValue::doHPF(bool isActive) {
  isHPF = isActive;
}
float FilteredValue::LPF() {
  float yn = (1 - a_lpf) * xn + (a_lpf) * this->getOldValueLPF();
  this->setOldValueLPF(yn);
  return yn;
}
void FilteredValue::setOldValueLPF(float val) {
  yn_1_lpf = val;
}
float FilteredValue::getOldValueLPF() {
  return yn_1_lpf;
}
float FilteredValue::HPF() {

  float bn = (a_hpf)*xn + (1 - a_hpf) * this->getOldValueHPF();
  float yn = xn - bn;
  this->setOldValueHPF(bn);
  return yn;
}
void FilteredValue::setOldValueHPF(float val) {
  bn_1_hpf = val;
}
float FilteredValue::getOldValueHPF() {
  return bn_1_hpf;
}
