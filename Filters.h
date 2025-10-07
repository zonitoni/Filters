#ifndef FILTERS
#define FILTERS

#define FLOAT_MIN -9999999;

class FilteredValue {
public:
  float xn;
  float lpf;
  float hpf;
  float floatingAverage;

  FilteredValue();

  void setLPFConstant(float);
  void setHPFConstant(float);
  void setShiftRegisterSize(int);

  void updateSample(float);

  void doLPF(bool);
  void doHPF(bool);
  void doFloatingAverage(bool);

private:
  float yn_1_lpf;
  float a_lpf;
  float a_hpf;
  float bn_1_hpf;

  float* shiftRegister;
  float shiftRegisterSum;
  int bufferSize;

  bool isLPF;
  bool isHPF;
  bool isFloatingAverage;

  float LPF();
  float HPF();
  float FloatingAverage();

  void freeShiftRegister();
  float* getShiftRegisterPointer();
  int getBufferSize();
  void initShiftRegister();
  float getShiftRegisterSum();
  void setShiftRegisterSum(float);
  void resetShiftRegisterSum();
  void setBufferSize(int);
  void setShiftRegisterPointer(float*);

  void setOldValueHPF(float);
  float getOldValueHPF();

  void setOldValueLPF(float);
  float getOldValueLPF();
};
#endif
