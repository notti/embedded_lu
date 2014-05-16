#include "systemc-ams.h"

SCA_TDF_MODULE(absx) {   
 
  sca_tdf::sca_out<double> out;
  sca_tdf::sca_in<double> in;

  void processing()
  { 
      out.write(fabs(in.read()));
  }
	
  SCA_CTOR(absx){};
};
