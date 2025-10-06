#ifndef FILTERS
#define FILTERS


class FilteredValue {
public:
  float xn;
  float lpf1;
  float lpf2;

  FilteredValue();

  void setLPF1Constant(float);
  void setLPF2Constant(float);
  void updateSample(float);
  void doLPF1(bool);
  void doLPF2(bool);

  

private:
  float yn_1_lpf1;
  float xn_1_lpf2;
  float yn_1_lpf2;
  float yn_2_lpf2;
  float a_lpf1;
  float a_lpf2;
  bool isActivelpf1;
  bool isActivelpf2;
  float LPF1();
  float LPF2();
  void setOldValueLPF1(float);
  float getOldValueLPF1();
  void setOldValuesLPF2(float, float);
  float getOldXnLPF2();
  float getOldYnLPF2();
};
#endif
