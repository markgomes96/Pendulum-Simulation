CC = gcc
C++ = g++
#LIBDIRS = -L/usr/lib64
#INCDIRS = -I/usr/include
LDLIBS =  -lGL -lGLU -lGLEW -lglut libSOIL.a -lX11 -lm

INCLUDES   = includes.h
HEADERS    = globals.h struct.h SOIL.h
PROTOTYPES = prototypes.h
OBJS 	   = display.o boxy.o timephys.o input.o pend.o

CF =	#-DTEXTURE -> to switch to level scene

all : pendpoc

pendpoc: main.o $(INCLUDES) $(HEADERS) $(PROTOTYPES) $(OBJS)
	$(C++) $(CF) -o pendpoc main.o $(OBJS) $(INCDIRS) $(LIBDIRS) $(LDLIBS)

display.o : display.cc $(INCLUDES) $(HEADERS) $(PROTOTYPES)
	$(C++) $(CF) -c display.cc

boxy.o : boxy.cc $(INCLUDES) $(HEADERS) $(PROTOTYPES)
	$(C++) $(CF) -c boxy.cc

timephys.o : timephys.cc $(INCLUDES) $(HEADERS) $(PROTOTYPES)
	$(C++) $(CF) -c timephys.cc

input.o : input.cc $(INCLUDES) $(HEADERS) $(PROTOTYPES)
	$(C++) $(CF) -c input.cc

pend.o : pend.c $(INCLUDES) $(HEADERS) $(PROTOTYPES)
	$(C++) $(CF) -c pend.c

main.o : main.cc
	$(C++) $(CF) -c main.cc

clean :
	rm *.o

pristine :
	rm *.o
	rm pendpoc
