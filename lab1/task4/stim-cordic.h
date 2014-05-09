// Testbench for the cordic module
// (c) Markus Damm
// Institute of Computer Technology
// Vienna University of Technology

#include <iomanip>
#include <math.h>
#include "systemc.h"

using namespace std;

SC_MODULE(source) {

    sc_out<double> out;   

    SC_CTOR(source) {    
        SC_THREAD(proc);
    }

    void proc()
    {
        for (double x=0; x<=M_PI; x+=M_PI/10) {
            wait(1, SC_US);
            out.write(x);
        }
    };
};

SC_MODULE(drain) {

    sc_in<double> in_x;
    sc_in<double> in_cos;
    sc_in<double> in_sin;

    SC_CTOR(drain) {    
        SC_METHOD(proc);
        sensitive << in_cos << in_sin;
    }

    void proc()
    {
        std::cout << setiosflags(std::ios::left) << std::setprecision(5) << std::setw(7) << in_x.read() <<
            ": Cos: " << std::setprecision(5) << std::setw(10) << in_cos.read() <<
            " == " << std::setprecision(5) << std::setw(10) << cos(in_x.read()) <<
            "; Sin: " << std::setprecision(5) << std::setw(10) << in_sin.read() <<
            " == " << std::setprecision(5) << std::setw(10) << sin(in_x.read()) << std::endl;
    };
};
