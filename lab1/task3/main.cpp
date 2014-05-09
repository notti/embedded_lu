// Main() of testbench for the fifo
// (c) Markus Damm
// Institute of Computer Technology
// Vienna University of Technology

#include "systemc.h"
#include "stim-fifo.h"

int sc_main(int argc, char* argv[]){

  srand(time(NULL));

  fifo<int> val(3);  // declare the fifo with 3 elements
   
  producer prod("prod");	// instantiate a producer
  consumer cons("cons");	// and a consumer
  
  prod.out(val);	// connect the producer
  cons.in(val);	// to the consumer via the fifo val
  
  sc_start(300,SC_US);	// run the simulation for 700 µ-sec

return 0;

};
