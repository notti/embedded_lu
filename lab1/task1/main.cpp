// Main() of testbench for the 8-bit shift-register

#include "systemc.h"
#include "shiftreg.h"
#include "stim-shiftreg.h"

int sc_main(int argc, char* argv[]){

  sc_signal<bool> reset;
  sc_signal<bool> ld;
  sc_signal<bool> lshift;
  sc_signal<bool> rshift;
  sc_signal<bool> leftin;
  sc_signal<bool> rightin;
  sc_signal<sc_bv<8> > in;
  sc_signal<sc_bv<8> > out;
   
  sc_clock clk ("clk", 2, SC_US);	// a clock with a period of 2 �-sec
   
  shiftreg sr("sr0");
  sr.clk(clk);
  sr.reset(reset);
  sr.ld(ld);
  sr.lshift(lshift);
  sr.rshift(rshift);
  sr.leftin(leftin);
  sr.rightin(rightin);
  sr.in(in);
  sr.out(out);
  stim st("stim0");
  st.reset(reset);
  st.ld(ld);
  st.lshift(lshift);
  st.rshift(rshift);
  st.leftin(leftin);
  st.rightin(rightin);
  st.in(out);
  st.out(in);
  sc_trace_file *tf;				// Signal tracing
  tf=sc_create_vcd_trace_file("shiftreg");	// create new trace file
  tf->set_time_unit(0.5,SC_US);	// set time resolution to 0.5 �-sec (let's do a bit oversampling ;-))
  
  sc_trace(tf,clk,"clk");
  sc_trace(tf,reset,"reset");
  sc_trace(tf,ld,"ld");
  sc_trace(tf,lshift,"lshift");
  sc_trace(tf,rshift,"rshift");
  sc_trace(tf,leftin,"leftin");
  sc_trace(tf,rightin,"rightin");
  sc_trace(tf,in,"in");
  sc_trace(tf,out,"out");

  sc_start(100,SC_US);	// run the simulation for 100 �-sec
  
  sc_close_vcd_trace_file(tf);	// close trace file

return 0;

};
