#include "systemc-ams.h"

SCA_TDF_MODULE(mult) {
   
   sca_tdf::sca_in<double> in;
   sca_tdf::sca_out<double> out;
   sca_tdf::sca_de::sca_in<bool> bitstream;

   void processing()
   {
       out.write(bitstream.read() ? in.read() : 0);
   }
   
   SCA_CTOR(mult){};
};
