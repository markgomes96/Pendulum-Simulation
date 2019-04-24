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
	GLfloat mat_ambient[] = { 0.1, 0.1, 0.1, 1.0 };
	GLfloat mat_diffuse[] = { 0.1, 0.5, 0.8, 1.0 };
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat low_shininess[] = { 5.0 };
	GLfloat high_shininess[] = { 100.0 };
	GLfloat mat_emission[] = {0.3, 0.2, 0.2, 0.0};
	GLfloat emission_on[] = { 0.5, 0.5, 0.5, 1.0};

	// setup some material properties
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glColorMaterial(GL_FRONT, GL_SPECULAR);

	// draw overhead light
	float *light0 = (float*) malloc(4*sizeof(float));
	light0[0]= lightPos.x; light0[1] = lightPos.y; light0[2] = lightPos.z; light0[3] = 1.0;
	glLightfv(GL_LIGHT0, GL_POSITION, light0);
	light0[0]= 0.1; light0[1] = 0.1; light0[2] = 0.1; light0[3] = 1.0;
	glLightfv(GL_LIGHT1, GL_AMBIENT, light0);
	light0[0]= 0.5; light0[1] = 0.0; light0[2]= 0.0; light0[3] = 1.0;
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light0);

	// draw spotlight
	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 45.0);
	glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 100.0);
	glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, 0.0);

	// specify spotlight postion and properties
	float *light1 = (float*) malloc(4*sizeof(float));
	light1[0]= splightPos.x; light1[1] = splightPos.y; light1[2]= splightPos.z; light1[3] = 1.0;
	glLightfv(GL_LIGHT1, GL_POSITION, light1);
	light1[0]= 0.0; light1[1] = 0.0; light1[2]=0.0; light1[3] = 1.0;
	glLightfv(GL_LIGHT1, GL_AMBIENT, light1);
	light1[0]= 1.0; light1[1] = 1.0; light1[2]= 1.0; light1[3] = 1.0;
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light1);
	glLightfv(GL_LIGHT1, GL_SPECULAR, light1);

	// specify spotlight direction
	vect3 splightDir = vectUnit(vectDist(splightPos, splightTarget));
	float *direction = (float*) malloc(3*sizeof(float));
	direction[0]= splightDir.x; direction[1] = splightDir.y; direction[2]= splightDir.z;
	//direction[0]= -splightPos.x; direction[1] = -splightPos.y; direction[2]= -splightPos.z;
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, direction);

	/* Turn on Lighting */
	glShadeModel(GL_SMOOTH);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHTING);
#endif

#ifdef TEXTURE
	glEnable(GL_TEXTURE_2D);	// enable texturing
#endif
	glEnable(GL_DEPTH_TEST);	// enable depth buffer

#ifdef LIGHTING
	glDisable(GL_LIGHTING);
	// draw overhead light position
	glPushMatrix();
	glColor3f(1.0, 1.0, 0.0);
	glTranslatef( lightPos.x, lightPos.y, lightPos.z);
	gluSphere(gluNewQuadric(),				//head
		(GLdouble) 0.5,			//radius
		(GLint)		10,			//slice
		(GLint)		10 );		//stacks
	glPopMatrix();

	// draw spotlight position
	glPushMatrix();
	glColor3f(1.0, 0.0, 0.0);
	glTranslatef( splightPos.x, splightPos.y, splightPos.z);
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

	drawSpotLight();

	showFPS();

	if(displayGraph)
		drawGraph();

	glutSwapBuffers();

	glDisable(GL_DEPTH_TEST);
#ifdef TEXTURE
	glDisable(GL_TEXTURE_2D);
#endif
#ifdef LIGHTING
	free(light0);
	free(light1);
	free(direction);
	glDisable(GL_LIGHTING);
#endif
}

void drawGraph()
{
	//set up 2d projection
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0.0, WINDOW_MAX_X, 0.0, WINDOW_MAX_Y);

	//switch back to modelview to draw tex
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

#ifdef TEXTURE
	glDisable(GL_TEXTURE_2D);
#endif
#ifdef LIGHTING
	glDisable(GL_LIGHTING);
