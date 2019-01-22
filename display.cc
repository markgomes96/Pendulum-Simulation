#include "includes.h"
#include "prototypes.h"
#include "globals.h"

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

    glColor3f (1.0, 0.0, 1.0);
    glRotatef(rotZ, 0, 0, 1);
    glRotatef(rotX, 1, 0, 0);
    glTranslatef( 0.0, 0.0, -1.0);
    
    gluSphere(gluNewQuadric(), 
             (GLdouble) 0.5,		//radius
             (GLint)     10,		//slices
             (GLint)     10 );		//stacks

    // Draw tether between weight and top
    glLineWidth(5.0);
    glColor3f(0.0, 1.0, 1.0);
    glBegin ( GL_LINES );
	glVertex3f ( 0.0, 0.0, 0.0 );
	glVertex3f ( 0.0, 0.0, 5.0 );
    glEnd();
    glLineWidth(5.0);

    glPopMatrix();

    frames++;
    glutSwapBuffers();
}

void runanim(void)
{
	glutPostRedisplay();
}

void checkFPS(int val)
{
	if(0 != val)
	{
		printf("The framerate is %d fps. \n", frames);
	}

	frames = 0;
	glutTimerFunc(1000, checkFPS, 1);
}
