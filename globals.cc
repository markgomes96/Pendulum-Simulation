#ifndef INC_GLOBALS_CC
#define INC_GLOBALS_CC

#include "includes.h"
#include "struct.h"
#include "globals.h"

// lighting variables
vect3 lightPos = vect3(6.0, 6.0, 5.0);
vect3 startLP = lightPos;

float cambounds[6];
vect3 oldCamPos = vect3(0.0, 0.0, 0.0);
vect3 oldTarget = vect3(0.0, 0.0, 0.0);

struct box room[6];
struct box penbase[6];

struct box tableLeg1[6];
struct box tableLeg2[6];
struct box tableLeg3[6];
struct box tableLeg4[6];
struct box tableFace[6];

struct texture textarray[10];

float rotZ = 90;							// rotation variables
float rotX = 0;

vect3 cameraPos = vect3(10.36, -16.91, 3.17);	// camera variables
vect3 targetPos = vect3(4.83, -8.65, 0.82);

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
