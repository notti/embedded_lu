#include "systemc-ams.h"


SCA_TDF_MODULE(drain) {   
   
  sca_tdf::sca_in<double> in;
   
  // this module just provides a drain for a double sdf-signal,
  // thus no processing (and no processing)
  
  SCA_CTOR(drain) {} 
};
