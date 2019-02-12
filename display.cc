#include "includes.h"
#include "prototypes.h"
#include "globals.h"
#include "struct.h"

void display(void)
{
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	glLoadIdentity();   	//call this before setting the viewing position 

	//we are going to set our position to be down the Y-Axis looking at the
	//center of the coordinate frame.  The positive Z-Axis will be up.

	gluLookAt( 20.0,   2.0, 2.5,  // Eye
		0.0,   0.0, 0.0,  // Center
		0.0,   0.0, 1.0); // Up

	glEnable(GL_DEPTH_TEST);

	glColor3f(0.0,1.0,0.0);

	// Draw the base 
	glPushMatrix();

	glColor3f (0.0,0.0,1.0);
	glRotatef(rotZ, 0, 0, 1);
	glRotatef(rotX, 1, 0, 0);
	glTranslatef(0.0, 0.0, -3.5);

	gluCylinder(gluNewQuadric(), 
	    (GLdouble) 7,		//base radius
	    (GLdouble) 7,		//top radius
	    (GLdouble) 1,		//hieght
	    (GLint)    4,		//slices
	    (GLint)    20 );		//stacks

	glPolygonMode(GL_FRONT, GL_FILL);
	glPolygonMode(GL_BACK, GL_FILL);

	glColor3f(1.0, 0.0, 0.0);
	glRotatef(45, 0, 0, 1);
	glBegin ( GL_POLYGON );
		glVertex3f ( 4.95, 4.95, 1 );
		glVertex3f ( -4.95, 4.95, 1 );	
		glVertex3f ( -4.95, -4.95, 1 );
		glVertex3f ( 4.95, -4.95, 1 );
	glEnd();

	glPopMatrix();

	// Draw the vertical pole of pendulum 
	glPushMatrix();

	glColor3f(0.0, 1.0, 0.0);
	glRotatef(rotZ, 0, 0, 1);
	glRotatef(rotX, 1, 0, 0);
	glTranslatef(-3.0, 3.0, -2.5);

	gluCylinder(gluNewQuadric(), 
	    (GLdouble) 0.2,		//base radius
	    (GLdouble) 0.2,		//top radius
	    (GLdouble) 6.5,		//hieght
	    (GLint)    10,		//slices
	    (GLint)    20 );		//stacks

	glPopMatrix();

	// Draw the horizontal pole of pendulum
	glPushMatrix();

	glColor3f(0.0, 1.0, 0.0);
	glRotatef(rotZ, 0, 0, 1);
	glRotatef(90 + rotX, 1, 0, 0);
	glRotatef(45, 0, 1, 0);
	glTranslatef(0.0, 4.0, -4.4);

	gluCylinder(gluNewQuadric(), 
	    (GLdouble) 0.2,		//base radius
	    (GLdouble) 0.2,		//top radius
	    (GLdouble) 4.75,		//hieght
	    (GLint)    10,		//slices
	    (GLint)    20 );		//stacks

	glPopMatrix();

	// Draw ball weight of pendulum 
	glPushMatrix();

	glRotatef(rotZ, 0, 0, 1);
	glRotatef(rotX, 1, 0, 0);
	// Draw tether between weight and top
	glLineWidth(5.0);
	glColor3f(0.0, 1.0, 1.0);
	glBegin ( GL_LINES );
		glVertex3f ( weightvert.x, weightvert.y, weightvert.z );
		glVertex3f ( 0.0, 0.0, 4.0 );
	glEnd();
	glLineWidth(5.0);

	glColor3f (1.0, 0.0, 1.0);
	glTranslated( weightvert.x, weightvert.y, weightvert.z);

	gluSphere(gluNewQuadric(), 
	     (GLdouble) 0.5,		//radius
	     (GLint)     10,		//slices
	     (GLint)     10 );		//stacks

	glPopMatrix();

	glPushMatrix();		//move cone man over to corner

	glRotatef(rotZ, 0, 0, 1);
    	glRotatef(rotX, 1, 0, 0);
	glTranslated( 0.0, 5.0, -0.5);

	// Draw cone man for scale
	glPushMatrix();
	
	glColor3f(1.0, 1.0, 0.0);

	glTranslated( 0, 0, 2.7);
	gluSphere(gluNewQuadric(),				//head
		(GLdouble) 0.5,			//radius
		(GLint)		10,			//slice 
		(GLint)		10 );		//stacks

	glColor3f(0.5, 0, 0.5);
	
	glTranslated( 0, 0, -3.0);
	gluCylinder(gluNewQuadric(),			//body
        (GLdouble) 0.5,     	//base radius
        (GLdouble) 1.0,     	//top radius
        (GLdouble) 2.5,         //hieght
        (GLint)      8,      	//slices
        (GLint)     20 );       //stacks

	glColor3f(0, 0.5, 0.5);

	glTranslated( -0.25, -0.25, -1.7);				//right leg
	gluCylinder(gluNewQuadric(),
		(GLdouble) 0.1,         //base radius
        (GLdouble) 0.25,         //top radius
        (GLdouble) 2.0,         //hieght
        (GLint)      6,         //slices
        (GLint)     20 );       //stacks

	glTranslated( 0.5, 0.5, 0);                 //left leg
    	gluCylinder(gluNewQuadric(),
        (GLdouble) 0.1,         //base radius
        (GLdouble) 0.25,         //top radius
        (GLdouble) 2.0,         //hieght
        (GLint)      6,         //slices
        (GLint)     20 );       //stacks
	
	glPopMatrix();
	
	glPushMatrix();

	glRotatef( 20, 1, -1, 0);

	glPushMatrix();
	
	glTranslated( 0.9, 0.9, -0.2);                 //right arm 
	gluCylinder(gluNewQuadric(),
        (GLdouble) 0.1,         //base radius
        (GLdouble) 0.25,         //top radius
        (GLdouble) 1.8,         //hieght
        (GLint)      6,         //slices
        (GLint)     20 );       //stacks

	glPopMatrix();

	glRotatef( -40, 1, -1, 0);

	glPushMatrix();

	glTranslated( -0.9, -0.9, -0.2);                 //left arm
	gluCylinder(gluNewQuadric(),
        (GLdouble) 0.1,         //base radius
        (GLdouble) 0.25,         //top radius
        (GLdouble) 1.8,         //hieght
        (GLint)      6,         //slices
        (GLint)     20 );       //stacks

	glPopMatrix();

	glPopMatrix();

	glPopMatrix();

	showFPS();
	
	glutSwapBuffers();
}

