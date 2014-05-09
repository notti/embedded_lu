// fifo interface & implementation
// (c) Markus Damm
// Institute of Computer Technology
// Vienna University of Technology

#include "systemc.h"
#include <queue>


template<class T> class fifo_out_if: virtual public sc_interface
{
    public:
    virtual bool nonb_write(T val) = 0;
    virtual void write(T val) = 0;
    virtual void reset() = 0;
};

template<class T> class fifo_in_if: virtual public sc_interface
{
    public:
    virtual bool nonb_read(T &val) = 0;
    virtual T read() = 0;
    virtual int num_available() = 0;
};


template<class T> class fifo: public fifo_in_if<T>, public fifo_out_if<T>, public sc_prim_channel
{
    std::queue<T> q;
    unsigned int max;
    sc_event data_written;
    sc_event data_read;

    public:

    fifo(unsigned int m) : max(m) {}

    virtual void reset() {
        std::queue<T> empty;
        std::swap( q, empty );
    }

    virtual int num_available() {
        return q.size();
    }

    virtual bool nonb_write(T val) {
        if (q.size() >= max)
            return false;
        q.push(val);
        return true;
    }

    virtual bool nonb_read(T &val) {
        if (q.empty())
            return false;
        val = q.front();
        q.pop();
        return true;
    }

    virtual void write(T val) {
        if (q.size() >= max) {
            std::cout << "Queue full (blocking)" << std::endl;
            wait(data_read);
            std::cout << "Queue nonfull (unblocking)" << std::endl;
        }
        q.push(val);
        data_written.notify();
    }

    virtual T read() {
        T val;
        if (q.empty()) {
            std::cout << "Queue empty (blocking)" << std::endl;
            wait(data_written);
            std::cout << "Queue nonempty (unblocking)" << std::endl;
        }
        val = q.front();
        q.pop();
        data_read.notify();
        return val;
    }
};
