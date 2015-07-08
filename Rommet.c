/**
  Rommet mitt på Berg Studentby.
  Ruben Undheim 2007

  Kompileres med:    gcc -o Rommet Rommet.c -lSDL -lGL -lGLU 

 **/

#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>


GLfloat xvinkel = 0;
GLfloat yvinkel = -58.400078;
GLfloat zvinkel = 0;
GLfloat pitch = 0;
GLfloat xtranslate = -2.861058;
GLfloat ytranslate = -1.000000;
GLfloat ztranslate = -2.451329;
GLfloat fwidth = 0.01;
GLfloat fdist = 0.017;
//xtranslate: -2.861058, ztranslate -2.451329, ytranslate -1.000000, yvinkel -58.400078
GLuint texture;

#define true 1
#define false 0
#define BREDDE 3.6
#define DYBDE 2.9

static float svart[] = {0,0,0,1};
static float vindufarge[] = {0.8,1.0,0.97};
static float trefarge[] = {0.55,0.35,0.11};
//static float lystre[] = {0.98,0.96,0.74};
//static float lystre[] = {0.85,0.47,0.13};
static float lystre[] = {0.86,0.62,0.12};
static float hvit[] = {1,1,1,1};
static float nestensvart[] = {0.25,0.25,0.25,1};
static float veggfarge[] = {0.9,0.9,0.9,1};
static float golvfarge[] = {0.73,0.65,0.26};
static float rod[] = {0.5,0,0};
static float gulfarge[] = {1,1,0,1};
static float skinning[] = {100};
static float morkblaa[] = {0.016,0.216,0.518};
unsigned int pulten, rommet;
GLfloat skuffz = 0;
GLuint lister;

void lagkube(float,float,float);

void draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
	static GLfloat red[4] = {0.8,0.1,0.0,1.0};
	static GLfloat green[4] = {0.0,0.8,0.2,1.0};
	GLfloat pos2[4] = {0,0,0,1};
	glRotatef(pitch,1,0,0);
	glRotatef(yvinkel,0,1,0);	
	glTranslatef(xtranslate,ytranslate,ztranslate);

	glPushMatrix();
	glCallList(rommet);
	glPushMatrix();			//skuff
	static GLfloat pos[4] = {0,0,0,1};
	static GLfloat grey[4] = {0.8,0.8,0.7,1};
//	glDisable(GL_LIGHT1);
	glPushMatrix();
		glTranslatef(1,2.05,1.5);
		glLightfv(GL_LIGHT1,GL_POSITION,pos);
		glMaterialfv(GL_FRONT,GL_EMISSION,hvit);
		glBegin(GL_QUADS);	
			glVertex3f(0,0,0);
			glVertex3f(0,0,0.3);
			glVertex3f(0.3,0,0.3);
			glVertex3f(0.3,0,0);
		glEnd();
		glMaterialfv(GL_FRONT,GL_EMISSION,svart);
		glLightfv(GL_LIGHT1,GL_DIFFUSE,grey);
		glLightfv(GL_LIGHT1,GL_SPECULAR,grey);
	glPopMatrix();
		glTranslatef(0.1,0,0.1);
		glTranslatef(0.02,0,0.78);
		glTranslatef(1.26,0,0);
		glTranslatef(-0.4,0.17,-0.03);
		glTranslatef(0.01,0.01,0);
		glTranslatef(-0.15,0.2,-0.15);
		glMaterialfv(GL_FRONT,GL_DIFFUSE,lystre);
		glMaterialfv(GL_FRONT,GL_AMBIENT,lystre);
		glTranslatef(0,0,skuffz);
				lagkube(0.37,0.14,0.65-0.09);
			
					glBegin(GL_QUADS);
						glNormal3f(0,0,1);
						glVertex3f(0,0,0);
						glVertex3f(0.37,0,0);
						glVertex3f(0.37,0.14,0);
						glVertex3f(0,0.14,0);
					glEnd();
					glMaterialfv(GL_FRONT,GL_DIFFUSE,svart);
					glMaterialfv(GL_FRONT,GL_AMBIENT,svart);
					glBegin(GL_QUADS);
						glVertex3f(0.14,0.07,0.02);
						glVertex3f(0.22,0.07,0.02);
						glVertex3f(0.22,0.09,0.02);
						glVertex3f(0.14,0.09,0.02);
					glEnd();
	glPopMatrix();
	glPopMatrix();


	glFlush();
	SDL_GL_SwapBuffers();

}