#endif

	float xsize = 450;	float ysize = 350;
	float minX = WINDOW_MAX_X-xsize;   float minY = 0.0;
	float maxX = WINDOW_MAX_X;	       float maxY = ysize;

	// draw graph axis
	glLineWidth(0.5);
	glColor3f (0.0, 0.0, 0.0);
	float gbx = 90;
	float gby = 45.0;
	glBegin ( GL_LINES );
		// X axis
		glVertex2f ( minX+gbx , minY+gby );
		glVertex2f ( maxX-15 , minY+gby );

		// Y axis
		glVertex2f ( minX+gbx , minY+gby );
		glVertex2f ( minX+gbx , maxY-15 );
	glEnd();

	// label axis and title
	char *charString = (char*) malloc(15*sizeof(char));
	// X axis
	sprintf(charString, "theta");
	drawString( minX+(xsize/2), minY+4, GLUT_BITMAP_HELVETICA_12, charString);
	// Y axis
	sprintf(charString, "dtheta/dt");
	drawString( minX, minY+(ysize/2), GLUT_BITMAP_HELVETICA_12, charString);

	float gxstart =	minX+gbx;		// axis starts
	float gystart =	minY+gby;
	float gxsize = (maxX-15)-(minX+gbx);		// axis sizes
	float gysize = (maxY-15)-(minY+gby);

	// draw grid marks
	float ts = 5;
	int tnum = 6;
	float gi = gxsize/tnum;
	string xgn[7] = {"-3PI/4","-PI/2","-PI/4","  0","PI/4","PI/2","3PI/4"};
	for(int i = 0; i <= tnum; i++)	// x axis
	{
		glBegin ( GL_LINES );
			glVertex2f ( gxstart+(gi*i) , gystart+ts );
			glVertex2f ( gxstart+(gi*i) , gystart-ts );
		glEnd();

		sprintf(charString, "%s", xgn[i].c_str());
		drawString( gxstart+(gi*i)-15, gystart-(ts*4), GLUT_BITMAP_HELVETICA_12, charString);
	}

	tnum = 8;
	gi = gysize/tnum;
	string ygn[9] = {"-4","-3","-2","-1","  0","  1","  2","  3","  4"};
	for(int i = 0; i <= tnum; i++)	// y axis
	{
		glBegin ( GL_LINES );
			glVertex2f ( gxstart+ts , gystart+(gi*i) );
			glVertex2f ( gxstart-ts , gystart+(gi*i) );
		glEnd();

		sprintf(charString, "%s", ygn[i].c_str());
		drawString( gxstart-25, gystart+(gi*i)-2, GLUT_BITMAP_HELVETICA_12, charString);
	}

	// draw white background (last for some unknown reason?)
	glColor3f (1.0, 1.0, 1.0);
	glBegin ( GL_POLYGON );
		glVertex2f ( minX , minY );
		glVertex2f ( maxX , minY );
		glVertex2f ( maxX , maxY );
		glVertex2f ( minX , maxY );
	glEnd();

#ifdef TEXTURE
	glEnable(GL_TEXTURE_2D);
#endif
#ifdef LIGHTING
	glEnable(GL_LIGHTING);
#endif

	//move back to 3D space
	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
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

void drawSpotLight()
{
#ifdef LIGHTING
	// material prameters
	GLfloat mat_ambient[] = { 0.1, 0.1, 0.1, 1.0 };
	GLfloat mat_diffuse[] = { 0.1, 0.4, 0.7, 1.0 };
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat high_shininess[] = { 100.0 };
	GLfloat mat_emission[] = {0.3, 0.2, 0.2, 0.0};

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
		glTranslatef(-9.8, -9.2, -6.0);
		gluCylinder(quad,
		    (GLdouble) 0.2,		//base radius
		    (GLdouble) 0.2,		//top radius
		    (GLdouble) 10.0,		//hieght
		    (GLint)    15,		//slices
		    (GLint)    30 );		//stacks
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
		glRotatef(75, 1, 0, 0);
		glRotatef(135, 0, 1, 0);
		glTranslatef(0.0, 1.0, -14.0);
		gluCylinder(quad,
		    (GLdouble) 0.3,		//base radius
		    (GLdouble) 1.2,		//top radius
		    (GLdouble) 1.8,		//hieght
		    (GLint)    15,		//slices
		    (GLint)    30 );		//stacks
	glPopMatrix();
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
	GLfloat mat_ambient[] = { 0.1, 0.1, 0.1, 1.0 };
	GLfloat mat_diffuse[] = { 0.1, 0.4, 0.7, 1.0 };
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat low_shininess[] = { 40.0 };
	GLfloat high_shininess[] = { 100.0 };
	GLfloat mat_emission[] = {0.3, 0.2, 0.2, 0.0};

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
