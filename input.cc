#include "includes.h"
#include "prototypes.h"
#include "globals.h"

void SpecialInput(int key, int x, int y)
{
	switch(key)		//moves the center point 5 pixels in inputed direction
	{
		case GLUT_KEY_UP:
			rotX--;
		break;
			
		case GLUT_KEY_DOWN:
			rotX++;
		break;

		case GLUT_KEY_RIGHT:
			rotZ++;
		break;
			
		case GLUT_KEY_LEFT:
			rotZ--;
		break;
	}

	if(rotZ > 360)
		rotZ -= 360.0;

	if(rotX > 360)
		rotX -= 360.0;

	glutPostRedisplay();
}
