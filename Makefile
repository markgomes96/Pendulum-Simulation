CC = gcc
C++ = g++ 
LIBDIRS = -L/usr/lib64
INCDIRS = -I/usr/include
LDLIBS =  -lglut -lGL -lGLU -lX11 -lm

INCLUDES   = includes.h
HEADERS    = globals.h
PROTOTYPES = prototypes.h
OBJS 	   = display.o input.o

all : pendpoc

pendpoc: main.o $(INCLUDES) $(HEADERS) $(PROTOTYPES) $(OBJS) 
	$(C++) -o pendpoc main.o $(OBJS) $(INCDIRS) $(LIBDIRS) $(LDLIBS) 

display.o : display.cc $(INCLUDES) $(HEADERS) $(PROTOTYPES)
	$(C++) -c display.cc

input.o : input.cc $(INCLUDES) $(HEADERS) $(PROTOTYPES)
	$(C++) -c input.cc

main.o : main.cc
	$(C++) -c main.cc 

clean :
	rm *.o

pristine :
	rm *.o
	rm pendpoc
