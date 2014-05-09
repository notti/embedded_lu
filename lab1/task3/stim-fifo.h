// Testbench for the fifo
// (c) Markus Damm
// Institute of Computer Technology
// Vienna University of Technology

#include "systemc.h"
#include "fifo.h"

SC_MODULE(producer) {

   public:	
   sc_port<fifo_out_if<int> > out;	// port using the fifo write interface

   SC_CTOR(producer) {
     SC_THREAD(go);	   // thread providing values for the fifo 
   };
    
   private:  
   void go() {  
     bool success;  
     int val;    
     wait(1,SC_US);		// wait one µ-sec
     while(true){
       val=(int)(rand()/((double)RAND_MAX/100));	// create a random integer between 0 and 100
#ifndef BLOCKING
       success = out->nonb_write(val);			// and write it to the fifo
       if(success) cout << "Writing " << val;
       else cout << "+++ Writing not succesful";
#else
       out->write(val);
       cout << "Writing " << val;
#endif
       cout << " at time " << sc_time_stamp() << endl;
       wait(1+(int)(rand()/((double)RAND_MAX/10)),SC_US);	// waits 1-11 µ-sec
       if(((double)rand()/RAND_MAX)<0.1) {
         out->reset();
         cout << "*** Resetting fifo at time " << sc_time_stamp() << endl;
         wait(1+(int)(rand()/((double)RAND_MAX/10)),SC_US);	// waits 1-11 µ-sec
       };
     };     
   }; 
};

SC_MODULE(consumer) {

   public:	
   sc_port<fifo_in_if<int> > in;	// port using the fifo write interface
   
   SC_CTOR(consumer) {
  
     SC_THREAD(traceout);  // thread reading the output of the fifo
   }
    
   private:  
   void traceout() {   
     bool success; 
     int val;  
     wait(1,SC_US);		// wait one µ-sec
     while(true){
       wait(1+(int)(rand()/((double)RAND_MAX/10)),SC_US);	// waits 1-11 µ-sec
#ifndef BLOCKING
       success = in->nonb_read(val);	// reads integer from the fifo
       if(success) cout << "Reading value " << val;
       else cout << "--- Reading not succesful";
#else
       val = in->read();	// reads integer from the fifo
       cout << "Reading value " << val;
#endif
       cout << " at time " << sc_time_stamp();
#ifndef BLOCKING
       if(success) cout << "  --  #fifo-el = " << in->num_available();
#endif
       cout << endl;
     };     
   };
};
