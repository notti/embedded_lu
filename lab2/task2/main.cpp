#include "systemc-ams.h"


#include "sine.h"
#include "drain.h"

int sc_main(int argc, char* argv[])
{
  sc_set_time_resolution(10.0, SC_NS);	// setting the time resolution
  					// like in SystemC
       
  sca_tdf::sca_signal<double> sig_sine ;	// instantiating an sdf-signal
   
  // instantiating TDF-modules works exactly like with SC-modules
  // except you need to set the TDF sample period at one port of one
  // module of the cluster with set_timestep(). If you forget it, you get a
  // run-time error "...at least one sample period must be assigned
  // per cluster..."
  // a sample period of 100 ns is fine in this case
  
  sine x("sine", 50, 1000);
  drain y("drain");
  x.out(sig_sine);
  y.in(sig_sine);
    

  sca_util::sca_trace_file* tr = sca_util::sca_create_vcd_trace_file("tr");
  sca_trace(tr, sig_sine, "sine");
  
  sc_core::sc_start(2, sc_core::SC_MS);
   
  return 0;
}


