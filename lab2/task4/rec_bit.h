#include "systemc-ams.h"

SCA_TDF_MODULE(rec_bit) {
   
   sca_tdf::sca_in<double> in;
   sca_tdf::sca_out<bool> bitstream;

   long width;

   void set_attribute() {
       in.set_rate(width);
    }

   void processing()
   {
       long i;
       double sum=0;
       for(i = 0; i<width/2; i++)
           sum += in.read();
       bitstream.write(sum > 0 ? true : false);
   }
   
   SCA_CTOR(rec_bit){
    width = 1000;
   };
};
