#include "includes.h"
#include "prototypes.h"
#include "globals.h"

void display(void)
{
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    glLoadIdentity();   	//call this before setting the viewing position 

    //we are going to set our position to be down the Y-Axis looking at the
    //center of the coordinate frame.  The positive Z-Axis will be up.

    gluLookAt( 20.0,   0.0, 5.0,  // Eye
                0.0,   0.0, 0.0,  // Center
                0.0,   0.0, 1.0); // Up

    glEnable(GL_DEPTH_TEST);

    glColor3f(0.0,1.0,0.0);

    // This should be to draw a cylinder 
    glPushMatrix();
    glRotatef(90.0, 1.0, 0.0, 0.0);
    glTranslatef(0.0, 0.0, -3.0);
    glScalef(3.0, 0.6, 3.0);
    //glRotatef(90.0, 0.0, 1.0, 0.0);
    glColor3f (0.0,0.0,1.0);
    gluCylinder(gluNewQuadric(), 
            (GLdouble) 2,		//base radius
            (GLdouble) 2,		//top radius
            (GLdouble) 2,		//hieght
            (GLint)    4,		//slices
            (GLint)    20 );		//stacks
    glPopMatrix();

/*
    // This should draw a green doughnut 
    glPushMatrix();
    glRotated(90.0,0,1,0);
    glTranslatef(2.0,0.0,0.0);
    glColor3f (0.0,1.0,0.0);
    gluDisk(gluNewQuadric(), 
            (GLdouble) 0.5,
            (GLdouble) 1.0,
            (GLint)     10,
            (GLint)     20 );
    glPopMatrix();

    // This should draw a red sphere 
    glPushMatrix();
    glTranslatef(-3.0,1.0,1.0);
    glColor3f (1.0,0.0,0.0);
    gluSphere(gluNewQuadric(), 
             (GLdouble) 1.5,
             (GLint)     10,
             (GLint)     10 );
    glPopMatrix();

    // This should draw a purple ellipsoid 
    glPushMatrix();
    glTranslatef(-3.0,1.0,-4.0);
    glScalef(0.5,0.5,1.0);
    glColor3f (1.0,0.0,1.0);
    gluSphere(gluNewQuadric(), 
             (GLdouble) 1.5,
             (GLint)     10,
             (GLint)     10 );
    glPopMatrix();
*/

    glutSwapBuffers();
}
