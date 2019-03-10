#ifndef DISPLAY
#define DISPLAY

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

	gluLookAt( cameraPos.x,  cameraPos.y,  cameraPos.z,  		// Eye
			   targetPos.x,  targetPos.y,  targetPos.z,  		// Center
				0.0,  0.0,  1.0); 		// Up

	glEnable(GL_DEPTH_TEST);

	drawRoom();

	drawTable();

	drawPendulum();

	showFPS();

	glutSwapBuffers();
}

void drawRoom()
{
	// Draw the room
	glPushMatrix();
		drawBox(&room[0], vect3(0.0, 0.0, 2.0), inside);
	glPopMatrix();

	// Texture the room
}

void drawTable()
{
	// Draw the room
	glPushMatrix();
		drawBox(&tableLeg1[0], vect3(5.0, 5.0, -4.5), outside);
	glPopMatrix();

	// Draw the room
	glPushMatrix();
		drawBox(&tableLeg2[0], vect3(-5.0, 5.0, -4.5), outside);
	glPopMatrix();

	// Draw the room
	glPushMatrix();
		drawBox(&tableLeg3[0], vect3(-5.0, -5.0, -4.5), outside);
	glPopMatrix();

	// Draw the room
	glPushMatrix();
		drawBox(&tableLeg4[0], vect3(5.0, -5.0, -4.5), outside);
	glPopMatrix();

	// Draw the room
	glPushMatrix();
		drawBox(&tableFace[0], vect3(0.0, 0.0, -2.90), outside);
	glPopMatrix();
}

void drawPendulum()
{
	// Draw the base
	glPushMatrix();
		drawBox(&penbase[0], vect3(0.0, 0.0, -2.6), outside);
	glPopMatrix();

	// Draw the vertical pole of pendulum
	glPushMatrix();
		glColor3f(0.0, 1.0, 0.0);
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
		glRotatef(90, 1, 0, 0);
		glRotatef(45, 0, 1, 0);
		glTranslatef(0.0, 4.0, -4.4);

		gluCylinder(gluNewQuadric(),
		    (GLdouble) 0.2,		//base radius
		    (GLdouble) 0.2,		//top radius
		    (GLdouble) 4.75,		//hieght
		    (GLint)    10,		//slices
		    (GLint)    20 );		//stacks
	glPopMatrix();

	// Draw ball weight and tether of pendulum
	glPushMatrix();
		glRotatef(45, 0, 0, 1);
		// Draw tether between weight and top
		glLineWidth(5.0);
		glColor3f(0.0, 1.0, 1.0);
		glBegin ( GL_LINES );
			glVertex3f ( weightvert.x, weightvert.y, weightvert.z );
			glVertex3f ( 0.0, 0.0, 4.0 );
		glEnd();
		glLineWidth(5.0);

		// Draw ball weight of pendulum
		glColor3f (1.0, 0.0, 1.0);
		glTranslated( weightvert.x, weightvert.y, weightvert.z);
		gluSphere(gluNewQuadric(),
		     (GLdouble) 0.5,		//radius
		     (GLint)     10,		//slices
		     (GLint)     10 );		//stacks
	glPopMatrix();
}

#endif
