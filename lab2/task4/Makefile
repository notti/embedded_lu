

CC     = g++
OPT    = -O3 -fpermissive
DEBUG  = -g
OTHER  = -Wall


CFLAGS = $(OPT) $(OTHER) -Wno-deprecated
# CFLAGS = $(DEBUG) $(OTHER)
# obere Zeile: ohne Debug, untere: mit Debug


MODULE = run
# Name der ausführbaren Datei
SRCS = main.cpp
# Name der Source(n), mit Spaces getrennt
OBJS = $(SRCS:.cpp=.o)

HOME = /home/sclab32/
SYSTEMCAMS =$(HOME)/systemc/systemcams
SYSTEMC =$(HOME)/systemc/systemc

TARGET_ARCH = linux


INCDIR = -I. -I.. -I$(SYSTEMC)/include -I$(SYSTEMCAMS)/include
LIBDIR = -L. -L.. -L$(SYSTEMC)/lib-$(TARGET_ARCH) -L$(SYSTEMCAMS)/lib-$(TARGET_ARCH)

LIBS   = -lpthread -lsystemc-ams -lsystemc -lm $(EXTRA_LIBS)


EXE    = $(MODULE).exe

.SUFFIXES: .cc .cpp .o .x


$(EXE): $(OBJS) $(SYSTEMC)/lib-$(TARGET_ARCH)/libsystemc.a $(SYSTEMCAMS)/lib-$(TARGET_ARCH)/libsystemc-ams.a
	$(CC) $(DEBUG) $(CFLAGS) $(INCDIR) $(LIBDIR) -o $@ $(OBJS) $(LIBS) 2>&1 | c++filt


all: $(EXE)	
	
.cpp.o:
	$(CC) $(DEBUG) $(CFLAGS) $(INCDIR) -c $<

.cc.o:
	$(CC) $(DEBUG) $(CFLAGS) $(INCDIR) -c $<

clean::
	rm -f $(OBJS) *~ $(EXE) 
main.o: lowpass.h sine.h abs.h mult.h rec_bit.h stim.h
