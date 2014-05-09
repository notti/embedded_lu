// Module shiftreg implementing an 8-bit shift-register

#include "systemc.h"

SC_MODULE(shiftreg) {

   sc_in<bool> clk;
   sc_in<bool> reset;
   sc_in<bool> ld;
   sc_in<bool> lshift;
   sc_in<bool> rshift;
   sc_in<bool> leftin;
   sc_in<bool> rightin;
   sc_in<sc_bv<8> > in;
   sc_out<sc_bv<8> > out;

   sc_bv<8> value;

   SC_CTOR(shiftreg) { 
	   SC_METHOD(do_shift)
			   sensitive << clk.pos() << reset;
   }

   void do_reset() {

   }
   
   void do_shift() {
	   if (this->reset.read()) {
		   this->value ^= this->value;
		   this->out.write(this->value);
	   } else if (this->ld.read()) {
		   this->value = this->in.read();
		   this->out->write(this->value);
	   } else if (this->lshift.read()) {
		   this->value <<= 1;
		   this->value[0] = this->rightin->read();
		   this->out->write(this->value);
	   } else if (this->rshift.read()) {
		   this->value >>= 1;
		   this->value[7] = this->leftin->read();
		   this->out->write(this->value);
	   }
   }
   
};