void lagvindu(float x,float y, int tvers)
{
	glMaterialfv(GL_FRONT,GL_DIFFUSE,vindufarge);
	glMaterialfv(GL_FRONT,GL_AMBIENT,vindufarge);

	if (tvers)
	{
		glBegin(GL_QUADS); //vindu
			glVertex3f(0.0,0.0,0);
			glVertex3f(0.0,0.0,-x);
			glVertex3f(0.0,y,-x);
			glVertex3f(0.0,y,0);
		glEnd();

		glMaterialfv(GL_FRONT,GL_DIFFUSE,trefarge);
		glMaterialfv(GL_FRONT,GL_AMBIENT,trefarge);
		glBegin(GL_QUADS);			//vinduskarm
			glVertex3f(0.0,-0.05,0.05);
			glVertex3f(0.0,-0.05,-x-0.05);
			glVertex3f(0.0,-0.01,-x-0.05);
			glVertex3f(0.0,-0.01,0.05);

			glVertex3f(0.0,y+0.01,0.05);
			glVertex3f(0.0,y+0.01,-x-0.05);
			glVertex3f(0.0,y+0.05,-x-0.05);
			glVertex3f(0.0,y+0.05,0.05);

			glVertex3f(0.0,-0.01,0+0.05);
			glVertex3f(0,-0.01,0.01);
			glVertex3f(0,y+0.01,0.01);
			glVertex3f(0,y+0.01,+0.05);

			glVertex3f(0.0,-0.01,-x-0.05);
			glVertex3f(0,-0.01,-x-0.01);
			glVertex3f(0,y+0.01,-x-0.01);
			glVertex3f(0,y+0.01,-x-0.05);
		glEnd();

	}
	else 
	{
		glBegin(GL_QUADS); //vindu
			glVertex3f(0.0,0.0,0);
			glVertex3f(x,0.0,0);
			glVertex3f(x,y,0);
			glVertex3f(0.0,y,0);
		glEnd();

	}
}

void lagpinne(float h, float tykkelse)
{
	glPushMatrix();
	glBegin(GL_QUADS);
		glNormal3f(0,0,1);
		glVertex3f(0,0,0);
		glVertex3f(tykkelse,0,0);
		glVertex3f(tykkelse,h,0);
		glVertex3f(0,h,0);

		glNormal3f(1,0,0);
		glVertex3f(tykkelse,0,0);
		glVertex3f(tykkelse,0,-tykkelse);
		glVertex3f(tykkelse,h,-tykkelse);
		glVertex3f(tykkelse,h,0);

		glNormal3f(0,0,-1);
		glVertex3f(tykkelse,0,-tykkelse);
		glVertex3f(0,0,-tykkelse);
		glVertex3f(0,h,-tykkelse);
		glVertex3f(tykkelse,h,-tykkelse);

		glNormal3f(-1,0,0);
		glVertex3f(0,0,-tykkelse);
		glVertex3f(0,0,0);
		glVertex3f(0,h,0);
		glVertex3f(0,h,-tykkelse);
	glEnd();
	glPopMatrix();
}

void lagkube(float x, float y, float z)
{
	glPushMatrix();
	glBegin(GL_QUADS);
		glNormal3f(1,0,0);
		glVertex3f(x,0,0);
		glVertex3f(x,0,-z);
		glVertex3f(x,y,-z);
		glVertex3f(x,y,0);

		glNormal3f(0,1,0);
		glVertex3f(x,y,0);
		glVertex3f(x,y,-z);
		glVertex3f(0,y,-z);
		glVertex3f(0,y,0);

		glNormal3f(-1,0,0);
		glVertex3f(0,y,0);
		glVertex3f(0,y,-z);
		glVertex3f(0,0,-z);
		glVertex3f(0,0,0);

		glNormal3f(0,-1,0);
		glVertex3f(0,0,0);
		glVertex3f(0,0,-z);
		glVertex3f(x,0,-z);
		glVertex3f(x,0,0);
	glEnd();
	glPopMatrix();
}


void lagkube2(float x, float y, float z)
{
	glPushMatrix();
	glBegin(GL_QUADS);
		glNormal3f(1,0,0);
		glVertex3f(x,0,0);
		glVertex3f(x,0,-z);
		glVertex3f(x,y,-z);
		glVertex3f(x,y,0);

		glNormal3f(0,1,0);
		glVertex3f(x,y,0);
		glVertex3f(x,y,-z);
		glVertex3f(0,y,-z);
		glVertex3f(0,y,0);

		glNormal3f(-1,0,0);
		glVertex3f(0,y,0);
		glVertex3f(0,y,-z);
		glVertex3f(0,0,-z);
		glVertex3f(0,0,0);

		glNormal3f(0,-1,0);
		glVertex3f(0,0,0);
		glVertex3f(0,0,-z);
		glVertex3f(x,0,-z);
		glVertex3f(x,0,0);

		glNormal3f(0,0,1);
		glVertex3f(0,0,0);
		glVertex3f(x,0,0);
		glVertex3f(x,y,0);
		glVertex3f(0,y,0);

		glNormal3f(0,0,-1);
		glVertex3f(0,0,-z);
		glVertex3f(x,0,-z);
		glVertex3f(x,y,-z);
		glVertex3f(0,y,-z);
	glEnd();
	glPopMatrix();
}

void lagkube3(float x, float y, float z)
{
	glPushMatrix();
	glBegin(GL_QUADS);
		glNormal3f(1,0,0);
		glVertex3f(x,0,0);
		glVertex3f(x,0,-z);
		glVertex3f(x,y,-z);
		glVertex3f(x,y,0);


		glNormal3f(-1,0,0);
		glVertex3f(0,y,0);
		glVertex3f(0,y,-z);
		glVertex3f(0,0,-z);
		glVertex3f(0,0,0);

		glNormal3f(0,-1,0);
		glVertex3f(0,0,0);
		glVertex3f(0,0,-z);
		glVertex3f(x,0,-z);
		glVertex3f(x,0,0);
	glEnd();
	glPopMatrix();
}


