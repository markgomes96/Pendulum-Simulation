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

	//glPushMatrix();

	glColor3f(1.0, 0.0, 0.0);
	glRotatef(45, 0, 0, 1);
	glBegin ( GL_POLYGON );
		glVertex3f ( 4.95, 4.95, 1 );
		glVertex3f ( -4.95, 4.95, 1 );	
		glVertex3f ( -4.95, -4.95, 1 );
		glVertex3f ( 4.95, -4.95, 1 );
	glEnd();

	//glPopMatrix();

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
	//glTranslatef( 0.0, 0.0, -1.0);
	glTranslated( weightvert.x, weightvert.y, weightvert.z);

	gluSphere(gluNewQuadric(), 
	     (GLdouble) 0.5,		//radius
	     (GLint)     10,		//slices
	     (GLint)     10 );		//stacks

	glPopMatrix();

	showFPS();
	glutSwapBuffers();
}

void runanim(void)
{
	step( &t, &theta, &omega);
	//printf("%f %f %f\n", t, theta, omega);

	weightvert.x = 3 * sin(theta);
	weightvert.z = (3 * -cos(theta)) + 3;

	glutPostRedisplay();
}

void showFPS()
{
	static float fps;
	
	//declare static will retain value between func calls
	frames++;
	int currentTime=glutGet(GLUT_ELAPSED_TIME);

	if(currentTime - oldTime > 1000)
	{
		fps = frames*1000.0/(currentTime-oldTime);
		oldTime = currentTime;
		frames = 0;
	}

	//define string to hold framerat 
	char *charString = (char*) malloc(12*sizeof(char));
	sprintf(charString, "FPS: %6.1f", fps);

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
	drawString(50, 50, GLUT_BITMAP_HELVETICA_12, charString);

	//move back to 3D space
	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);

	free(charString);
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