void runanim(void)
{
	step( &t, &theta, &omega, timeStep);

	weightvert.x = 3 * sin(theta);
	weightvert.z = (3 * -cos(theta)) + 4;

	if(inputFR != 0.0)
		glutLockFrameRate(inputFR);	//lock framerate at 60 fps

	glutPostRedisplay();
}

void showFPS()
{
	frames++;
	int currentTime = glutGet(GLUT_ELAPSED_TIME);
	
	if(currentTime - oldTime > 1000)		//handle fps
	{
		fps = frames*1000.0/(currentTime-oldTime);
		oldTime = currentTime;
		frames = 0;
		
		if(inputFR != 0.0)
			timeStep = (1.0 / fps);		//calc physics time per frame
	}

	if(sign(omega) != sign(omegaPrev))		//handle period, fpp
	{
		if(omegaChangeCount == 2)		//second omega change
		{
			period = ( (float)currentTime - (float)periodStartTime ) / 1000.0;	//get period in seconds

			fpp = fps * period;		//frames per period

			//frameWait = (1.0 / (fpp / 2.0)) * 1000;

			omegaChangeCount = 0;
		}	
		
		if(omegaChangeCount == 1)		//first omega change
		{
			omegaPrev = omega;
			omegaChangeCount++;
		}

		if(omegaChangeCount == 0)	//start period recording
		{
			periodStartTime = currentTime;
			omegaPrev = omega;
			omegaChangeCount++;
		}
	}	

	//define string to hold framerat 
	char *charString = (char*) malloc(45*sizeof(char));
	sprintf(charString, "FPS: %6.1f  |  Period: %6.2f  |  FPP: %6.1f", fps, period, fpp);
	

	//set up 2d projection
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0.0, 500.0, 0.0, 500.0);

	//switch back to modelview to draw tex
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	
	glColor3f(255,255,0);
	drawString(25, 25, GLUT_BITMAP_HELVETICA_12, charString);

	//move back to 3D space
	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);

	free(charString);
}

void glutSleep(int millisecondsToWait)
{
	int startTime = glutGet(GLUT_ELAPSED_TIME);

	do{/*wait*/}
	while((glutGet(GLUT_ELAPSED_TIME) - startTime) < millisecondsToWait);
}

void glutLockFrameRate(float desiredFrameRate)
{
	int millisecondsToWait = (int)((1.0 / desiredFrameRate) * 1000);
	
	int startTime = glutGet(GLUT_ELAPSED_TIME);

	do{/*wait*/}
	while((glutGet(GLUT_ELAPSED_TIME)-startTime) < millisecondsToWait);
}

void drawString(GLuint x, GLuint y, void *font, const char* string)
{
	const char *c;
	glRasterPos2i(x, y);

	for(c=string; *c!='\0'; c++)
	{
		glutBitmapCharacter(font, *c);
	}
}

int sign(double n)
{
	return (n > 0) ? 1 : ((n < 0) ? -1 : 0);
}

