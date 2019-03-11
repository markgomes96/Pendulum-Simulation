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

#ifdef TEXTURE
	glEnable(GL_TEXTURE_2D);	// enable texturing
#endif
	glEnable(GL_DEPTH_TEST);	// enable depth buffer

	drawRoom();
	drawTable();
	drawPendulum();

	showFPS();

	glutSwapBuffers();
#ifdef TEXTURE
	glDisable(GL_TEXTURE_2D);
#endif
    glDisable(GL_DEPTH_TEST);
}

void drawRoom()
{
	//glBindTexture(GL_TEXTURE_2D, textarray[0].textid);
	float tmp1[] = {0.0, 0.0, 0.0, 1.0, 1.0, 1.0, 1.0, 0.0};
	copy(begin(tmp1), std::end(tmp1), std::begin(textarray[0].textcoords));
	// Draw the room
	glPushMatrix();
		drawBox(&room[0], vect3(0.0, 0.0, 0.0), inside);
	glPopMatrix();
}

void drawTable()
{
	//glBindTexture(GL_TEXTURE_2D, textarray[3].textid);
	float tmp1[] = {0.0, 0.0, 0.0, 0.2, 1.0, 0.2, 1.0, 0.0};
	copy(begin(tmp1), std::end(tmp1), std::begin(textarray[1].textcoords));
	// Draw table leg 1
	glPushMatrix();
		drawBox(&tableLeg1[0], vect3(5.0, 5.0, -4.5), outside);
	glPopMatrix();

	// Draw table leg 2
	glPushMatrix();
		drawBox(&tableLeg2[0], vect3(-5.0, 5.0, -4.5), outside);
	glPopMatrix();

	// Draw table leg 3
	glPushMatrix();
		drawBox(&tableLeg3[0], vect3(-5.0, -5.0, -4.5), outside);
	glPopMatrix();

	// Draw table leg 4
	glPushMatrix();
		drawBox(&tableLeg4[0], vect3(5.0, -5.0, -4.5), outside);
	glPopMatrix();

	float tmp2[] = {0.0, 0.0, 0.0, 1.0, 1.0, 1.0, 1.0, 0.0};
	copy(begin(tmp2), std::end(tmp2), std::begin(textarray[1].textcoords));
	// Draw table face
	glPushMatrix();
		drawBox(&tableFace[0], vect3(0.0, 0.0, -2.90), outside);
	glPopMatrix();
}

void drawPendulum()
{
	//glBindTexture(GL_TEXTURE_2D, textarray[4].textid);
	float tmp1[] = {0.0, 0.0, 0.0, 1.0, 1.0, 1.0, 1.0, 0.0};
	copy(begin(tmp1), std::end(tmp1), std::begin(textarray[1].textcoords));
	// Draw the base
	glPushMatrix();
		drawBox(&penbase[0], vect3(0.0, 0.0, -2.6), outside);
	glPopMatrix();

#ifdef TEXTURE
	glBindTexture(GL_TEXTURE_2D, textarray[5].textid);
#endif
	// Draw the vertical pole of pendulum
	GLUquadric* quad = gluNewQuadric();
#ifdef TEXTURE
	gluQuadricTexture(quad, true);       		//Default: false
	glColor3f (1.0, 1.0, 1.0);
#else
	glColor3f(0.0, 1.0, 0.0);
#endif
	glPushMatrix();
		glTranslatef(-3.0, 3.0, -2.5);
		gluCylinder(quad,
		    (GLdouble) 0.2,		//base radius
		    (GLdouble) 0.2,		//top radius
		    (GLdouble) 6.5,		//hieght
		    (GLint)    10,		//slices
		    (GLint)    20 );		//stacks
	glPopMatrix();

	// Draw the horizontal pole of pendulum
	quad = gluNewQuadric();
#ifdef TEXTURE
	gluQuadricTexture(quad, true);       		//Default: false
	glColor3f (1.0, 1.0, 1.0);
#else
	glColor3f(0.0, 1.0, 0.0);
#endif
	glPushMatrix();
		glRotatef(90, 1, 0, 0);
		glRotatef(45, 0, 1, 0);
		glTranslatef(0.0, 4.0, -4.4);

		gluCylinder(quad,
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

		quad = gluNewQuadric();
#ifdef TEXTURE
		gluQuadricTexture(quad, true);       		//Default: false
		glColor3f (1.0, 1.0, 1.0);
#else
		glColor3f (1.0, 0.0, 1.0);
#endif
		// Draw ball weight of pendulum
		glTranslated( weightvert.x, weightvert.y, weightvert.z);
		gluSphere(quad,
		     (GLdouble) 0.5,		//radius
		     (GLint)     10,		//slices
		     (GLint)     10 );		//stacks
	glPopMatrix();
}

#endif
