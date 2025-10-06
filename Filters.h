#ifndef FILTERS
#define FILTERS

#define FLOAT_MIN -9999999;

class FilteredValue {
public:
  float xn;
  float lpf1;
  float hpf1;

  FilteredValue();
  
  void setLPF1Constant(float);
  void setHPF1Constant(float);
  void updateSample(float);
  void doLPF1(bool);
  void doHPF1(bool);

private:
  float yn_1_lpf1;
  float a_lpf1;
  float a_hpf1;
  float bn_1;
  bool isActivelpf1;
  bool isActivehpf1;
  float LPF1();
  float HPF1();
  void setOldValueHPF1(float);
  float getOldValueHPF1();
  void setOldValueLPF1(float);
  float getOldValueLPF1();
};
#endif
