#ifndef INC_GLOBALS_H
#define INC_GLOBALS_H

#include "includes.h"
#include "struct.h"

//Variables to specify window position 
#define WINDOW_POS_X 100
#define WINDOW_POS_Y 0

//Variables to specify window size
#define WINDOW_MAX_X 800
#define WINDOW_MAX_Y 800

#define DFP "datafeed"

extern float rotZ;	//rotation variables 
extern float rotX;

extern unsigned frames;		//fps variables
extern int oldTime;

extern int periodStartTime;		//period variables
extern double omegaPrev;
extern int omegaChangeCount;
//extern double Nstep;
extern int prevTime;
extern float scalefactor;

extern double t;				//datafeed variables
extern double theta;
extern double omega;

extern vertex weightvert;

#endif
