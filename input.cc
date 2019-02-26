#include "includes.h"
#include "prototypes.h"
#include "globals.h"

void SpecialInput(int key, int x, int y)
{
	vect3 panCoord;

	switch(key)
	{
		case GLUT_KEY_UP:			// pan up
			panCoord = cartToSph(vectDist(cameraPos, targetPos));	// convert cartesian to spherical
			panCoord.z = panCoord.z - 1.5;						// increment spherical
			if(panCoord.z > 0)
			{ 
				targetPos = vectAdd(cameraPos, sphToCart(panCoord));	// convert spherical back to cartesian
			}
		break;
			
		case GLUT_KEY_DOWN:			// pan down
			panCoord = cartToSph(vectDist(cameraPos, targetPos));	// convert cartesian to spherical
			panCoord.z = panCoord.z + 1.5;						// increment spherical
			if(panCoord.z < 180)
			{ 
				targetPos = vectAdd(cameraPos, sphToCart(panCoord));	// convert spherical back to cartesian
			}
		break;

		case GLUT_KEY_RIGHT:		// pan right
			panCoord = cartToSph(vectDist(cameraPos, targetPos));	// convert cartesian to spherical
			panCoord.y = panCoord.y - 1.5;						// increment spherical
			targetPos = vectAdd(cameraPos, sphToCart(panCoord));	// convert spherical back to cartesian
		break;
			
		case GLUT_KEY_LEFT:			// pan left
			panCoord = cartToSph(vectDist(cameraPos, targetPos));	// convert cartesian to spherical
			panCoord.y = panCoord.y + 1.5;						// increment spherical
			targetPos = vectAdd(cameraPos, sphToCart(panCoord));	// convert spherical back to cartesian
		break;

		case GLUT_KEY_PAGE_UP:		// move up
			cameraPos.z = cameraPos.z + 0.5;
			targetPos.z = targetPos.z + 0.5;
		break;

		case GLUT_KEY_PAGE_DOWN:	// move down
			cameraPos.z = cameraPos.z - 0.5;
			targetPos.z = targetPos.z - 0.5;
		break;
	}

	glutPostRedisplay();
}

void keyboard( unsigned char key, int x, int y )
{ 	
	if ( key == 'w' || key == 'W') 		// move forward
	{
		vect3 moveVect = vectMult(vectUnit(vectDist(cameraPos, targetPos)), 0.5);
		cameraPos = vectAdd(cameraPos, moveVect);
		targetPos = vectAdd(targetPos, moveVect);
	}
	if ( key == 's' || key == 'S') 		// move backward
	{
		vect3 moveVect = vectMult(vectUnit(vectDist(cameraPos, targetPos)), -0.5);
		cameraPos = vectAdd(cameraPos, moveVect);
		targetPos = vectAdd(targetPos, moveVect);
	}
	if ( key == 'd' || key == 'D') 		// move right
	{
		vect3 moveVect = vectMult(vectUnit(vectCross(vectDist(cameraPos, targetPos), vect3(cameraPos.x,cameraPos.y,cameraPos.z+10.0))), 0.5);
		moveVect.z = 0.0;
		cameraPos = vectAdd(cameraPos, moveVect);
		targetPos = vectAdd(targetPos, moveVect);
	}
	if ( key == 'a' || key == 'A') 		// move left
	{
		vect3 moveVect = vectMult(vectUnit(vectCross(vectDist(cameraPos, targetPos), vect3(cameraPos.x,cameraPos.y,cameraPos.z+10.0))), -0.5);
		moveVect.z = 0.0;
		cameraPos = vectAdd(cameraPos, moveVect);
		targetPos = vectAdd(targetPos, moveVect);
	}

	if ( key == 'q' || key == 'Q') 		// exit the program
	{
		printf("FARWELL, POWERING OFFFF...\n");
		exit(0);
	}
	glutPostRedisplay();
}

vect3 cartToSph(vect3 a)
{
	vect3 sph;
	sph.x = vectMagn(a);										// radius
	sph.y = atan2(a.y , a.x) * (180/M_PI);									// thetha
	sph.z = atan2( sqrt( (a.x*a.x) + (a.y*a.y) ) , a.z ) * (180/M_PI);		// phi

	return sph;
}

vect3 sphToCart(vect3 a)
{
	vect3 cart;
	cart.x = a.x * sin(a.z*M_PI/180.0) * cos(a.y*M_PI/180.0);
	cart.y = a.x * sin(a.z*M_PI/180.0) * sin(a.y*M_PI/180.0);
	cart.z = a.x * cos(a.z*M_PI/180.0);

	return cart;
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


