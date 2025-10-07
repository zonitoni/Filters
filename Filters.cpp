#include "Filters.h"
#include <stdlib.h>


//Constructor
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

  setBufferSize(10);
  setShiftRegisterPointer(NULL);
  setShiftRegisterSum(0);
}

//Main Use.
void FilteredValue::updateSample(float sample) {
  xn = sample;
  isLPF ? lpf = LPF() : lpf = FLOAT_MIN;
  isHPF ? hpf = HPF() : hpf = FLOAT_MIN;
  isFloatingAverage ? floatingAverage = FloatingAverage() : floatingAverage = FLOAT_MIN;
}

// Low Pass Filter
float FilteredValue::LPF() {
  float yn = (1 - a_lpf) * xn + (a_lpf) * getOldValueLPF();
  setOldValueLPF(yn);
  return yn;
}
void FilteredValue::doLPF(bool isActive) {
  isLPF = isActive;
}
void FilteredValue::setLPFConstant(float a) {
  a_lpf = a;
}
void FilteredValue::setOldValueLPF(float val) {
  yn_1_lpf = val;
}
float FilteredValue::getOldValueLPF() {
  return yn_1_lpf;
}

//High Pass Filter
float FilteredValue::HPF() {
  float bn = (a_hpf)*xn + (1 - a_hpf) * getOldValueHPF();
  float yn = xn - bn;
  setOldValueHPF(bn);
  return yn;
}
void FilteredValue::doHPF(bool isActive) {
  isHPF = isActive;
}
void FilteredValue::setHPFConstant(float val) {
  a_hpf = val;
}
void FilteredValue::setOldValueHPF(float val) {
  bn_1_hpf = val;
}
float FilteredValue::getOldValueHPF() {
  return bn_1_hpf;
}


//Floating Average Filter
float FilteredValue::FloatingAverage() {
  //add new Value at first location
  resetShiftRegisterSum();
  int bufferSize = getBufferSize();
  float *ptr = getShiftRegisterPointer();
  for (int i = bufferSize - 1; i > 0; i--) {
    setShiftRegisterSum(*(ptr + i));
    *(ptr + i) = *(ptr + i - 1);
  }
  *(ptr) = xn;
  setShiftRegisterSum(*ptr);
  return (getShiftRegisterSum() / (float)bufferSize);
}
void FilteredValue::doFloatingAverage(bool isActive) {
  isFloatingAverage = isActive;
  if (isFloatingAverage) {
    float* ptr = (float*)malloc(getBufferSize() * sizeof(float));
    setShiftRegisterPointer(ptr);
    initShiftRegister();
  } else {
    freeShiftRegister();
  }
}
float* FilteredValue::getShiftRegisterPointer() {
  return shiftRegister;
}
void FilteredValue::setBufferSize(int size) {
  bufferSize = size;
}
int FilteredValue::getBufferSize() {
  return bufferSize;
}
void FilteredValue::resetShiftRegisterSum() {
  shiftRegisterSum = 0;
}
float FilteredValue::getShiftRegisterSum() {
  return shiftRegisterSum;
}
void FilteredValue::setShiftRegisterSum(float val) {
  shiftRegisterSum += val;
}
void FilteredValue::setShiftRegisterPointer(float* ptr) {
  shiftRegister = ptr;
}
void FilteredValue::setShiftRegisterSize(int newSize) {
  float* ptr = (float*)realloc(getShiftRegisterPointer(), newSize * sizeof(float));
  setShiftRegisterPointer(ptr);
  setBufferSize(newSize);
  initShiftRegister();
}
void FilteredValue::initShiftRegister() {
  float* ptr = getShiftRegisterPointer();
  int size = getBufferSize();
  for (int i = 0; i < size; i++) {
    *(ptr + i) = 0;
  }
}
void FilteredValue::freeShiftRegister() {
  float* ptr = getShiftRegisterPointer();
  if (ptr != NULL) {
    free(ptr);
    setShiftRegisterPointer(NULL);
  }
}