void laghylle()
{
	glMaterialfv(GL_FRONT,GL_DIFFUSE,lystre);
	glMaterialfv(GL_FRONT,GL_AMBIENT,lystre);
	glPushMatrix();
		lagkube2(0.03,0.8,0.4);   //nedre del
		glTranslatef(0.98,0,0);
		lagkube2(0.03,0.8,0.4);
		glTranslatef(-0.98,0,0);
		glPushMatrix();
			glTranslatef(0,0.1,-0.015);
			lagkube2(0.98,0.03,0.4-0.015);
			glTranslatef(0,0.26,0);
			lagkube2(0.98,0.03,0.4-0.015);
			glTranslatef(0,0.4,0);
			lagkube2(0.98,0.03,0.4-0.015);
		glPopMatrix();

		glTranslatef(0,0.8,-0.16);		//øvre del
		lagkube2(0.03,0.96,0.24);
		glTranslatef(0.98,0,0);
		lagkube2(0.03,0.96,0.24);
		glTranslatef(-0.98,0,0);
		glPushMatrix();
			glTranslatef(0,0.4,0);
			lagkube2(0.98,0.03,0.24);
			glTranslatef(0,0.26,0);
			lagkube2(0.98,0.03,0.24);
			glTranslatef(0,0.26,0);
			lagkube2(0.98,0.03,0.24);
		glPopMatrix();

	glPopMatrix();
}


