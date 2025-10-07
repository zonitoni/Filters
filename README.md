# Filters
header and cpp files for simple Filters for Arduino at RunTime

#LPF1
simple Low Pass Filter 1. Order

#HPF1
simple High Pass Filter 1. Order

#Floating Average Filter with customizeable array size

#Supplies the actual Sample, LPF, HPF and FAVG values at the same time.


How to use:

-) Create Instance of FilterdValue Class


-) activate filters via FilteredValue.doLPF(true) / .doHPf(true) ...


-) if necessary: Change Filter Constants via .changeFilterConstant(float) 


-) whenever a new sample is availabe call .updateSample(sample). This updates all selected filtered variables.




