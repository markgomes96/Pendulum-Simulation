#ifndef INC_GLOBALS_CC
#define INC_GLOBALS_CC

#include "includes.h"
#include "struct.h"

float rotZ = 90;			//rotation variables 
float rotX = 0;

unsigned frames = 0;		//fps variables
int oldTime = 0;

double t = 0.0;			//datafeed variables
double theta = M_PI-.01;
double omega = 0.0;

vertex weightvert = vertex(0.0, 0.0, 0.0, 1.0);

#endif
