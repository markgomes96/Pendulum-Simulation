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

	constrainCamera();

	gluLookAt( cameraPos.x,  cameraPos.y,  cameraPos.z,  		// Eye
			   targetPos.x,  targetPos.y,  targetPos.z,  		// Center
				0.0,  0.0,  1.0); 		// Up

#ifdef LIGHTING
	// material prameters
	GLfloat mat_ambient[] = { 0.3, 0.3, 0.3, 1.0 };
	GLfloat mat_diffuse[] = { 0.1, 0.5, 0.8, 1.0 };
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat no_shininess[] = { 0.0 };
	GLfloat low_shininess[] = { 5.0 };
	GLfloat high_shininess[] = { 100.0 };
	GLfloat mat_emission[] = {0.3, 0.2, 0.2, 0.0};
	GLfloat emission_on[] = { 0.5, 0.5, 0.5, 1.0};
	GLfloat on[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat off[] = { 0.0, 0.0, 0.0, 1.0};

	// handle lighting position
	GLfloat position0[] = { lightPos.x, lightPos.y, lightPos.z, 1.0 };
	glLightfv (GL_LIGHT0, GL_POSITION, position0);
#endif

#ifdef TEXTURE
	glEnable(GL_TEXTURE_2D);	// enable texturing
#endif
	glEnable(GL_DEPTH_TEST);	// enable depth buffer

#ifdef LIGHTING
	// draw light position for testing
	glDisable(GL_LIGHTING);
	glPushMatrix();
	glColor3f(1.0, 1.0, 0.0);
	glTranslatef( lightPos.x, lightPos.y, lightPos.z);
	gluSphere(gluNewQuadric(),				//head
		(GLdouble) 0.5,			//radius
		(GLint)		10,			//slice
		(GLint)		10 );		//stacks
	glPopMatrix();
	glEnable(GL_LIGHTING);
#endif

#ifdef LIGHTING
	// material properties for Room
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT,   mat_ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE,   mat_diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR,  mat_specular);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, low_shininess);
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION,  mat_emission);
#endif
	drawRoom();

#ifdef LIGHTING
	// material properties for Table
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT,   mat_ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE,   mat_diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR,  mat_specular);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, low_shininess);
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION,  mat_emission);
#endif
	drawTable();

	drawPendulum();

#ifdef LIGHTING
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT,   off);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE,   off);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR,  off);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, off);
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION,  off);
#endif

	showFPS();

	glutSwapBuffers();
#ifdef TEXTURE
	glDisable(GL_TEXTURE_2D);
#endif
    glDisable(GL_DEPTH_TEST);
}

// constrains camera based camera bounds variable
void constrainCamera()
{
	float buffer = 0.3;
	bool hitBounds = false;

	// x constraints
	if( cameraPos.x < (cambounds[0] + buffer) )
		hitBounds = true;
	else if( cameraPos.x > (cambounds[1] - buffer) )
		hitBounds = true;

	// y constraints
	if( cameraPos.y < (cambounds[2] + buffer) )
		hitBounds = true;
	else if(cameraPos.y > (cambounds[3] - buffer) )
		hitBounds = true;

	// z constraints
	if(cameraPos.z < (cambounds[4] + buffer) )
		hitBounds = true;
	else if(cameraPos.z > (cambounds[5] - buffer) )
		hitBounds = true;

	// adjust target position
	if(hitBounds)
	{
		cameraPos = oldCamPos;
		targetPos = oldTarget;
	}

	// record last cam and target positions
	oldCamPos = cameraPos;
	oldTarget = targetPos;
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
#ifdef LIGHTING
	// material prameters
	GLfloat mat_ambient[] = { 0.3, 0.3, 0.3, 1.0 };
	GLfloat mat_diffuse[] = { 0.1, 0.5, 0.8, 1.0 };
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat no_shininess[] = { 0.0 };
	GLfloat low_shininess[] = { 5.0 };
	GLfloat high_shininess[] = { 100.0 };
	GLfloat mat_emission[] = {0.3, 0.2, 0.2, 0.0};
	GLfloat emission_on[] = { 0.5, 0.5, 0.5, 1.0};
	GLfloat on[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat off[] = { 0.0, 0.0, 0.0, 1.0};


	// material properties for pendulum base
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT,   mat_ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE,   mat_diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR,  mat_specular);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, low_shininess);
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION,  mat_emission);
#endif

	//glBindTexture(GL_TEXTURE_2D, textarray[4].textid);
	float tmp1[] = {0.0, 0.0, 0.0, 1.0, 1.0, 1.0, 1.0, 0.0};
	copy(begin(tmp1), std::end(tmp1), std::begin(textarray[1].textcoords));
	// Draw the base
	glPushMatrix();
		drawBox(&penbase[0], vect3(0.0, 0.0, -2.6), outside);
	glPopMatrix();

#ifdef LIGHTING
	// material properties for metal pendulum parts
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT,   mat_ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE,   mat_diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR,  mat_specular);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, high_shininess);
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION,  mat_emission);
#endif

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
