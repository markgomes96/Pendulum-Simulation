#ifndef BOXY
#define BOXY

#include "includes.h"
#include "struct.h"

void drawBox( struct box *face, vertex position)
{
	int i, j;

	glPolygonMode(GL_FRONT, GL_FILL);
	glPolygonMode(GL_BACK, GL_FILL);

	glPushMatrix();
	glTranslatef( position.x, position.y, position.z);		//move box to right position

	for(j = 0; j < 6; j++)	//draw box
	{

		glColor3f(face[j].color.red,
		  face[j].color.green,
		  face[j].color.blue);

		glBegin( GL_POLYGON );				//draw solid faces
			for (i = 0; i < 4; i++)
			{
				glVertex3f(face[j].point[i].x,
					face[j].point[i].y,
					face[j].point[i].z);
			}
		glEnd();

		glColor3f(1.0, 1.0, 1.0);
		glLineWidth(5.0);
		glBegin( GL_LINE_LOOP );			//draw outside face outline
			for (i = 0; i < 4; i++)
			{
				glVertex3f(face[j].point[i].x,
					face[j].point[i].y,
					face[j].point[i].z);
			}
		glEnd();

		glBegin( GL_LINE_LOOP );			//draw inside face outline
			for (i = 0; i < 4; i++)
			{
				glVertex3f( (face[j].point[i].x * 0.95),
					(face[j].point[i].y * 0.95),
					(face[j].point[i].z * 0.95));
			}
		glEnd();
		glLineWidth(5.0);
	}

	glPopMatrix();
}

void defineBox(box *face, vect3 scale)
{
	face[0].point[0].x = -1.0 * scale.x;  // Bottom
	face[0].point[0].y = -1.0 * scale.y;
	face[0].point[0].z = -1.0 * scale.z;
	face[0].point[0].w =  1.0;

	face[0].point[1].x = -1.0 * scale.x;
	face[0].point[1].y =  1.0 * scale.y;
	face[0].point[1].z = -1.0 * scale.z;
	face[0].point[1].w =  1.0;

	face[0].point[2].x =  1.0 * scale.x;
	face[0].point[2].y =  1.0 * scale.y;
	face[0].point[2].z = -1.0 * scale.z;
	face[0].point[2].w =  1.0;

	face[0].point[3].x =  1.0 * scale.x;
	face[0].point[3].y = -1.0 * scale.y;
	face[0].point[3].z = -1.0 * scale.z;
	face[0].point[3].w =  1.0;

	face[1].point[0].x = -1.0 * scale.x;  // Left Side
	face[1].point[0].y = -1.0 * scale.y;
	face[1].point[0].z = -1.0 * scale.z;
	face[1].point[0].w =  1.0;

	face[1].point[1].x = -1.0 * scale.x;
	face[1].point[1].y = -1.0 * scale.y;
	face[1].point[1].z =  1.0 * scale.z;
	face[1].point[1].w =  1.0;

	face[1].point[2].x =  1.0 * scale.x;
    face[1].point[2].y = -1.0 * scale.y;
	face[1].point[2].z =  1.0 * scale.z;
	face[1].point[2].w =  1.0;

	face[1].point[3].x =  1.0 * scale.x;
	face[1].point[3].y = -1.0 * scale.y;
	face[1].point[3].z = -1.0 * scale.z;
	face[1].point[3].w =  1.0;

	face[2].point[0].x = -1.0 * scale.x;  // Right Side 
	face[2].point[0].y =  1.0 * scale.y;
	face[2].point[0].z = -1.0 * scale.z;
	face[2].point[0].w =  1.0;

	face[2].point[1].x = -1.0 * scale.x;
	face[2].point[1].y =  1.0 * scale.y;
	face[2].point[1].z =  1.0 * scale.z;
	face[2].point[1].w =  1.0;

	face[2].point[2].x =  1.0 * scale.x;
	face[2].point[2].y =  1.0 * scale.y;
	face[2].point[2].z =  1.0 * scale.z;
	face[2].point[2].w =  1.0;

	face[2].point[3].x =  1.0 * scale.x;
	face[2].point[3].y =  1.0 * scale.y;
	face[2].point[3].z = -1.0 * scale.z;
	face[2].point[3].w =  1.0;
	
	face[3].point[0].x = -1.0 * scale.x;  // Back Side 
	face[3].point[0].y = -1.0 * scale.y;
	face[3].point[0].z = -1.0 * scale.z;
	face[3].point[0].w =  1.0;

	face[3].point[1].x = -1.0 * scale.x;
	face[3].point[1].y = -1.0 * scale.y;
	face[3].point[1].z =  1.0 * scale.z;
	face[3].point[1].w =  1.0;

	face[3].point[2].x = -1.0 * scale.x;
	face[3].point[2].y =  1.0 * scale.y;
	face[3].point[2].z =  1.0 * scale.z;
	face[3].point[2].w =  1.0;

	face[3].point[3].x = -1.0 * scale.x;
	face[3].point[3].y =  1.0 * scale.y;
	face[3].point[3].z = -1.0 * scale.z;
	face[3].point[3].w =  1.0;

	face[4].point[0].x =  1.0 * scale.x;  // Front Side 
	face[4].point[0].y = -1.0 * scale.y;
	face[4].point[0].z = -1.0 * scale.z;
	face[4].point[0].w =  1.0;

	face[4].point[1].x =  1.0 * scale.x;
	face[4].point[1].y = -1.0 * scale.y;
	face[4].point[1].z =  1.0 * scale.z;
	face[4].point[1].w =  1.0;

	face[4].point[2].x =  1.0 * scale.x;
	face[4].point[2].y =  1.0 * scale.y;
	face[4].point[2].z =  1.0 * scale.z;
	face[4].point[2].w =  1.0;

	face[4].point[3].x =  1.0 * scale.x;
	face[4].point[3].y =  1.0 * scale.y;
	face[4].point[3].z = -1.0 * scale.z;
	face[4].point[3].w =  1.0;

	face[5].point[0].x = -1.0 * scale.x;  // Top 
	face[5].point[0].y = -1.0 * scale.y;
	face[5].point[0].z =  1.0 * scale.z;
	face[5].point[0].w =  1.0;

	face[5].point[1].x = -1.0 * scale.x;
	face[5].point[1].y =  1.0 * scale.y;
	face[5].point[1].z =  1.0 * scale.z;
	face[5].point[1].w =  1.0;

	face[5].point[2].x =  1.0 * scale.x;
	face[5].point[2].y =  1.0 * scale.y;
	face[5].point[2].z =  1.0 * scale.z;
	face[5].point[2].w =  1.0;

	face[5].point[3].x =  1.0 * scale.x;
	face[5].point[3].y = -1.0 * scale.y;
	face[5].point[3].z =  1.0 * scale.z;
	face[5].point[3].w =  1.0;


	// Define the colors
	face[0].color.red   = 0.93;
	face[0].color.green = 0.55;
	face[0].color.blue  = 0.39;
	
	face[1].color.red   = 0.93;
	face[1].color.green = 0.55;
	face[1].color.blue  = 0.39;
	
	face[2].color.red   = 0.93;
	face[2].color.green = 0.55;
	face[2].color.blue  = 0.39;

	face[3].color.red   = 0.93;
	face[3].color.green = 0.55;
	face[3].color.blue  = 0.39;

	face[4].color.red   = 0.93;
	face[4].color.green = 0.55;
	face[4].color.blue  = 0.39;

	face[5].color.red   = 0.93;
	face[5].color.green = 0.55;
	face[5].color.blue  = 0.39;
	
}

#endif