void displaylister()
{
	lister = glGenLists(2);
	rommet = lister;
	pulten = lister+1;
	glNewList(pulten,GL_COMPILE);					//Pulten
	glMaterialfv(GL_FRONT,GL_DIFFUSE,lystre);
	glMaterialfv(GL_FRONT,GL_AMBIENT,lystre);
	glPushMatrix();
	glTranslatef(0,0.7,0);
	glBegin(GL_QUADS);
		glNormal3f(0,1,0);
		glVertex3f(0,0,0.66);
		glVertex3f(1.25,0,0.66);
		glVertex3f(1.25,0,0);
		glVertex3f(0,0,0);

		glNormal3f(0,-1,0);
		glVertex3f(0,-0.04,0.66);
		glVertex3f(1.25,-0.04,0.66);
		glVertex3f(1.25,-0.04,0);
		glVertex3f(0,-0.04,0);

		glNormal3f(0,0,1);
		glVertex3f(0,-0.04,0.66);
		glVertex3f(1.25,-0.04,0.66);
		glVertex3f(1.25,0,0.66);
		glVertex3f(0,0,0.66);

		glNormal3f(1,0,0);
		glVertex3f(1.25,-0.04,0.66);
		glVertex3f(1.25,-0.04,0.0);
		glVertex3f(1.25,0,0.0);
		glVertex3f(1.25,0,0.66);
	glEnd();

	glPopMatrix();
	glPushMatrix();
		glTranslatef(0.02,0,0.78-0.15);
		lagpinne(0.7,0.05);
		glPushMatrix();
			glTranslatef(0,+0.2,0);
			lagkube(0.05,0.05,0.7-0.15);
		glPopMatrix();
		glTranslatef(1.26-0.15,0,0);
		lagpinne(0.7,0.05);
		glPushMatrix();
			glTranslatef(0,+0.2,0);
			lagkube(0.05,0.05,0.7-0.15);
			glTranslatef(-0.4,0.17,-0.03);
			lagkube(0.39,0.31,0.65-0.09);
			glPushMatrix();		//skuffer i pulten
				glTranslatef(0.01,0.01,0);
				glMaterialfv(GL_FRONT,GL_DIFFUSE,lystre);
				glMaterialfv(GL_FRONT,GL_AMBIENT,lystre);
				glTranslatef(0,0.15,0);
				lagkube3(0.37,0.14,0.65-0.09);
				glBegin(GL_QUADS);
					glNormal3f(0,0,1);
					glVertex3f(0,0,0);
					glVertex3f(0.37,0,0);
					glVertex3f(0.37,0.14,0);
					glVertex3f(0,0.14,0);
				glEnd();
				glMaterialfv(GL_FRONT,GL_DIFFUSE,svart);
				glMaterialfv(GL_FRONT,GL_AMBIENT,svart);
				glBegin(GL_QUADS);
					glVertex3f(0.14,0.07,0.01);
					glVertex3f(0.22,0.07,0.01);
					glVertex3f(0.22,0.09,0.01);
					glVertex3f(0.14,0.09,0.01);
				glEnd();
				glMaterialfv(GL_FRONT,GL_DIFFUSE,lystre);
				glMaterialfv(GL_FRONT,GL_AMBIENT,lystre);
			glPopMatrix();
		glPopMatrix();
		glTranslatef(0,0,-0.68+0.15);
		lagpinne(0.7,0.05);
		glTranslatef(-1.26+0.15,0,0);
		lagpinne(0.7,0.05);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(2,1,2);

	glPopMatrix();
	glEndList();




	glNewList(rommet,GL_COMPILE);
	glPushMatrix();			//Rom start

	glMaterialfv(GL_FRONT,GL_DIFFUSE,nestensvart);
	glMaterialfv(GL_FRONT,GL_AMBIENT,svart);
	glBegin(GL_QUADS);    //vegger utvendig
		glNormal3f(0,0,-1);
		glVertex3f(0,0,0);
		glVertex3f(BREDDE,0,0);
		glVertex3f(BREDDE,2.44,0);
		glVertex3f(0,2.07,0);

		glNormal3f(0,0,1);
		glVertex3f(0,0,DYBDE);
		glVertex3f(BREDDE,0,DYBDE);
		glVertex3f(BREDDE,2.44,DYBDE);
		glVertex3f(0,2.07,DYBDE);

		glNormal3f(-1,0,0);
		glVertex3f(0,0,0);
		glVertex3f(0,0,DYBDE);
		glVertex3f(0,2.07,DYBDE);
		glVertex3f(0,2.07,0);

		glNormal3f(1,0,0);
		glVertex3f(BREDDE,0,0);
		glVertex3f(BREDDE,0,DYBDE);
		glVertex3f(BREDDE,2.44,DYBDE);
		glVertex3f(BREDDE,2.44,0);

		glNormal3f(0,1,0);   //tak utvendig
		glVertex3f(0,2.07,0);
		glVertex3f(BREDDE,2.44,0);
		glVertex3f(BREDDE,2.44,DYBDE);
		glVertex3f(0,2.07,DYBDE);

	glEnd();
	glMaterialfv(GL_FRONT,GL_DIFFUSE,veggfarge);
	glMaterialfv(GL_FRONT,GL_AMBIENT,veggfarge);
	//glPolygonStipple(stiplavegg);
	//glEnable(GL_POLYGON_STIPPLE);
	glBegin(GL_QUADS);    //vegger innvendig
		glNormal3f(0,0,1);
		glVertex3f(0.01,0,0.01);
		glVertex3f(BREDDE-0.01,0,0.01);
		glVertex3f(BREDDE-0.01,2.44-0.01,0.01);
		glVertex3f(0.01,2.07-0.01,0.01);

		glNormal3f(0,0,-1);
		glVertex3f(0.01,0,DYBDE-0.01);
		glVertex3f(BREDDE-0.01,0,DYBDE-0.01);
		glVertex3f(BREDDE-0.01,2.44,DYBDE-0.01);
		glVertex3f(0.01,2.07,DYBDE-0.01);

		glNormal3f(+1,0,0);
		glVertex3f(0.01,0,0.01);
		glVertex3f(0.01,0,DYBDE-0.01);
		glVertex3f(0.01,2.07,DYBDE-0.01);
		glVertex3f(0.01,2.07,0.01);

		glNormal3f(-1,0,0);
		glVertex3f(BREDDE-0.01,0,0.01);
		glVertex3f(BREDDE-0.01,0,DYBDE-0.01);
		glVertex3f(BREDDE-0.01,2.44,DYBDE-0.01);
		glVertex3f(BREDDE-0.01,2.44,0.01);


		glNormal3f(0,-1,0);   //tak innvendig
		glVertex3f(0.01,2.07-0.01,0.01);
		glVertex3f(BREDDE-0.01,2.44-0.01,0.01);
		glVertex3f(BREDDE-0.01,2.44-0.01,DYBDE-0.01);
		glVertex3f(0.01,2.07-0.01,DYBDE-0.01);


	glEnd();
	glDisable(GL_POLYGON_STIPPLE);
	glMaterialfv(GL_FRONT,GL_AMBIENT,golvfarge);
	glMaterialfv(GL_FRONT,GL_DIFFUSE,golvfarge);
	glBegin(GL_QUADS);
		glNormal3f(0,1,0);   //golvet
		glVertex3f(0,0,0);
		glVertex3f(BREDDE,0,0);
		glVertex3f(BREDDE,0,DYBDE);
		glVertex3f(0,0,DYBDE);
	glEnd();
	glPushMatrix();
	glTranslatef(0.02,0.75,DYBDE-0.1);  //vinduer
	glNormal3f(1,0,0);
	lagvindu(1.15,1.12,true);
	glTranslatef(-0.02,-0.75,-DYBDE+0.15);
	glTranslatef(0.02,0.75,DYBDE-0.23-1.15);
	glNormal3f(1,0,0);
	lagvindu(0.4,1.12,true);
	glTranslatef(-0.02,-0.75,-(DYBDE-0.2-1.3-0.1));
	glPopMatrix();
	glPushMatrix();
	//glMaterialfv(GL_FRONT,GL_DIFFUSE,lystre);
	//glMaterialfv(GL_FRONT,GL_AMBIENT,lystre);
	glTranslatef(0.02,0.75+1.12+0.05,DYBDE-0.01);
	lagkube2(0.02,0.05,DYBDE-0.02);
	glTranslatef(0,-1.14-0.12,0);
	lagkube2(0.02,0.05,DYBDE-0.02);
	glPopMatrix();

	glMaterialfv(GL_FRONT,GL_DIFFUSE,rod);
	glMaterialfv(GL_FRONT,GL_AMBIENT,rod);
	glBegin(GL_QUADS); //dør
		glNormal3f(-1,0,0); //innvendig
		glVertex3f(BREDDE-0.02,0.05,0.03);
		glVertex3f(BREDDE-0.02,0.05,0.03+0.72);
		glVertex3f(BREDDE-0.02,1.90,0.03+0.72);
		glVertex3f(BREDDE-0.02,1.90,0.03);

		glNormal3f(1,0,0); //utvendig
		glVertex3f(BREDDE+0.02,0.05,0.03);
		glVertex3f(BREDDE+0.02,0.05,0.03+0.72);
		glVertex3f(BREDDE+0.02,1.90,0.03+0.72);
		glVertex3f(BREDDE+0.02,1.90,0.03);
	glEnd();
	glMaterialfv(GL_FRONT,GL_AMBIENT,vindufarge);
	glMaterialfv(GL_FRONT,GL_DIFFUSE,vindufarge);
	glLineWidth(5);
	glBegin(GL_QUADS);
		glNormal3f(-1,0,0);
		glVertex3f(BREDDE-0.03,1,0.10);
		glVertex3f(BREDDE-0.03,1,0.21);
		glVertex3f(BREDDE-0.03,1.02,0.21);
		glVertex3f(BREDDE-0.03,1.02,0.10);

		glNormal3f(1,0,0);	
		glVertex3f(BREDDE+0.03,1,0.10);
		glVertex3f(BREDDE+0.03,1,0.21);
		glVertex3f(BREDDE+0.03,1.02,0.21);
		glVertex3f(BREDDE+0.03,1.02,0.10);
	glEnd();

	glMaterialfv(GL_FRONT,GL_DIFFUSE,veggfarge);
	glMaterialfv(GL_FRONT,GL_AMBIENT,veggfarge);
	glBegin(GL_QUADS); //hylle over dør/vask
		glNormal3f(0,-1,0);
		glVertex3f(BREDDE-0.58,1.95,0.02);
		glVertex3f(BREDDE-0.02,1.95,0.02);
		glVertex3f(BREDDE-0.02,1.95,DYBDE-0.02);
		glVertex3f(BREDDE-0.58,1.95,DYBDE-0.02);

		glNormal3f(0,-1,0);
		glVertex3f(BREDDE-0.58,2.04,0.02);
		glVertex3f(BREDDE-0.02,2.04,0.02);
		glVertex3f(BREDDE-0.02,2.04,DYBDE-0.02);
		glVertex3f(BREDDE-0.58,2.04,DYBDE-0.02);

		glNormal3f(-1,0,0);
		glVertex3f(BREDDE-0.58,1.95,0.02);
		glVertex3f(BREDDE-0.58,1.95,DYBDE-0.02);
		glVertex3f(BREDDE-0.58,2.04,DYBDE-0.02);
		glVertex3f(BREDDE-0.58,2.04,0.02);
	glEnd();
	glBegin(GL_QUADS);  //den lille veggen over hylla
		glNormal3f(-1,0,0);
		glVertex3f(BREDDE-0.30,2.04,0.02);
		glVertex3f(BREDDE-0.30,2.04,DYBDE-0.02);
		glVertex3f(BREDDE-0.30,2.40,DYBDE-0.02);
		glVertex3f(BREDDE-0.30,2.40,0.02);
	glEnd();
	glMaterialfv(GL_FRONT,GL_DIFFUSE,veggfarge);
	glMaterialfv(GL_FRONT,GL_AMBIENT,veggfarge);
	glBegin(GL_QUADS);	//venstre vaskskap
		glNormal3f(-1,0,0);
		glVertex3f(BREDDE-0.58,0.02,0.85);
		glVertex3f(BREDDE-0.58,0.02,0.85+0.63);
		glVertex3f(BREDDE-0.58,1.94,0.85+0.63);
		glVertex3f(BREDDE-0.58,1.94,0.85);

		glNormal3f(0,0,-1);
		glVertex3f(BREDDE-0.02,0.02,0.85);
		glVertex3f(BREDDE-0.58,0.02,0.85);
		glVertex3f(BREDDE-0.58,1.94,0.85);
		glVertex3f(BREDDE-0.02,1.94,0.85);

		glNormal3f(0,0,1);
		glVertex3f(BREDDE-0.02,0.02,0.85+0.63);
		glVertex3f(BREDDE-0.58,0.02,0.85+0.63);
		glVertex3f(BREDDE-0.58,1.94,0.85+0.63);
		glVertex3f(BREDDE-0.02,1.94,0.85+0.63);
	glEnd();
	glMaterialfv(GL_FRONT,GL_AMBIENT,gulfarge);
	glMaterialfv(GL_FRONT,GL_DIFFUSE,gulfarge);
	glBegin(GL_QUADS);
		glVertex3f(BREDDE-0.59,0.9,0.85+0.54);
		glVertex3f(BREDDE-0.59,0.8,0.85+0.54);
		glVertex3f(BREDDE-0.59,0.8,0.85+0.55);
		glVertex3f(BREDDE-0.59,0.9,0.85+0.55);
	glEnd();
	glMaterialfv(GL_FRONT,GL_DIFFUSE,veggfarge);
	glMaterialfv(GL_FRONT,GL_AMBIENT,veggfarge);
	//glTranslatef(0,0,1.67);
	glBegin(GL_QUADS);	//høyre vaskskap
		glNormal3f(-1,0,0);
		glVertex3f(BREDDE-0.58,0.02,DYBDE-0.68);
		glVertex3f(BREDDE-0.58,0.02,DYBDE-0.05);
		glVertex3f(BREDDE-0.58,1.94,DYBDE-0.05);
		glVertex3f(BREDDE-0.58,1.94,DYBDE-0.68);

		glNormal3f(0,0,-1);
		glVertex3f(BREDDE-0.02,0.02,DYBDE-0.68);
		glVertex3f(BREDDE-0.58,0.02,DYBDE-0.68);
		glVertex3f(BREDDE-0.58,1.94,DYBDE-0.68);
		glVertex3f(BREDDE-0.02,1.94,DYBDE-0.68);

		glNormal3f(0,0,1);
		glVertex3f(BREDDE-0.02,0.02,DYBDE-0.05);
		glVertex3f(BREDDE-0.58,0.02,DYBDE-0.05);
		glVertex3f(BREDDE-0.58,1.94,DYBDE-0.05);
		glVertex3f(BREDDE-0.02,1.94,DYBDE-0.05);
	glEnd();
	glMaterialfv(GL_FRONT,GL_AMBIENT,gulfarge);
	glMaterialfv(GL_FRONT,GL_DIFFUSE,gulfarge);
	glBegin(GL_QUADS);
		glVertex3f(BREDDE-0.59,0.9,DYBDE-0.60);
		glVertex3f(BREDDE-0.59,0.8,DYBDE-0.60);
		glVertex3f(BREDDE-0.59,0.8,DYBDE-0.61);
		glVertex3f(BREDDE-0.59,0.9,DYBDE-0.61);
	glEnd();

	glMaterialfv(GL_FRONT,GL_DIFFUSE,vindufarge);
	glMaterialfv(GL_FRONT,GL_AMBIENT,vindufarge);
	glMaterialfv(GL_FRONT,GL_SPECULAR,hvit);

	glMaterialfv(GL_FRONT,GL_SHININESS,skinning);
	glBegin(GL_QUADS); //speil vask
		glNormal3f(-1,0,0);
		glVertex3f(BREDDE-0.02,1.3,1.58);
		glVertex3f(BREDDE-0.02,1.3,1.58+0.58);
		glVertex3f(BREDDE-0.02,1.6,1.58+0.58);
		glVertex3f(BREDDE-0.02,1.6,1.58);
	glEnd();
	glPushMatrix();
	glBegin(GL_QUADS);   //stort speil
		glNormal3f(0,0,-1);
		glVertex3f(BREDDE-0.9,0.75,DYBDE-0.02);
		glVertex3f(BREDDE-0.9-0.30,0.75,DYBDE-0.02);
		glVertex3f(BREDDE-0.9-0.30,1.05,DYBDE-0.02);
		glVertex3f(BREDDE-0.9,1.05,DYBDE-0.02);
	glEnd();	
	glTranslatef(-0.32,0,0);
	glBegin(GL_QUADS);   //stort speil
		glNormal3f(0,0,-1);
		glVertex3f(BREDDE-0.9,0.75,DYBDE-0.02);
		glVertex3f(BREDDE-0.9-0.3,0.75,DYBDE-0.02);
		glVertex3f(BREDDE-0.9-0.3,1.05,DYBDE-0.02);
		glVertex3f(BREDDE-0.9,1.05,DYBDE-0.02);
	glEnd();	
	glTranslatef(0,0.32,0);
	glBegin(GL_QUADS);   //stort speil
		glNormal3f(0,0,-1);
		glVertex3f(BREDDE-0.9,0.75,DYBDE-0.02);
		glVertex3f(BREDDE-0.9-0.3,0.75,DYBDE-0.02);
		glVertex3f(BREDDE-0.9-0.3,1.05,DYBDE-0.02);
		glVertex3f(BREDDE-0.9,1.05,DYBDE-0.02);
	glEnd();	
	glTranslatef(0,0.32,0);
	glBegin(GL_QUADS);   //stort speil
		glNormal3f(0,0,-1);
		glVertex3f(BREDDE-0.9,0.75,DYBDE-0.02);
		glVertex3f(BREDDE-0.9-0.3,0.75,DYBDE-0.02);
		glVertex3f(BREDDE-0.9-0.3,1.05,DYBDE-0.02);
		glVertex3f(BREDDE-0.9,1.05,DYBDE-0.02);
	glEnd();	
	glTranslatef(0.32,0,0);
	glBegin(GL_QUADS);   //stort speil
		glNormal3f(0,0,-1);
		glVertex3f(BREDDE-0.9,0.75,DYBDE-0.02);
		glVertex3f(BREDDE-0.9-0.3,0.75,DYBDE-0.02);
		glVertex3f(BREDDE-0.9-0.3,1.05,DYBDE-0.02);
		glVertex3f(BREDDE-0.9,1.05,DYBDE-0.02);
	glEnd();	
	glTranslatef(0,-0.32,0);
	glBegin(GL_QUADS);   //stort speil
		glNormal3f(0,0,-1);
		glVertex3f(BREDDE-0.9,0.75,DYBDE-0.02);
		glVertex3f(BREDDE-0.9-0.3,0.75,DYBDE-0.02);
		glVertex3f(BREDDE-0.9-0.3,1.05,DYBDE-0.02);
		glVertex3f(BREDDE-0.9,1.05,DYBDE-0.02);
	glEnd();
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,texture);	
	glMaterialfv(GL_FRONT,GL_AMBIENT_AND_DIFFUSE,hvit);
	glNormal3f(0,0,1);
	glPushMatrix();
	glTranslatef(0.2,0.45,0.05);
	glBegin(GL_QUADS);
		glTexCoord2i(0,1);
		glVertex3f(0,0,0);
		glTexCoord2i(1,1);
		glVertex3f(1,0,0);
		glTexCoord2i(1,0);
		glVertex3f(1,1,0);
		glTexCoord2i(0,0);
		glVertex3f(0,1,0);
	glEnd();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);

	glPopMatrix();
	glMaterialfv(GL_FRONT,GL_SPECULAR,svart);
	glMaterialfv(GL_FRONT,GL_SHININESS,svart);
	glPushMatrix();
	glTranslatef(0.1,0,0.1);
	glCallList(pulten);  //skrivepult

	/*glPushMatrix();
	  glTranslatef(0,0,1);
	  glCallList(pulten);
	  glPopMatrix();*/

	glTranslatef(1.3,0,0.37);  //hylle
	laghylle();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0.1,0,DYBDE-0.05);


	glPushMatrix();                  //Lager seng
	glPushMatrix();
	glTranslatef(0.2,0,-0.1);
	lagpinne(0.4,0.05);
	glTranslatef(0,0,-0.55);
	lagpinne(0.4,0.05);
	glTranslatef(1.65-0.15,0,0);
	lagpinne(0.4,0.05);
	glTranslatef(0,0,0.55);
	lagpinne(0.4,0.05);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0,0.4,0);
	glMaterialfv(GL_FRONT,GL_AMBIENT,morkblaa);
	glMaterialfv(GL_FRONT,GL_DIFFUSE,morkblaa);
	lagkube2(1.85,0.1,0.75);
	glPushMatrix();
	glMaterialfv(GL_FRONT,GL_AMBIENT,lystre);
	glMaterialfv(GL_FRONT,GL_DIFFUSE,lystre);
	glBegin(GL_QUADS);
		glNormal3f(0,0,-1);
		glVertex3f(1.86,-0.08,-0.76);
		glVertex3f(0,-0.08,-0.76);
		glVertex3f(0,0.04,-0.76);
		glVertex3f(1.86,0.04,-0.76);

		glNormal3f(1,0,0);
		glVertex3f(1.86,-0.08,0);
		glVertex3f(1.86,-0.08,-0.76);
		glVertex3f(1.86,0.04,-0.76);
		glVertex3f(1.86,0.04,0);
	glEnd();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();			//Slutt på å lage seng

	glPopMatrix();
	glPopMatrix();		//Rom slutt
	glEndList();
}

