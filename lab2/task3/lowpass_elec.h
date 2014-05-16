#include "systemc-ams.h"

SC_MODULE(lp_elec) {
  
  // NOTE: Although we're in the SystemC-AMS world here, we use
  // an ordinary SystemC-module! This is done everytime we want
  // to bundle some TDF-modules or (like in this case) some
  // electrical components within a modules (a.k.a. hierarchization)
  // You can't use an TDF-module to instantiate sub-modules.
   
  sca_tdf::sca_in<double> in;	// input double (wave)
  sca_tdf::sca_out<double> out;	// output is the filtered wave

  sca_eln::sca_tdf::sca_vsource *vin;
  sca_eln::sca_tdf::sca_vsink *vout;
   
   
  sca_eln::sca_c *c;
  sca_eln::sca_r *r;

  sca_eln::sca_node a,b;
  sca_eln::sca_node_ref gnd;

  lp_elec(sc_module_name n, double R, double C) 
  {   
    vin = new sca_eln::sca_tdf::sca_vsource("vin");
      vin->inp(in);
      vin->p(a);
      vin->n(gnd);
    r = new sca_eln::sca_r("r");
      r->value=R; // 160
      r->p(a);
      r->n(b);       
    c = new sca_eln::sca_c("c");
      c->value = C; //100e-6
      c->p(b);
      c->n(gnd);
    vout = new sca_eln::sca_tdf::sca_vsink("vout");
      vout->p(b);
      vout->n(gnd);
      vout->outp(out);
  }
};
