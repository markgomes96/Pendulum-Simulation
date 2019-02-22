// Mark Gomes
// Pendulum Project
// CSC 415
// 2/7/19

#include "includes.h"
#include "globals.h"
#include "globals.cc"
#include "prototypes.h"
#include "struct.h"

/*
*Add vert struct to store wieght position
*Add animation for wieght position
*Connect animation to real physics
*/

void init(void) 
{
	glClearColor (0.0, 0.0, 0.0, 0.0);
	glLoadIdentity();
}

void reshape (int w, int h)
{
	glViewport (0, 0, (GLsizei) w, (GLsizei) h);
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(40.0, (GLfloat) w/(GLfloat) h, 1.0, 100.0);
	glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv)
{
	if(argc > 1)				//take in command line scaling factor
		inputFR = stof(argv[1]);

	glutInit(&argc, argv);
	glutInitDisplayMode ( GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH );
	glutInitWindowSize (800, 800); 
	glutInitWindowPosition (100, 100);
	glutCreateWindow (argv[0]);
	init ();
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(SpecialInput);
	glutIdleFunc(runanim);
	glutMainLoop();
	return 0;
}
