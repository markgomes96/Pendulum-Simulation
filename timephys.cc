#ifndef TIMEPHYS
#define TIMEPHYS

#include "includes.h"
#include "prototypes.h"
#include "globals.h"
#include "struct.h"

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
	//sprintf(charString, "Camera Position : %6.1f, %6.2f, %6.1f", cameraPos.x, cameraPos.y, cameraPos.z);

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

#endif
