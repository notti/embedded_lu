#include "systemc-ams.h"

SC_MODULE(stim)
{
    sca_tdf::sca_in<bool> in;
    sc_out<bool> out;

   void set_attributes() {
       in.set_delay(1);
   }

    void work() {
        out.write(true);
        wait(1, SC_MS);
        out.write(false);
        wait(3, SC_MS);
        out.write(true);
        wait(2, SC_MS);
        out.write(false);
        wait(5, SC_MS);
        out.write(true);
    }

    SC_CTOR(stim) {
        SC_THREAD(work);
    }
};


