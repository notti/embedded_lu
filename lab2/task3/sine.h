#include "systemc-ams.h"

SCA_TDF_MODULE(sine) {   
 
  // you need to declare a sca_sdf_out port
  // with data type double here
  sca_tdf::sca_out<double> out;
  long data_rate;
  long frequency;

  void set_attributes() {
      out.set_rate(data_rate);
      out.set_timestep(100, SC_NS);
  }

  void processing()
  { 
      for(long i; i<data_rate; i++)
          out.write(sin(2*M_PI*get_time().to_seconds()*frequency +
                      2*M_PI*out.get_timestep().to_seconds()*frequency*i), i);
  }
	
  sine(sc_module_name n, long data_rate, long frequency):sca_module(n) {
    this->data_rate = data_rate;
    this->frequency = frequency;
  }
};
