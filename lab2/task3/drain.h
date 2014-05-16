#include "systemc-ams.h"


SCA_TDF_MODULE(drain) {   
   
  sca_tdf::sca_in<double> in;
   
  void set_attributes() {
      in.set_rate(100);
  }
  SCA_CTOR(drain) {} 
};
