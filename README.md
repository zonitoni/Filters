# Filters
header and cpp files for simples Filters for Arduino

#LPF1
simple Low Pass Filter 1. Order

#HPF1
simple High Pass Filter 1. Order



How to use:

-) Create Instance of FilterdValue Class


-) activate filters via FilteredValue.doLPF1(true)


-) if necessary: Change Filter Constants via .changeFilterConstant(float)


-) whenever a new measurement is availabe call FilteredValue.update(). This updates all selected filtered variables


