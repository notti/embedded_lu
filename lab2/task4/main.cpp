#include "systemc-ams.h"
#include "sine.h"
#include "lowpass.h"
#include "mult.h"
#include "abs.h"
#include "rec_bit.h"
#include "stim.h"

int sc_main(int argc, char* argv[])
{
  sc_set_time_resolution(10.0, sc_core::SC_NS);	// setting the time resolution
       
  sca_tdf::sca_signal<double> sig_sine, sig_lpout, sig_mod, sig_abs;	// The two signals we need
  sca_tdf::sca_signal<bool> out;
  sc_signal<bool> in;

  sine src("sine", 1, 1000);
  lowpass lp("lowpass", 1);
  mult m("mult");
  absx a("abs");
  rec_bit r("rec_bit");
  stim s("stim");

  src.out(sig_sine);

  m.in(sig_sine);
  m.bitstream(in);
  m.out(sig_mod);

  a.in(sig_mod);
  a.out(sig_abs);

  lp.in(sig_mod);
  lp.out(sig_lpout);
  r.in(sig_lpout);
  r.bitstream(out);
  s.in(out);
  s.out(in);

  sca_util::sca_trace_file* tr = sca_util::sca_create_vcd_trace_file("tr");
  sca_util::sca_trace(tr, in, "bit_in");
  sca_util::sca_trace(tr, sig_sine ,"sine");
  sca_util::sca_trace(tr, sig_mod,"mod");
  sca_util::sca_trace(tr, sig_abs,"abs");
  sca_util::sca_trace(tr, sig_lpout ,"lpout");
  sca_util::sca_trace(tr, out, "bit_out");
  
  sc_core::sc_start(20, sc_core::SC_MS);
   
  return 0;
}


