// Module lfsr_comp computing the feedback for an 8-bit LFSR

#include "systemc.h"

SC_MODULE(lfsr_feedback) {

    sc_in<sc_bv<8> > in;
    sc_out<bool> out;

   SC_CTOR(lfsr_feedback) {
       SC_METHOD(generate_feedback)
           sensitive << in;
   }   

   void generate_feedback() {
        sc_bv<8> x = in.read();
        out->write((x[3].to_bool() == x[4].to_bool()) == (x[5].to_bool() == x[7].to_bool()));
   }
};
