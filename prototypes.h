#ifndef PROTOTYPES
#define PROTOTYPES

#include "includes.h"
#include "struct.h"

// display.cc
void display( void );
void drawGraph();
void constrainCamera( void );
void drawSpotLight();
void drawRoom();
void drawTable();
void drawPendulum();

// boxy.cc
void drawBox( struct box* , vect3 , outline o);
void defineBox( box* , vect3 , colortype, GLuint* );

// timephys.cc
void runanim(void);
void showFPS();
void glutSleep(int millisecondsToWait);
void glutLockFrameRate(float desiredFrameRate);
void drawString(GLuint x, GLuint y, void *font, const char* string);
int sign(double n);

// input.cc
void SpecialInput( int , int , int );
void keyboard( unsigned char , int , int );
vect3 cartToSph(vect3 a);
vect3 sphToCart(vect3 a);
vect3 vectUnit( vect3 );
vect3 vectDist( vect3 , vect3 );
vect3 vectCross( vect3 , vect3 );
float vectMagn( vect3 );
vect3 vectAdd( vect3 , vect3 );
vect3 vectMult( vect3 , float );

// pend.c
double thetadot( double , double , double );
double omegadot( double , double , double );
void step( double* , double* , double* , double );

// main.cc
int main( int , char** );
void reshape ( int , int );
void init( void );
void textureLoader( int , string );

#endif
