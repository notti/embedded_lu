// main() of testbench for the cordic module
// (c) Markus Damm
// Institute of Computer Technology
// Vienna University of Technology

#include "systemc.h"
#include "cordic.h"
#include "stim-cordic.h"

int sc_main(int argc, char* argv[]){

  sc_signal<double> angle, cos, sin;
  
  int steps;
  cout << "Number of Cordic-iterations: "; cin >> steps;
  
  cordic cordic_inst("cordic_inst",steps);
  source src("src");
  drain drn ("drn");
    
  src.out(angle);
  cordic_inst.angle(angle);
  cordic_inst.cos_out(cos);
  cordic_inst.sin_out(sin); 
  
  drn.in_x(angle);   
  drn.in_cos(cos); 
  drn.in_sin(sin); 
  
  sc_start(40,SC_US);

 return 0;

};
