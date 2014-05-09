// Testbench module for the 8-bit shift-register
// (c) Markus Damm
// Institute of Computer Technology
// Vienna University of Technology

#include "systemc.h"

SC_MODULE(stim) {

   public:	
   sc_out<bool> ld;		// the ports of the testbench module are
   sc_out<bool> reset;		// basically the same as those of the register
   sc_out<bool> lshift;		// but the directions are reversed
   sc_out<bool> rshift;		// except for the ports in and out.
   sc_out<bool> leftin;		// also, there is no clk-input
   sc_out<bool> rightin;
   sc_out<sc_bv<8> > out;
   sc_in<sc_bv<8> > in;

   SC_CTOR(stim) {
     SC_THREAD(go);	   // thread providing the inputs and control signals for the register   
     SC_METHOD(traceout);  // method reading the output of the regsiter
     sensitive << in;	   // sensitive to all changes in the modlues input (= register output)
     dont_initialize();	   // ensures that method isn't called during initialization   
   }
    
   private:  
   void go() {     
     wait(1,SC_US);		// wait one µ-sec
     out.write("10011010");	// write to the registers input
     wait(1,SC_US);
     ld.write(true);		// set load-signal => load new value
     wait(2,SC_US);
     ld.write(false);		// reset load-signal
     wait(4,SC_US); 
     lshift.write(true);	// start shifting to the left
     wait(5,SC_US); 
     rightin.write(true);	// set right input bit to 1
     wait(5,SC_US); 
     lshift.write(false); 	// stop shifting to the left
     rshift.write(true);	// start shifting to the right 
     wait(5,SC_US);  
     leftin.write(true);	// set left input bit to 1
     wait(5,SC_US);   
     rshift.write(false);	// stop shifting to the right
     reset.write(true);		// reset register
     wait(1,SC_US); 
     reset.write(false);	// reset reset signal ;-)
     wait(2,SC_US);     
     out.write("00101101");	// write new value to the registers input
     ld.write(true);		// and load it
     wait(2,SC_US);
     ld.write(false);   
     wait(10,SC_US); 
     lshift.write(true);	// start shifting to the left   
     
   };
   
   void traceout(){ 	// called anytime the register's output is changing
     cout << "Register contains " << in.read();		// output value
     cout << "  at time: "<< sc_time_stamp() << endl;	// and time
   }
 
};
