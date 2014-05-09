// Main() of testbench for the lfsr-counter
// (c) Markus Damm
// Institute of Computer Technology
// Vienna University of Technology

#include "systemc.h"
#include "lfsr.h"
#include "stim-lfsr.h"

int sc_main(int argc, char* argv[]){
  sc_signal<bool> count_en;  	// triggers counting of the lfsr 
  sc_signal<bool> reset;  	// resets lfsr 
  sc_signal<sc_bv<8> > lfsrout;	// with testbench module 
   
  sc_clock clk ("clk", 2, SC_US);	// clock with a period of 2 µ-sec
   
  lfsr lfsr_inst("lfsr_inst");	// instantiate a lfsr
  stim stim_inst("stim_inst");	// and a testbench-module  
  
  lfsr_inst.clk(clk);		// connect the lfsr ports to the
  lfsr_inst.reset(reset);	// appropriate signals
  lfsr_inst.count_en(count_en);
  lfsr_inst.out(lfsrout);
  
  stim_inst.count_en(count_en);	// connect the testbench ports to the
  stim_inst.reset(reset);	// appropriate signals
  stim_inst.in(lfsrout);
  
  
  sc_trace_file *tf;				// Signal tracing
  tf=sc_create_vcd_trace_file("lfsr");	// create new trace file
  tf->set_time_unit(0.5,SC_US);			// set time resolution to 0.5 µ-sec
  sc_trace(tf,clk,"clk");			// trace each signal
  sc_trace(tf,reset,"reset");			// trace each signal
  sc_trace(tf,count_en,"count_en");
  sc_trace(tf,lfsrout,"lfsrout");
  sc_trace(tf,lfsr_inst.rightin,"rightin");
  
  sc_start(700,SC_US);	// run the simulation for 100 µ-sec
  
  sc_close_vcd_trace_file(tf);	// close trace file

return 0;

};
