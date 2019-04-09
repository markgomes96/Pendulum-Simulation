// Mark Gomes
// Pendulum Project
// CSC 415
// 2/7/19

#include "includes.h"
#include "globals.h"
#include "globals.cc"
#include "prototypes.h"
#include "struct.h"

void init(void)
{
	glClearColor (0.0, 0.0, 0.0, 0.0);
	glLoadIdentity();

#ifdef LIGHTING
	GLfloat ambient[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat lmodel_ambient[] = { 0.4, 0.4, 0.4, 1.0 };
	GLfloat local_view[] = { 0.0 };

	glShadeModel (GL_SMOOTH);

	// ambient lighting
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
	glLightModelfv(GL_LIGHT_MODEL_LOCAL_VIEWER, local_view);
	// directional lighting
	glLightfv(GL_LIGHT0, GL_AMBIENT,   ambient);
	glLightfv (GL_LIGHT0, GL_SPECULAR, specular);
	glLightfv (GL_LIGHT0, GL_DIFFUSE,  diffuse);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
#endif

#ifdef TEXTURE
	textureLoader(0, "./textures/wall.jpg");
	textureLoader(1, "./textures/carpet.jpg");
	textureLoader(2, "./textures/ceiling.jpg");
	textureLoader(3, "./textures/table.jpg");
	textureLoader(4, "./textures/bluebase.jpg");
	textureLoader(5, "./textures/metalpendulum.jpg");
#endif

	//*** create all my objects
	// faces -> {bottom, left, right, back, front, top}
	// room object
#ifdef TEXTURE
	colortype roomColor = colortype(1.0, 1.0, 1.0);
#else
	colortype roomColor = colortype(0.93, 0.55, 0.39);	// peach
#endif
	GLuint roomft[] = {textarray[1].textid, textarray[0].textid, textarray[0].textid,
		textarray[0].textid, textarray[0].textid, textarray[2].textid};

	vect3 scale = vect3(14.0, 20.0, 6.0);
	defineBox(&room[0], scale, roomColor, &roomft[0]);
	// set camera bounds to room size
	cambounds[0] = -1 * scale.x;		cambounds[1] = scale.x;
	cambounds[2] = -1 * scale.y;		cambounds[3] = scale.y;
	cambounds[4] = -1 * scale.z;		cambounds[5] = scale.z;

	// table object
#ifdef TEXTURE
	colortype tableColor = colortype(1.0, 1.0, 1.0);
#else
	colortype tableColor = colortype(0.45, 0.30, 0.22);		// brown
#endif
	GLuint tableft[] = {textarray[3].textid, textarray[3].textid, textarray[3].textid,
		textarray[3].textid, textarray[3].textid, textarray[3].textid};
	defineBox(&tableLeg1[0], vect3(0.5, 0.5, 1.5), tableColor, &tableft[0]);
	defineBox(&tableLeg2[0], vect3(0.5, 0.5, 1.5), tableColor, &tableft[0]);
	defineBox(&tableLeg3[0], vect3(0.5, 0.5, 1.5), tableColor, &tableft[0]);
	defineBox(&tableLeg4[0], vect3(0.5, 0.5, 1.5), tableColor, &tableft[0]);
	defineBox(&tableFace[0], vect3(6.0, 6.0, 0.2), tableColor, &tableft[0]);

	// pendulum base object
#ifdef TEXTURE
	colortype penbaseColor = colortype(1.0, 1.0, 1.0);
#else
	colortype penbaseColor = colortype(1.0, 0.0, 0.0);		// red
#endif
	GLuint baseft[] = {textarray[4].textid, textarray[4].textid, textarray[4].textid,
		textarray[4].textid, textarray[4].textid, textarray[4].textid};
	defineBox(&penbase[0], vect3(5.0, 5.0, 0.1), penbaseColor, &baseft[0]);
	//***
}

void textureLoader(int ti, string path) 	// textarray index, file path
{
    glEnable(GL_TEXTURE_2D);

	glGenTextures(1, &textarray[ti].textid);		// create texture ID
	glBindTexture(GL_TEXTURE_2D, textarray[ti].textid);	// bind texutre to structure type

	// load image data into char array using SOIL library
	textarray[ti].image = SOIL_load_image(path.c_str(),
			&textarray[ti].width, &textarray[ti].height, 0, SOIL_LOAD_RGB);
	// set up filters and functions for MIPMAPS
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// glTexImage2D takes data and converts it to format used by OpenGL
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, textarray[ti].width, textarray[ti].height,
			0, GL_RGB, GL_UNSIGNED_BYTE, textarray[ti].image);
	// builds MIPMAP representations of texutres and stores in object
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(textarray[ti].image);

	/*
	cout << "Width: " << textarray[ti].width << ", Height: "
			  << textarray[ti].height << endl;
    cout << "Image ID: " << textarray[ti].textid << endl;
	*/
}

void reshape (int w, int h)
{
	glViewport (0, 0, (GLsizei) w, (GLsizei) h);
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(40.0, (GLfloat) w/(GLfloat) h, 0.25, 100.0);
	glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv)
{
	if(argc > 1)				//take in command line scaling factor
		inputFR = stof(argv[1]);

	cout << "\nPress [L] to move light around\n" << endl;

	glutInit(&argc, argv);
	glutInitDisplayMode ( GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH );
	glutInitWindowSize (800, 800);
	glutInitWindowPosition (100, 100);
	glutCreateWindow ("Pendulum Project");

	glewInit();
	init ();

	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutIdleFunc(runanim);

	glutKeyboardFunc(keyboard);		// input
	glutSpecialFunc(SpecialInput);

	glutMainLoop();
	return 0;
}
