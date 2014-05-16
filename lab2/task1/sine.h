#include "systemc-ams.h"

SCA_TDF_MODULE(sine) {   
 
  // you need to declare a sca_sdf_out port
  // with data type double here
  sca_tdf::sca_out<double> out;

  void processing()
  { 
      out.write(sin(2*M_PI*sc_time_stamp().to_seconds()*1000));
  }
	
  SCA_CTOR(sine) {} 
};
