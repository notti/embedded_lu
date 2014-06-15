// Module lfsr implementing an 8-bit lfsr-counter

#include "systemc.h"
#include "../task1/shiftreg.h"
#include "lfsr-feedback.h"

SC_MODULE(lfsr) {

    sc_in<bool> clk;
    sc_in<bool> reset;
    sc_in<bool> count_en;
    sc_inout<sc_bv<8> > out;


    shiftreg sr;
    lfsr_feedback fb;

    sc_signal<bool> rightin;

    //dummy
    sc_signal<sc_bv<8> > in;
    sc_signal<bool> zero;

    SC_CTOR(lfsr) : sr("shiftreg"), fb("feedback") {
        zero.write(0);

        sr.clk(clk); 
        sr.reset(reset);
        sr.ld(zero);
        sr.lshift(count_en);
        sr.rshift(zero);
        sr.leftin(zero);
        sr.in(in);
        sr.rightin(rightin);
        sr.out(out);

        fb.in(out);
        fb.out(rightin);
    }   



};
