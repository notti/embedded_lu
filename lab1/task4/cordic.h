// cordic module

#include <math.h>
#include <vector>
#include "systemc.h"

using namespace std;

template <typename T> int sgn(T val) {
        return (T(0) < val) - (val < T(0));
}

SC_MODULE(cordic) {

    sc_in<double> angle; 	// the input angle 
    sc_out<double> cos_out;	// the outputs
    sc_out<double> sin_out;


    vector<double> table;
    double scale;
    int steps;
    SC_HAS_PROCESS(cordic);				// this is the first line to replace the Macro	
    cordic(sc_module_name n, int stp):sc_module(n)	// and the second line: int stp is our extra
    { 							// argument, the rest is mandatory
        steps = stp;
        scale = 1;
        for(int i=0; i<=stp; i++) {
            double ai = atan(pow(2, -i));
            table.push_back(ai);
            scale *= cos(ai);
        }
        SC_METHOD(proc)
            sensitive << angle;
    };   

    void proc()
    {   
        double x = 1, y = 0, z = angle.read();
        for(int i=0; i<=steps; i++) {
            double xn = x - sgn(z) * pow(2, -i) * y;
            double yn = y + sgn(z) * pow(2, -i) * x;
            double zn = z - sgn(z) * table[i];
            x = xn; y = yn; z = zn;
        }
        cos_out.write(scale * x);
        sin_out.write(scale * y);
    }
};
