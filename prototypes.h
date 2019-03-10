#ifndef PROTOTYPES
#define PROTOTYPES

#include "includes.h"
#include "struct.h"

void display( void );			//display.cc
void runanim( void );
void checkFPS( int );
void showFPS( void );
void glutSleep( int );
void glutLockFrameRate( float );
void drawString( GLuint , GLuint , void*, const char* );
int sign( double );
void drawRoom();
void drawTable();
void drawPendulum();

void drawBox( struct box* , vect3 , outline ol);		//boxy.cc
void defineBox( box* , vect3 , colortype );

void runanim(void);
void showFPS();
void glutSleep(int millisecondsToWait);
void glutLockFrameRate(float desiredFrameRate);
void drawString(GLuint x, GLuint y, void *font, const char* string);
int sign(double n);

void SpecialInput( int , int , int );		//input.cc
void keyboard( unsigned char , int , int );
vect3 cartToSph(vect3 a);
vect3 sphToCart(vect3 a);
vect3 vectUnit( vect3 );
vect3 vectDist( vect3 , vect3 );
vect3 vectCross( vect3 , vect3 );
float vectMagn( vect3 );
vect3 vectAdd( vect3 , vect3 );
vect3 vectMult( vect3 , float );

double thetadot( double , double , double );
double omegadot( double , double , double );
void step( double* , double* , double* , double );

int main( int , char** );		//main.cc
void reshape ( int , int );
void init( void );

#endif
