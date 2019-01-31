#include "includes.h"
#include "struct.h"

void display( void );			//display.cc
void runanim( void );
void checkFPS( int );
void showFPS( void );
void drawString( GLuint , GLuint , void*, const char* );
int sign( int );

void SpecialInput( int , int , int );		//input.cc
void keyboard( unsigned char , int , int );

double thetadot( double , double , double );
double omegadot( double , double , double );
void step( double* , double* , double* );

int main( int , char** );		//main.cc
void reshape ( int , int );
void init( void );
