CC = gcc
C++ = g++
LDLIBS =  -lGL -lGLU -lGLEW -lglut libSOIL.a -lX11 -lm

INCLUDES   = includes.h
HEADERS    = globals.h struct.h SOIL.h
PROTOTYPES = prototypes.h
OBJS 	   = display.o boxy.o timephys.o input.o pend.o

# build flags
BDFG =  -DTEXTURE
BDFG +=  -DLIGHTING

all : pendpoc

pendpoc: main.o $(INCLUDES) $(HEADERS) $(PROTOTYPES) $(OBJS)
	$(C++) $(BDFG) -o pendpoc main.o $(OBJS) $(INCDIRS) $(LIBDIRS) $(LDLIBS)

display.o : display.cc $(INCLUDES) $(HEADERS) $(PROTOTYPES)
	$(C++) $(BDFG) -c display.cc

boxy.o : boxy.cc $(INCLUDES) $(HEADERS) $(PROTOTYPES)
	$(C++) $(BDFG) -c boxy.cc

timephys.o : timephys.cc $(INCLUDES) $(HEADERS) $(PROTOTYPES)
	$(C++) $(BDFG) -c timephys.cc

input.o : input.cc $(INCLUDES) $(HEADERS) $(PROTOTYPES)
	$(C++) $(BDFG) -c input.cc

pend.o : pend.c $(INCLUDES) $(HEADERS) $(PROTOTYPES)
	$(C++) $(BDFG) -c pend.c

main.o : main.cc
	$(C++) $(BDFG) -c main.cc

clean :
	rm *.o

pristine :
	rm *.o
	rm pendpoc

purge :
	rm *.o
	rm pendpoc
