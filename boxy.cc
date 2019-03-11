#ifndef BOXY
#define BOXY

#include "includes.h"
#include "globals.h"
#include "struct.h"

void drawBox( struct box *face, vect3 position, outline ol)
{
	glPolygonMode(GL_FRONT, GL_FILL);
	glPolygonMode(GL_BACK, GL_FILL);

	glPushMatrix();
	glTranslatef( position.x, position.y, position.z);		//move box to right position

	for(int j = 0; j < 6; j++)	//draw box
	{
#ifdef TEXTURE
		// set to face texture
		glBindTexture(GL_TEXTURE_2D, face[j].facetext);
#endif
		// set to face color
		glColor3f(face[j].color.red,
		  face[j].color.green,
		  face[j].color.blue);

		glBegin( GL_POLYGON );				//draw solid faces
			for (int i = 0; i < 4; i++)
			{
				glTexCoord2d(textarray[0].textcoords[i*2],
							 textarray[0].textcoords[(i*2)+1]);
				glVertex3f(face[j].point[i].x,
					face[j].point[i].y,
					face[j].point[i].z);
			}
		glEnd();

#ifdef TEXTURE
#else
		glLineWidth(5.0);
		if(ol == outside)
		{
			glColor3f(1.0, 1.0, 1.0);
			glBegin( GL_LINE_LOOP );			//draw outside face outline
				for (int i = 0; i < 4; i++)
				{
					glVertex3f(face[j].point[i].x,
						face[j].point[i].y,
						face[j].point[i].z);
				}
			glEnd();
		}
		else if(ol == inside)
		{
			glColor3f(1.0, 1.0, 1.0);
			glBegin( GL_LINE_LOOP );			//draw inside face outline
				for (int i = 0; i < 4; i++)
				{
					glVertex3f( (face[j].point[i].x * 0.95),
						(face[j].point[i].y * 0.95),
						(face[j].point[i].z * 0.95));
				}
			glEnd();
		}
		glLineWidth(1.0);
#endif
	}
	glPopMatrix();
}

// faces -> {bottom, left, right, back, front, top}
void defineBox(box *face, vect3 scale, colortype col, GLuint *ft)
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
	face[0].color.red   = col.red;
	face[0].color.green = col.green;
	face[0].color.blue  = col.blue;

	face[1].color.red   = col.red;
	face[1].color.green = col.green;
	face[1].color.blue  = col.blue;

	face[2].color.red   = col.red;
	face[2].color.green = col.green;
	face[2].color.blue  = col.blue;

	face[3].color.red   = col.red;
	face[3].color.green = col.green;
	face[3].color.blue  = col.blue;

	face[4].color.red   = col.red;
	face[4].color.green = col.green;
	face[4].color.blue  = col.blue;

	face[5].color.red   = col.red;
	face[5].color.green = col.green;
	face[5].color.blue  = col.blue;

	// Define face textures
	face[0].facetext = ft[0];
	face[1].facetext = ft[1];
	face[2].facetext = ft[2];
	face[3].facetext = ft[3];
	face[4].facetext = ft[4];
	face[5].facetext = ft[5];
}

#endif
