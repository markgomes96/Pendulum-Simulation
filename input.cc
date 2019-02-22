#include "includes.h"
#include "prototypes.h"
#include "globals.h"

void SpecialInput(int key, int x, int y)
{
	switch(key)		//moves the center point 5 pixels in inputed direction
	{
		case GLUT_KEY_UP:
			targetPos.z += 0.1;		//***quick fix ->improve by keeping same distance
		break;
			
		case GLUT_KEY_DOWN:
			targetPos.z -= 0.1;
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

void keyboard( unsigned char key, int x, int y )
{ 	
	if ( key == 'w' || key == 'W') 		//move forward
	{
		vect3 moveVect = vectMult(vectUnit(vectDist(cameraPos, targetPos)), 0.1);
		cameraPos = vectAdd(cameraPos, moveVect);
		targetPos = vectAdd(targetPos, moveVect);
	}
	if ( key == 's' || key == 'S') 		//move backward
	{
		vect3 moveVect = vectMult(vectUnit(vectDist(cameraPos, targetPos)), -0.1);
		cameraPos = vectAdd(cameraPos, moveVect);
		targetPos = vectAdd(targetPos, moveVect);
	}
	if ( key == 'd' || key == 'D') 		//move right
	{
		vect3 moveVect = vectMult(vectUnit(vectCross(vectDist(cameraPos, targetPos), vect3(cameraPos.x,cameraPos.y,cameraPos.z+10.0))), 0.1);
		moveVect.z = 0.0;
		cameraPos = vectAdd(cameraPos, moveVect);
		targetPos = vectAdd(targetPos, moveVect);
	}
	if ( key == 'a' || key == 'A') 		//move left
	{
		vect3 moveVect = vectMult(vectUnit(vectCross(vectDist(cameraPos, targetPos), vect3(cameraPos.x,cameraPos.y,cameraPos.z+10.0))), -0.1);
		moveVect.z = 0.0;
		cameraPos = vectAdd(cameraPos, moveVect);
		targetPos = vectAdd(targetPos, moveVect);
	}

	if ( key == 'q' || key == 'Q') 		//exit the program
	{
		printf("FARWELL, POWERING OFFFF...\n");
		exit(0);
	}
	glutPostRedisplay();
}

vect3 vectUnit(vect3 a)
{
	float magn = vectMagn(a);
	return vect3( (a.x/magn) , (a.y/magn) , (a.z/magn) );
}

vect3 vectDist(vect3 a, vect3 b)
{
	return vect3(b.x - a.x, b.y - a.y, b.z - a.z);
}

vect3 vectCross(vect3 a, vect3 b)
{
	return vect3( (a.y * b.z) - (b.y * a.z), 
				  (b.x * a.z) - (a.x * b.z),
			      (a.x * b.y) - (b.x * a.y));
}

float vectMagn(vect3 a)
{
	return sqrt( (a.x*a.x) + (a.y*a.y) + (a.z*a.z) );
}

vect3 vectAdd(vect3 a, vect3 b)
{
	return vect3(a.x + b.x, a.y + b.y, a.z + b.z);
}

vect3 vectMult(vect3 a, float scalar)
{
	return vect3(a.x * scalar, a.y * scalar, a.z * scalar);
}


