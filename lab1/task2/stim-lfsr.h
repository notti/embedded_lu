// Testbench module for the 8-bit shift-register

#include "systemc.h"

SC_MODULE(stim) {

    sc_out<bool> count_en;
    sc_out<bool> reset;
    sc_in<sc_bv<8> > in;


    SC_CTOR(stim) {
        SC_THREAD(go);
        SC_METHOD(traceout);
        sensitive << in;
        dont_initialize();
    }

    void go() {
        reset.write(true);
        wait(1, SC_US);
        reset.write(false);
        wait(1, SC_US);
        count_en.write(true);
        wait(10, SC_US);
        count_en.write(false);
        wait(4, SC_US);
        count_en.write(true);
        wait(4, SC_US);
        reset.write(true);
        wait(4, SC_US);
        reset.write(false);
        wait(10, SC_US);
    }

    void traceout() {
        cout << "Register contains " << in.read();
        cout << "  at time: "<< sc_time_stamp() << endl;
    }

};
