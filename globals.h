#ifndef INC_GLOBALS_H
#define INC_GLOBALS_H

#include "includes.h"
#include "struct.h"

// Variables to specify window position
#define WINDOW_POS_X 100
#define WINDOW_POS_Y 0

// Variables to specify window size
#define WINDOW_MAX_X 800
#define WINDOW_MAX_Y 800

#define DFP "datafeed"

//dtheta/dt - theta graph
extern vector<gpoint> glist;
extern bool displayGraph;
extern float timer;
extern bool tf;

// testing
//extern vect3 testPos;

// lighting variables
extern vect3 lightPos;
extern vect3 startLP;   // ***testing variable
extern vect3 splightPos;
extern vect3 splightTarget;

// {-x, +x, -y, +y, -z, +z}
extern float cambounds[6];
extern vect3 oldCamPos;
extern vect3 oldTarget;

extern struct box room[6];
extern struct box penbase[6];

extern struct box tableLeg1[6];
extern struct box tableLeg2[6];
extern struct box tableLeg3[6];
extern struct box tableLeg4[6];
extern struct box tableFace[6];

extern struct texture textarray[10];       // holds all the textures

extern vect3 cameraPos;				// camera movement variables
extern vect3 targetPos;

extern unsigned frames;				// fps variables
extern int oldTime;
extern float fps;

extern int periodStartTime;			// period variables
extern double omegaPrev;
extern int omegaChangeCount;
extern float period;
extern float fpp;

extern double timeStep;
extern float inputFR;

extern double t;					// datafeed variables
extern double theta;
extern double omega;

extern vertex weightvert;

#endif
