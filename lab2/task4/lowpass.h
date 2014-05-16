#include "systemc-ams.h"

SCA_TDF_MODULE(lowpass) {
   
   sca_tdf::sca_in<double> in;	// input double (wave)
   sca_tdf::sca_out<double> out;	// output is the filtered wave

   sca_tdf::sca_ltf_nd ltf;
   sca_util::sca_vector<double> num, den;
   sca_util::sca_vector<double> state;
   double fc0;
   
   void initialize() {
       const double r2pi = M_1_PI * 0.5;
       num(0) = 1.0;
       den(0) =  1.0;
       den(1) = r2pi/fc0;
   }

	    
   void processing()
   {
       out.write(ltf(num, den, state, in.read()));

     // here you apply the Laplace-Transform module on the input, and
     // write its result to the output
     
     // CAVE: the laplace transfer module has a bug preventing it to
     // function correctly in modules using higher data rates than one.
     // So don't get fancy with the data rates here
   }
   
   lowpass(sc_module_name n, double freq_cut) 
   {
       fc0 = freq_cut; 
   }
};
