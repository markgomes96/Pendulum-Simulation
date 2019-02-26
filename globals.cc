#ifndef INC_GLOBALS_CC
#define INC_GLOBALS_CC

#include "includes.h"
#include "struct.h"

float rotZ = 90;							// rotation variables 
float rotX = 0;

vect3 cameraPos = vect3(20.0, 2.0, 2.5);	// camera variables
vect3 targetPos = vect3(0.0, 0.0, 0.0);

unsigned frames = 0;						// fps variables
float fps = 0.0;
int oldTime = 0;

int periodStartTime = 0;					// period variables
double omegaPrev = 0.0;
int omegaChangeCount = 0;
float period = 0.0;
float fpp = 0.0;

double timeStep = 0.0;
float inputFR = 0.0;

double t = 0.0;								// datafeed variables
double theta = M_PI/4;
double omega = 0.0;

vertex weightvert = vertex(0.0, 0.0, 0.0, 1.0);

#endif