void newfrustum(GLfloat h)
{
				glMatrixMode(GL_PROJECTION);
				glLoadIdentity();
				//gluPerspective(60.0f,1/h,0.1f,100.0f);
				glFrustum(-fwidth*h,fwidth*h,-fwidth,fwidth,fdist,10.0);
				glMatrixMode(GL_MODELVIEW);
}

void textures()
{
 /*SDL_Surface * bmpFile = SDL_LoadBMP("moose.bmp");

 glPixelStorei(GL_UNPACK_ALIGNMENT,4);
 glGenTextures(1,&texture);
 glBindTexture(GL_TEXTURE_2D,texture);
 glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
 glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

 gluBuild2DMipmaps(GL_TEXTURE_2D, 3,bmpFile->w, bmpFile->h, GL_BGR_EXT, GL_UNSIGNED_BYTE,bmpFile->pixels);

SDL_FreeSurface(bmpFile);
*/}	

int main()
{

	Uint8 *keys;
	SDL_Surface *screen;
	SDL_Init(SDL_INIT_VIDEO);

	screen = SDL_SetVideoMode(800,600,16,SDL_OPENGL|SDL_RESIZABLE);
 SDL_WM_SetCaption("Rommet mitt", "Berg studentby");

	if(!screen)
	{
		fprintf(stderr,"Feil\n");
		SDL_Quit();
		exit(2);
	}

	static GLfloat pos[4] = {0,0,1,0};
	glLightfv(GL_LIGHT0,GL_POSITION,pos);
	static float ambientlys[] = {0.4,0.4,0.4,1};
	static float diffuselys[] = {0.6,0.6,0.6,1};
	glLightfv(GL_LIGHT0,GL_AMBIENT,ambientlys);
	glLightfv(GL_LIGHT0,GL_DIFFUSE,diffuselys);
	//glEnable(GL_CULL_FACE);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT1);
	//glClearDepth(1.0f);	
	//glEnable(GL_LIGHT1);
	glDepthFunc(GL_LEQUAL);	
	//glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);

	glClearColor(0,0,0,0.5);
	glEnable(GL_NORMALIZE);


	GLfloat h = (GLfloat)screen->w/ (GLfloat)screen->h;
	glViewport(0,0,(GLint)screen->w, (GLint) screen->h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//gluPerspective(60.0f,1/h,0.1f,100.0f);
	glFrustum(-fwidth*h,fwidth*h,-fwidth,fwidth,fdist,10.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.0,0.0,0.0);
	textures();
	displaylister();



	int done = 0;
	SDL_WarpMouse(screen->w/2, screen->h/2);
	while(!done)
	{

		SDL_Event event;
		while(SDL_PollEvent(&event))
		{
			switch(event.type)
			{
				
				case SDL_MOUSEMOTION:
				if(320 - event.motion.x != 0)
				{
					yvinkel += (event.motion.x - screen->w/2) /5.0;
					if(yvinkel > 360) yvinkel -=360;
					if(yvinkel < 0) yvinkel +=360;
					SDL_WarpMouse(screen->w/2,screen->h/2);

				}
				if(240 - event.motion.y != 0) {
					pitch += (event.motion.y - screen->h/2) / 5.0;
					if(pitch < -90) pitch = -90;
					if(pitch > 90) pitch = 90;
					SDL_WarpMouse(screen->w / 2, screen->h / 2);
				}


				break;
				case SDL_VIDEORESIZE:
					screen = SDL_SetVideoMode(event.resize.w, event.resize.h, 16, SDL_OPENGL|SDL_RESIZABLE);
					if (screen) {
						h = (GLfloat)screen->w/ (GLfloat)screen->h;
						glViewport(0,0,(GLint)screen->w, (GLint) screen->h);
						glMatrixMode(GL_PROJECTION);
						glLoadIdentity();
						glFrustum(-fwidth*h,fwidth*h,-fwidth,fwidth,fdist,10.0);
						//glFrustum(-5.0,5.0,-5*h,5*h,0.15,2.0);
						glMatrixMode(GL_MODELVIEW);
						glLoadIdentity();
						glTranslatef(0.0,0.0,-40.0);

					}
					break;
				case SDL_QUIT:
					done = 1;
					break;
			}
		}
		keys = SDL_GetKeyState(NULL);
		if(keys[SDLK_ESCAPE])
		{
			done = 1 ;
		}
		/*		if(keys[SDLK_UP])
				ztranslate += 0.2;	
				if(keys[SDLK_DOWN])
				ztranslate -= 0.2;	*/
		if(keys[SDLK_LEFT])
			yvinkel -= 0.8;	
		if(keys[SDLK_RIGHT])
			yvinkel += 0.8;	
		if(keys[SDLK_w]) {
			ztranslate += 0.02*cos(yvinkel*M_PI/180);
			xtranslate -= 0.02*sin(yvinkel*M_PI/180);	
		}
		if(keys[SDLK_s]){
			ztranslate -= 0.02*cos(yvinkel*M_PI/180);
			xtranslate += 0.02*sin(yvinkel*M_PI/180);
		}
		if(keys[SDLK_a]){
			xtranslate += 0.02*cos(yvinkel*M_PI/180);
			ztranslate += 0.02*sin(yvinkel*M_PI/180);	
		}
		if(keys[SDLK_d]){
			xtranslate -= 0.02*cos(yvinkel*M_PI/180);
			ztranslate -= 0.02*sin(yvinkel*M_PI/180);
		}
		if(keys[SDLK_r])
			ytranslate -= 0.02;	
		if(keys[SDLK_f])
			ytranslate += 0.02;
		if(keys[SDLK_j])
			skuffz += 0.01;
		if(keys[SDLK_k])
			skuffz -= 0.01;
		if(keys[SDLK_t])
			{
				h = (GLfloat)screen->w/ (GLfloat)screen->h;
				fwidth+=0.0001;
				newfrustum(h);
				printf("fwidth: %f\n",fwidth);
			}
		if(keys[SDLK_g])
			{
				h = (GLfloat)screen->w/ (GLfloat)screen->h;
				fwidth-=0.0001;
				newfrustum(h);
				printf("fwidth: %f\n",fwidth);
			}
		if(keys[SDLK_y])
			{
				h = (GLfloat)screen->w/ (GLfloat)screen->h;
				fdist+=0.0001;
				newfrustum(h);
				printf("fdist: %f\n",fdist);
			}
		if(keys[SDLK_h])
			{
				h = (GLfloat)screen->w/ (GLfloat)screen->h;
				fdist-=0.0001;
				newfrustum(h);
				printf("fdist: %f\n",fdist);
			}		
		if(keys[SDLK_F1])
			SDL_WM_ToggleFullScreen( screen );

		//		if (xvinkel > 360) xvinkel -= 360;
		//		else if (xvinkel < -360) xvinkel += 360;
		if (yvinkel > 360) yvinkel -= 360;
		else if (yvinkel < -360) yvinkel += 360;
		if (fdist < 0.001) fdist = 0.001;
		if (skuffz < 0) skuffz = 0;
		else if (skuffz > 0.5) skuffz = 0.5;
		//printf("xtranslate: %f, ztranslate %f, ytranslate %f, yvinkel %f\n",xtranslate,ztranslate,ytranslate,yvinkel);
		draw();
		usleep(4000);
	}
	SDL_Quit();
	return 0;

}
