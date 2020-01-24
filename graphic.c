#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <string.h>
#include <math.h>
#include <stdio.h>

#include "structures.h"
#include "globales.h"
#include "headers.h"

extern Chlamydomonas *head_chlam;
extern Aggregate *head_aggregate;
extern int pass;

float red_chlam = 0.2;
float green_chlam = 1;
float blue_chlam = 1;
float red_aggr = 0.2;
float green_aggr = 1;
float blue_aggr = 0.2;

float temp = 0;

void *font = GLUT_BITMAP_TIMES_ROMAN_24;

void print_rgb(float x, float y, char *string, float r, float g, float b)
{
	int length, i;
	glColor3f(r,g,b);

	length = (int) strlen(string);
	for (int i = 0; i < length; i++)
		x -= 0.038 * glutBitmapWidth(font, string[i]);
	glRasterPos2f(x, y);
	for (i = 0; i < length; i++)
		glutBitmapCharacter(font, string[i]);
}
/*
static void output_rvb(float x, float y, char *string, float r, float v, float b, int lg)
{
   int len, i, max;

   glColor3f(r, v, b);

   len = (int) strlen(string);
   max = len < lg ? len : lg;
   glRasterPos2f(x - 0.305 - 0.3 * max, y);
   for (i = 0; i < max ; i++) {
     glutBitmapCharacter(font, string[i]);
   }

   glColor3f(1,1,1);
}
*/
void affich_colors()
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
 	glTranslatef(-15.5,-15.5,-53);

	// -15.6 // 46
	glColor3f(0.968627,0.968627,0.968627);
	glBegin(GL_POLYGON);
	glVertex2f(-15.6 + 1 * 61.6/8., 46 - 0 * 61.6/5);
	glVertex2f(-15.6 + 1 * 61.6/8., 46 - 1 * 61.6/5);
	glVertex2f(-15.6 + 0 * 61.6/8., 46 - 1 * 61.6/5);
	glVertex2f(-15.6 + 0 * 61.6/8., 46 - 0 * 61.6/5);
	glEnd();

	glColor3f(227./255,227./255,227./255);
	glBegin(GL_POLYGON);
	glVertex2f(-15.6 + 1 * 61.6/8., 46 - 0 * 61.6/5);
	glVertex2f(-15.6 + 1 * 61.6/8., 46 - 1 * 61.6/5);
	glVertex2f(-15.6 + 2 * 61.6/8., 46 - 1 * 61.6/5);
	glVertex2f(-15.6 + 2 * 61.6/8., 46 - 0 * 61.6/5);
	glEnd();

	glColor3f(208./255,208./255,208./255);
	glBegin(GL_POLYGON);
	glVertex2f(-15.6 + 2 * 61.6/8., 46 - 0 * 61.6/5);
	glVertex2f(-15.6 + 2 * 61.6/8., 46 - 1 * 61.6/5);
	glVertex2f(-15.6 + 3 * 61.6/8., 46 - 1 * 61.6/5);
	glVertex2f(-15.6 + 3 * 61.6/8., 46 - 0 * 61.6/5);
	glEnd();

	glColor3f(173./255,173./255,173./255);
	glBegin(GL_POLYGON);
	glVertex2f(-15.6 + 3 * 61.6/8., 46 - 0 * 61.6/5);
	glVertex2f(-15.6 + 3 * 61.6/8., 46 - 1 * 61.6/5);
	glVertex2f(-15.6 + 4 * 61.6/8., 46 - 1 * 61.6/5);
	glVertex2f(-15.6 + 4 * 61.6/8., 46 - 0 * 61.6/5);
	glEnd();

	glColor3f(153./255,153./255,153./255);
	glBegin(GL_POLYGON);
	glVertex2f(-15.6 + 5 * 61.6/8., 46 - 0 * 61.6/5);
	glVertex2f(-15.6 + 5 * 61.6/8., 46 - 1 * 61.6/5);
	glVertex2f(-15.6 + 4 * 61.6/8., 46 - 1 * 61.6/5);
	glVertex2f(-15.6 + 4 * 61.6/8., 46 - 0 * 61.6/5);
	glEnd();

	glColor3f(102./255,102./255,102./255);
	glBegin(GL_POLYGON);
	glVertex2f(-15.6 + 5 * 61.6/8., 46 - 0 * 61.6/5);
	glVertex2f(-15.6 + 5 * 61.6/8., 46 - 1 * 61.6/5);
	glVertex2f(-15.6 + 6 * 61.6/8., 46 - 1 * 61.6/5);
	glVertex2f(-15.6 + 6 * 61.6/8., 46 - 0 * 61.6/5);
	glEnd();

	glColor3f(051./255,051./255,051./255);
	glBegin(GL_POLYGON);
	glVertex2f(-15.6 + 6 * 61.6/8., 46 - 0 * 61.6/5);
	glVertex2f(-15.6 + 6 * 61.6/8., 46 - 1 * 61.6/5);
	glVertex2f(-15.6 + 7 * 61.6/8., 46 - 1 * 61.6/5);
	glVertex2f(-15.6 + 7 * 61.6/8., 46 - 0 * 61.6/5);
	glEnd();

	glColor3f(0,0,0);
	glBegin(GL_POLYGON);
	glVertex2f(-15.6 + 7 * 61.6/8., 46 - 0 * 61.6/5);
	glVertex2f(-15.6 + 7 * 61.6/8., 46 - 1 * 61.6/5);
	glVertex2f(-15.6 + 8 * 61.6/8., 46 - 1 * 61.6/5);
	glVertex2f(-15.6 + 8 * 61.6/8., 46 - 0 * 61.6/5);
	glEnd();

	glColor3f(1,216./255,52./255);
	glBegin(GL_POLYGON);
	glVertex2f(-15.6 + 0 * 61.6/8., 46 - 2 * 61.6/5);
	glVertex2f(-15.6 + 0 * 61.6/8., 46 - 1 * 61.6/5);
	glVertex2f(-15.6 + 1 * 61.6/8., 46 - 1 * 61.6/5);
	glVertex2f(-15.6 + 1 * 61.6/8., 46 - 2 * 61.6/5);
	glEnd();

	glColor3f(1,149./255,149./255);
	glBegin(GL_POLYGON);
	glVertex2f(-15.6 + 1 * 61.6/8., 46 - 2 * 61.6/5);
	glVertex2f(-15.6 + 1 * 61.6/8., 46 - 1 * 61.6/5);
	glVertex2f(-15.6 + 2 * 61.6/8., 46 - 1 * 61.6/5);
	glVertex2f(-15.6 + 2 * 61.6/8., 46 - 2 * 61.6/5);
	glEnd();

	glColor3f(142./255,222./255,153./255);
	glBegin(GL_POLYGON);
	glVertex2f(-15.6 + 2 * 61.6/8., 46 - 2 * 61.6/5);
	glVertex2f(-15.6 + 2 * 61.6/8., 46 - 1 * 61.6/5);
	glVertex2f(-15.6 + 3 * 61.6/8., 46 - 1 * 61.6/5);
	glVertex2f(-15.6 + 3 * 61.6/8., 46 - 2 * 61.6/5);
	glEnd();

	glColor3f(12./255,230./255,207./255);
	glBegin(GL_POLYGON);
	glVertex2f(-15.6 + 4 * 61.6/8., 46 - 2 * 61.6/5);
	glVertex2f(-15.6 + 4 * 61.6/8., 46 - 1 * 61.6/5);
	glVertex2f(-15.6 + 3 * 61.6/8., 46 - 1 * 61.6/5);
	glVertex2f(-15.6 + 3 * 61.6/8., 46 - 2 * 61.6/5);
	glEnd();

	glColor3f(161./255,217./255,237./255);
	glBegin(GL_POLYGON);
	glVertex2f(-15.6 + 4 * 61.6/8., 46 - 2 * 61.6/5);
	glVertex2f(-15.6 + 4 * 61.6/8., 46 - 1 * 61.6/5);
	glVertex2f(-15.6 + 5 * 61.6/8., 46 - 1 * 61.6/5);
	glVertex2f(-15.6 + 5 * 61.6/8., 46 - 2 * 61.6/5);
	glEnd();

	glColor3f(121./255,134./255,203./255);
	glBegin(GL_POLYGON);
	glVertex2f(-15.6 + 5 * 61.6/8., 46 - 2 * 61.6/5);
	glVertex2f(-15.6 + 5 * 61.6/8., 46 - 1 * 61.6/5);
	glVertex2f(-15.6 + 6 * 61.6/8., 46 - 1 * 61.6/5);
	glVertex2f(-15.6 + 6 * 61.6/8., 46 - 2 * 61.6/5);
	glEnd();

	glColor3f(186./255,105./255,200./255);
	glBegin(GL_POLYGON);
	glVertex2f(-15.6 + 6 * 61.6/8., 46 - 2 * 61.6/5);
	glVertex2f(-15.6 + 6 * 61.6/8., 46 - 1 * 61.6/5);
	glVertex2f(-15.6 + 7 * 61.6/8., 46 - 1 * 61.6/5);
	glVertex2f(-15.6 + 7 * 61.6/8., 46 - 2 * 61.6/5);
	glEnd();

	glColor3f(1,171./255,213./255);
	glBegin(GL_POLYGON);
	glVertex2f(-15.6 + 7 * 61.6/8., 46 - 2 * 61.6/5);
	glVertex2f(-15.6 + 7 * 61.6/8., 46 - 1 * 61.6/5);
	glVertex2f(-15.6 + 8 * 61.6/8., 46 - 1 * 61.6/5);
	glVertex2f(-15.6 + 8 * 61.6/8., 46 - 2 * 61.6/5);
	glEnd();


	glColor3f(1,192./255,009./255);
	glBegin(GL_POLYGON);
	glVertex2f(-15.6 + 0 * 61.6/8., 46 - 2 * 61.6/5);
	glVertex2f(-15.6 + 0 * 61.6/8., 46 - 3 * 61.6/5);
	glVertex2f(-15.6 + 1 * 61.6/8., 46 - 3 * 61.6/5);
	glVertex2f(-15.6 + 1 * 61.6/8., 46 - 2 * 61.6/5);
	glEnd();

	glColor3f(1,82./255,82./255);
	glBegin(GL_POLYGON);
	glVertex2f(-15.6 + 1 * 61.6/8., 46 - 2 * 61.6/5);
	glVertex2f(-15.6 + 1 * 61.6/8., 46 - 3 * 61.6/5);
	glVertex2f(-15.6 + 2 * 61.6/8., 46 - 3 * 61.6/5);
	glVertex2f(-15.6 + 2 * 61.6/8., 46 - 2 * 61.6/5);
	glEnd();

	glColor3f(44./255,213./255,81./255);
	glBegin(GL_POLYGON);
	glVertex2f(-15.6 + 2 * 61.6/8., 46 - 2 * 61.6/5);
	glVertex2f(-15.6 + 2 * 61.6/8., 46 - 3 * 61.6/5);
	glVertex2f(-15.6 + 3 * 61.6/8., 46 - 3 * 61.6/5);
	glVertex2f(-15.6 + 3 * 61.6/8., 46 - 2 * 61.6/5);
	glEnd();

	glColor3f(0,169./255,157./255);
	glBegin(GL_POLYGON);
	glVertex2f(-15.6 + 3 * 61.6/8., 46 - 2 * 61.6/5);
	glVertex2f(-15.6 + 3 * 61.6/8., 46 - 3 * 61.6/5);
	glVertex2f(-15.6 + 4 * 61.6/8., 46 - 3 * 61.6/5);
	glVertex2f(-15.6 + 4 * 61.6/8., 46 - 2 * 61.6/5);
	glEnd();

	glColor3f(5./255,168./255,244./255);
	glBegin(GL_POLYGON);
	glVertex2f(-15.6 + 4 * 61.6/8., 46 - 2 * 61.6/5);
	glVertex2f(-15.6 + 4 * 61.6/8., 46 - 3 * 61.6/5);
	glVertex2f(-15.6 + 5 * 61.6/8., 46 - 3 * 61.6/5);
	glVertex2f(-15.6 + 5 * 61.6/8., 46 - 2 * 61.6/5);
	glEnd();

	glColor3f(64./255,81./255,181./255);
	glBegin(GL_POLYGON);
	glVertex2f(-15.6 + 5 * 61.6/8., 46 - 2 * 61.6/5);
	glVertex2f(-15.6 + 5 * 61.6/8., 46 - 3 * 61.6/5);
	glVertex2f(-15.6 + 6 * 61.6/8., 46 - 3 * 61.6/5);
	glVertex2f(-15.6 + 6 * 61.6/8., 46 - 2 * 61.6/5);
	glEnd();

	glColor3f(156./255,039./255,176./255);
	glBegin(GL_POLYGON);
	glVertex2f(-15.6 + 6 * 61.6/8., 46 - 2 * 61.6/5);
	glVertex2f(-15.6 + 6 * 61.6/8., 46 - 3 * 61.6/5);
	glVertex2f(-15.6 + 7 * 61.6/8., 46 - 3 * 61.6/5);
	glVertex2f(-15.6 + 7 * 61.6/8., 46 - 2 * 61.6/5);
	glEnd();

	glColor3f(234./255,138./255,286./255);
	glBegin(GL_POLYGON);
	glVertex2f(-15.6 + 8 * 61.6/8., 46 - 2 * 61.6/5);
	glVertex2f(-15.6 + 8 * 61.6/8., 46 - 3 * 61.6/5);
	glVertex2f(-15.6 + 7 * 61.6/8., 46 - 3 * 61.6/5);
	glVertex2f(-15.6 + 7 * 61.6/8., 46 - 2 * 61.6/5);
	glEnd();


	glColor3f(1,159./255,0);
	glBegin(GL_POLYGON);
	glVertex2f(-15.6 + 0 * 61.6/8., 46 - 4 * 61.6/5);
	glVertex2f(-15.6 + 0 * 61.6/8., 46 - 3 * 61.6/5);
	glVertex2f(-15.6 + 1 * 61.6/8., 46 - 3 * 61.6/5);
	glVertex2f(-15.6 + 1 * 61.6/8., 46 - 4 * 61.6/5);
	glEnd();

	glColor3f(1,60./255,0);
	glBegin(GL_POLYGON);
	glVertex2f(-15.6 + 2 * 61.6/8., 46 - 4 * 61.6/5);
	glVertex2f(-15.6 + 2 * 61.6/8., 46 - 3 * 61.6/5);
	glVertex2f(-15.6 + 1 * 61.6/8., 46 - 3 * 61.6/5);
	glVertex2f(-15.6 + 1 * 61.6/8., 46 - 4 * 61.6/5);
	glEnd();

	glColor3f(25./255,167./255,25./255);
	glBegin(GL_POLYGON);
	glVertex2f(-15.6 + 2 * 61.6/8., 46 - 4 * 61.6/5);
	glVertex2f(-15.6 + 2 * 61.6/8., 46 - 3 * 61.6/5);
	glVertex2f(-15.6 + 3 * 61.6/8., 46 - 3 * 61.6/5);
	glVertex2f(-15.6 + 3 * 61.6/8., 46 - 4 * 61.6/5);
	glEnd();

	glColor3f(0,124./255,116./255);
	glBegin(GL_POLYGON);
	glVertex2f(-15.6 + 3 * 61.6/8., 46 - 4 * 61.6/5);
	glVertex2f(-15.6 + 3 * 61.6/8., 46 - 3 * 61.6/5);
	glVertex2f(-15.6 + 4 * 61.6/8., 46 - 3 * 61.6/5);
	glVertex2f(-15.6 + 4 * 61.6/8., 46 - 4 * 61.6/5);
	glEnd();

	glColor3f(2./255,136./255,209./255);
	glBegin(GL_POLYGON);
	glVertex2f(-15.6 + 4 * 61.6/8., 46 - 4 * 61.6/5);
	glVertex2f(-15.6 + 4 * 61.6/8., 46 - 3 * 61.6/5);
	glVertex2f(-15.6 + 5 * 61.6/8., 46 - 3 * 61.6/5);
	glVertex2f(-15.6 + 5 * 61.6/8., 46 - 4 * 61.6/5);
	glEnd();

	glColor3f(48./255,63./255,159./255);
	glBegin(GL_POLYGON);
	glVertex2f(-15.6 + 6 * 61.6/8., 46 - 4 * 61.6/5);
	glVertex2f(-15.6 + 6 * 61.6/8., 46 - 3 * 61.6/5);
	glVertex2f(-15.6 + 5 * 61.6/8., 46 - 3 * 61.6/5);
	glVertex2f(-15.6 + 5 * 61.6/8., 46 - 4 * 61.6/5);
	glEnd();

	glColor3f(123./255,031./255,162./255);
	glBegin(GL_POLYGON);
	glVertex2f(-15.6 + 6 * 61.6/8., 46 - 4 * 61.6/5);
	glVertex2f(-15.6 + 6 * 61.6/8., 46 - 3 * 61.6/5);
	glVertex2f(-15.6 + 7 * 61.6/8., 46 - 3 * 61.6/5);
	glVertex2f(-15.6 + 7 * 61.6/8., 46 - 4 * 61.6/5);
	glEnd();

	glColor3f(206./255,66./255,137./255);
	glBegin(GL_POLYGON);
	glVertex2f(-15.6 + 7 * 61.6/8., 46 - 4 * 61.6/5);
	glVertex2f(-15.6 + 7 * 61.6/8., 46 - 3 * 61.6/5);
	glVertex2f(-15.6 + 8 * 61.6/8., 46 - 3 * 61.6/5);
	glVertex2f(-15.6 + 8 * 61.6/8., 46 - 4 * 61.6/5);
	glEnd();

	glColor3f(1,111./255,0);
	glBegin(GL_POLYGON);
	glVertex2f(-15.6 + 0 * 61.6/8., 46 - 4 * 61.6/5);
	glVertex2f(-15.6 + 0 * 61.6/8., 46 - 5 * 61.6/5);
	glVertex2f(-15.6 + 1 * 61.6/8., 46 - 5 * 61.6/5);
	glVertex2f(-15.6 + 1 * 61.6/8., 46 - 4 * 61.6/5);
	glEnd();

	glColor3f(246./255,33./255,045./255);
	glBegin(GL_POLYGON);
	glVertex2f(-15.6 + 2 * 61.6/8., 46 - 4 * 61.6/5);
	glVertex2f(-15.6 + 2 * 61.6/8., 46 - 5 * 61.6/5);
	glVertex2f(-15.6 + 1 * 61.6/8., 46 - 5 * 61.6/5);
	glVertex2f(-15.6 + 1 * 61.6/8., 46 - 4 * 61.6/5);
	glEnd();

	glColor3f(21./255,131./255,28./255);
	glBegin(GL_POLYGON);
	glVertex2f(-15.6 + 2 * 61.6/8., 46 - 4 * 61.6/5);
	glVertex2f(-15.6 + 2 * 61.6/8., 46 - 5 * 61.6/5);
	glVertex2f(-15.6 + 3 * 61.6/8., 46 - 5 * 61.6/5);
	glVertex2f(-15.6 + 3 * 61.6/8., 46 - 4 * 61.6/5);
	glEnd();

	glColor3f(2./255,90./255,90./255);
	glBegin(GL_POLYGON);
	glVertex2f(-15.6 + 3 * 61.6/8., 46 - 4 * 61.6/5);
	glVertex2f(-15.6 + 3 * 61.6/8., 46 - 5 * 61.6/5);
	glVertex2f(-15.6 + 4 * 61.6/8., 46 - 5 * 61.6/5);
	glVertex2f(-15.6 + 4 * 61.6/8., 46 - 4 * 61.6/5);
	glEnd();

	glColor3f(0,87./255,155./255);
	glBegin(GL_POLYGON);
	glVertex2f(-15.6 + 4 * 61.6/8., 46 - 4 * 61.6/5);
	glVertex2f(-15.6 + 4 * 61.6/8., 46 - 5 * 61.6/5);
	glVertex2f(-15.6 + 5 * 61.6/8., 46 - 5 * 61.6/5);
	glVertex2f(-15.6 + 5 * 61.6/8., 46 - 4 * 61.6/5);
	glEnd();

	glColor3f(26./255,34./255,126./255);
	glBegin(GL_POLYGON);
	glVertex2f(-15.6 + 5 * 61.6/8., 46 - 4 * 61.6/5);
	glVertex2f(-15.6 + 5 * 61.6/8., 46 - 5 * 61.6/5);
	glVertex2f(-15.6 + 6 * 61.6/8., 46 - 5 * 61.6/5);
	glVertex2f(-15.6 + 6 * 61.6/8., 46 - 4 * 61.6/5);
	glEnd();

	glColor3f(74./255,20./255,140./255);
	glBegin(GL_POLYGON);
	glVertex2f(-15.6 + 6 * 61.6/8., 46 - 4 * 61.6/5);
	glVertex2f(-15.6 + 6 * 61.6/8., 46 - 5 * 61.6/5);
	glVertex2f(-15.6 + 7 * 61.6/8., 46 - 5 * 61.6/5);
	glVertex2f(-15.6 + 7 * 61.6/8., 46 - 4 * 61.6/5);
	glEnd();

	glColor3f(163./255,064./255,117./255);
	glBegin(GL_POLYGON);
	glVertex2f(-15.6 + 7 * 61.6/8., 46 - 4 * 61.6/5);
	glVertex2f(-15.6 + 7 * 61.6/8., 46 - 5 * 61.6/5);
	glVertex2f(-15.6 + 8 * 61.6/8., 46 - 5 * 61.6/5);
	glVertex2f(-15.6 + 8 * 61.6/8., 46 - 4 * 61.6/5);
	glEnd();
}

void reshape(GLsizei width, GLsizei height)
{
	if (width > height)
		glViewport((width - height)/2, 0, height, height);
	else glViewport(0, (height - width)/2, width, width);
	glutPostRedisplay();
}

void cube(int x, int y, int z)
{
    glBegin(GL_POLYGON);
    glVertex3f(x - size, y - size, z + size);
	glVertex3f(x + size, y - size, z + size);
	glVertex3f(x + size, y + size, z + size);
	glVertex3f(x - size, y + size, z + size);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(x + size, y - size, z + size);
	glVertex3f(x + size, y + size, z + size);
	glVertex3f(x + size, y + size, z - size);
	glVertex3f(x + size, y - size, z - size);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(x - size, y - size, z - size);
	glVertex3f(x + size, y - size, z - size);
	glVertex3f(x + size, y + size, z - size);
	glVertex3f(x - size, y + size, z - size);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(x - size, y - size, z + size);
	glVertex3f(x - size, y - size, z - size);
	glVertex3f(x - size, y + size, z - size);
	glVertex3f(x - size, y + size, z + size);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(x - size, y + size, z - size);
	glVertex3f(x + size, y + size, z - size);
	glVertex3f(x + size, y + size, z + size);
	glVertex3f(x - size, y + size, z + size);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(x - size, y - size, z - size);
	glVertex3f(x + size, y - size, z - size);
	glVertex3f(x + size, y - size, z + size);
	glVertex3f(x - size, y - size, z + size);
	glEnd();
}

void print_chlam(Chlamydomonas *head)
{
    if (head == NULL)
        return;
    if (!red_chlam && !green_chlam && !blue_chlam) return;
    glColor3f(red_chlam,green_chlam,blue_chlam);
    while (head != NULL) {
        cube(head->x,head->y,head->z);
        head = head->next;
    }
}

void print_aggregates(Aggregate *head)
{
    if (head == NULL)
        return;
    if (!red_aggr && !green_aggr && !blue_aggr) 
    	return;
    glColor3f(red_aggr,green_aggr,blue_aggr);
    while (head != NULL) {
		glPushMatrix();
        glTranslatef(head->center->x,head->center->y,head->center->z);
        glutSolidSphere((head->radius * 3 * size) + size ,30,30);
        head = head->next;
        glPopMatrix();
    }
}

void affich_menu(char option)
{
	glMatrixMode(GL_MODELVIEW);
  	glLoadIdentity();

  	glTranslatef(-15.5,-15.5,-53);


	print_rgb(15.2, 40.865, "End program", 0.8, 0.8, 0.8);
    print_rgb(15.2, 30.6, "New experiment", 0.8, 0.8, 0.8);
    print_rgb(15.2, 20.335, "Change options", 0.8, 0.8, 0.8);
    print_rgb(15.2, 10.13, "See tutorial", 0.8, 0.8, 0.8);
    print_rgb(15.2, -0.135, "Resume", 0.8, 0.8, 0.8);

    switch (option) {
    	case 1:	glColor3f(0.9,0.1,0.1);
		   	glBegin(GL_POLYGON);
			glVertex2f(-13, 46);
			glVertex2f(-13, 35.73);
			glVertex2f(43.4, 35.73);
			glVertex2f(43.4, 46);
			glEnd();
			break;
		case 2:	glColor3f(0.9, 0.1, 0.1);
			glBegin(GL_POLYGON);
			glVertex2f(-13, 35.73);
			glVertex2f(-13, 25.47);
			glVertex2f(43.4, 25.47);
			glVertex2f(43.4, 35.73);
			glEnd();
			break;
		case 3:	glColor3f(0.9,0.1,0.1);
			glBegin(GL_POLYGON);
			glVertex2f(-13, 25.47);
			glVertex2f(-13, 15.21);
			glVertex2f(43.4, 15.21);
			glVertex2f(43.4, 25.47);
			glEnd();
			break;
		case 4:	glColor3f(0.9, 0.1, 0.1);
			glBegin(GL_POLYGON);
			glVertex2f(-13, 15.21);
			glVertex2f(-13, 4.95);
			glVertex2f(43.4, 4.95);
			glVertex2f(43.4, 15.21);
			glEnd();
			break;
		case 5:
			glColor3f(0.9, 0.1, 0.1);
			glBegin(GL_POLYGON);
			glVertex2f(-13, 4.95);
			glVertex2f(-13, -5.31);
			glVertex2f(43.4, -5.31);
			glVertex2f(43.4, 4.95);
			glEnd();
			break;
    }


	// -15.6 // 46
	glColor3f(0.1,0.1,0.1);
   	glBegin(GL_POLYGON);
	glVertex2f(-13, 46);
	glVertex2f(-13, 35.73);
	glVertex2f(43.4, 35.73);
	glVertex2f(43.4, 46);
	glEnd();

	glColor3f(0.12, 0.12, 0.12);
	glBegin(GL_POLYGON);
	glVertex2f(-13, 35.73);
	glVertex2f(-13, 25.47);
	glVertex2f(43.4, 25.47);
	glVertex2f(43.4, 35.73);
	glEnd();

	glColor3f(0.14,0.14,0.14);
	glBegin(GL_POLYGON);
	glVertex2f(-13, 25.47);
	glVertex2f(-13, 15.21);
	glVertex2f(43.4, 15.21);
	glVertex2f(43.4, 25.47);
	glEnd();

	glColor3f(0.16, 0.16, 0.16);
	glBegin(GL_POLYGON);
	glVertex2f(-13, 15.21);
	glVertex2f(-13, 4.95);
	glVertex2f(43.4, 4.95);
	glVertex2f(43.4, 15.21);
	glEnd();

	glColor3f(0.18, 0.18, 0.18);
	glBegin(GL_POLYGON);
	glVertex2f(-13, 4.95);
	glVertex2f(-13, -5.31);
	glVertex2f(43.4, -5.31);
	glVertex2f(43.4, 4.95);
	glEnd();


	//BACKGROUND
	glColor3f(0.3,0.3,0.3);
	glBegin(GL_POLYGON);
	glVertex2f(-15.6, 46);
	glVertex2f(-15.6, -15.6);
	glVertex2f(46, -15.6);
	glVertex2f(46, 46);
	glEnd();
}

void affich_menu_opt1(char option)
{
	glMatrixMode(GL_MODELVIEW);
  	glLoadIdentity();

	glTranslatef(-15.5,-15.5,-53);


	print_rgb(15.2, 40.865, "Color Chlamydomonas", 0.8, 0.8, 0.8);
    print_rgb(15.2, 30.6, "Color aggregate", 0.8, 0.8, 0.8);
    print_rgb(15.2, 20.335, "Modify parameters", 0.8, 0.8, 0.8);
    print_rgb(15.2, 10.13, "Patches per time", 0.8, 0.8, 0.8);
    print_rgb(15.2, -0.135, "Back", 0.8, 0.8, 0.8);

    switch (option) {
    	case 1:	glColor3f(0.9,0.1,0.1);
		   	glBegin(GL_POLYGON);
			glVertex2f(-13, 46);
			glVertex2f(-13, 35.73);
			glVertex2f(43.4, 35.73);
			glVertex2f(43.4, 46);
			glEnd();
			break;
		case 2:	glColor3f(0.9, 0.1, 0.1);
			glBegin(GL_POLYGON);
			glVertex2f(-13, 35.73);
			glVertex2f(-13, 25.47);
			glVertex2f(43.4, 25.47);
			glVertex2f(43.4, 35.73);
			glEnd();
			break;
		case 3:	glColor3f(0.9,0.1,0.1);
			glBegin(GL_POLYGON);
			glVertex2f(-13, 25.47);
			glVertex2f(-13, 15.21);
			glVertex2f(43.4, 15.21);
			glVertex2f(43.4, 25.47);
			glEnd();
			break;
		case 4:	glColor3f(0.9, 0.1, 0.1);
			glBegin(GL_POLYGON);
			glVertex2f(-13, 15.21);
			glVertex2f(-13, 4.95);
			glVertex2f(43.4, 4.95);
			glVertex2f(43.4, 15.21);
			glEnd();
			break;
		case 5:	glColor3f(0.9, 0.1, 0.1);
			glBegin(GL_POLYGON);
			glVertex2f(-13, 4.95);
			glVertex2f(-13, -5.31);
			glVertex2f(43.4, -5.31);
			glVertex2f(43.4, 4.95);
			glEnd();
			break;
		case 6: glColor3f(0.9, 0.1, 0.1);
			glBegin(GL_POLYGON);
			glVertex2f(-13, -5.31);
			glVertex2f(-13, -15.57);
			glVertex2f(43.4, -15.57);
			glVertex2f(43.4, -5.31);
			glEnd();
			break;		
    }


	// -15.6 // 46
	glColor3f(0.1,0.1,0.1);
   	glBegin(GL_POLYGON);
	glVertex2f(-13, 46);
	glVertex2f(-13, 35.73);
	glVertex2f(43.4, 35.73);
	glVertex2f(43.4, 46);
	glEnd();

	glColor3f(0.12, 0.12, 0.12);
	glBegin(GL_POLYGON);
	glVertex2f(-13, 35.73);
	glVertex2f(-13, 25.47);
	glVertex2f(43.4, 25.47);
	glVertex2f(43.4, 35.73);
	glEnd();

	glColor3f(0.14,0.14,0.14);
	glBegin(GL_POLYGON);
	glVertex2f(-13, 25.47);
	glVertex2f(-13, 15.21);
	glVertex2f(43.4, 15.21);
	glVertex2f(43.4, 25.47);
	glEnd();

	glColor3f(0.16, 0.16, 0.16);
	glBegin(GL_POLYGON);
	glVertex2f(-13, 15.21);
	glVertex2f(-13, 4.95);
	glVertex2f(43.4, 4.95);
	glVertex2f(43.4, 15.21);
	glEnd();

	glColor3f(0.18, 0.18, 0.18);
	glBegin(GL_POLYGON);
	glVertex2f(-13, 4.95);
	glVertex2f(-13, -5.31);
	glVertex2f(43.4, -5.31);
	glVertex2f(43.4, 4.95);
	glEnd();
/*
	glColor3f(0.2, 0.2, 0.2);
	glBegin(GL_POLYGON);
	glVertex2f(-13, -5.31);
	glVertex2f(-13, -15.57);
	glVertex2f(43.4, -15.57);
	glVertex2f(43.4, -5.31);
	glEnd();
*/

	//BACKGROUND
	glColor3f(0.3,0.3,0.3);
	glBegin(GL_POLYGON);
	glVertex2f(-15.6, 46);
	glVertex2f(-15.6, -15.6);
	glVertex2f(46, -15.6);
	glVertex2f(46, 46);
	glEnd();
}

void tutorial()
{
	glMatrixMode(GL_MODELVIEW);
  	glLoadIdentity();

	glTranslatef(-15.5,-15.5,-53);


   	print_rgb(15.2, 40.865, "Welcome to our modelization program of Chlamydomonas Reinhardtii", 0.8, 0.8, 0.8);
    print_rgb(15.2, 37.865, "Thank you for using it and for every feedback you would provide", 0.8, 0.8, 0.8);
    print_rgb(15.2, 34.865, "Please feel free to email us at mainchlamproject@gmail.com", 0.8, 0.8, 0.8);
    print_rgb(15.2, 28.865, "The modelization will use a cubic world as drawn next", 0.8, 0.8, 0.8);

    glPushMatrix();

    float temp = size;
    size = 5;
    glRotatef(45, 0.5, 0.5, 0);
    glColor3f(1,0.1,0.14);
    cube(5.5,25.5,15.5);
    size = temp;
    glPopMatrix();

    print_rgb(15.2, -3.865, "You can start the modelization using 'a' or access the options", 0.8, 0.8, 0.8);
    print_rgb(15.2, -6.865, "using either 'esc' or a right click, then 'change parameters'", 0.8, 0.8, 0.8);
    print_rgb(15.2, -9.865, "Move the world around using arrowkeys, and advance in time hitting 'space'", 0.8, 0.8, 0.8);
    print_rgb(15.2, -12.865, "When you are ready to start, hit the corresponding key", 0.8, 0.8, 0.8);
}

void affich_menu_opt_patch(char option)
{
	glMatrixMode(GL_MODELVIEW);
  	glLoadIdentity();

	glTranslatef(-15.5,-15.5,-53);


   	print_rgb(15.2, 40.865, "1 patch per time", 0.8, 0.8, 0.8);
    print_rgb(15.2, 30.6, "2 patches per time", 0.8, 0.8, 0.8);
    print_rgb(15.2, 20.335, "3 patches per time", 0.8, 0.8, 0.8);
    print_rgb(15.2, 10.13, "4 patches per time", 0.8, 0.8, 0.8);
    print_rgb(15.2, -0.135, "5 patches per time", 0.8, 0.8, 0.8);
    print_rgb(15.2, -10.4, "Back", 0.8, 0.8, 0.8);

    switch (option) {
    	case 1:	glColor3f(0.9,0.1,0.1);
		   	glBegin(GL_POLYGON);
			glVertex2f(-13, 46);
			glVertex2f(-13, 35.73);
			glVertex2f(43.4, 35.73);
			glVertex2f(43.4, 46);
			glEnd();
		break;
		case 2:	glColor3f(0.9, 0.1, 0.1);
			glBegin(GL_POLYGON);
			glVertex2f(-13, 35.73);
			glVertex2f(-13, 25.47);
			glVertex2f(43.4, 25.47);
			glVertex2f(43.4, 35.73);
			glEnd();
		break;
		case 3:	glColor3f(0.9,0.1,0.1);
			glBegin(GL_POLYGON);
			glVertex2f(-13, 25.47);
			glVertex2f(-13, 15.21);
			glVertex2f(43.4, 15.21);
			glVertex2f(43.4, 25.47);
			glEnd();
		break;
		case 4:	glColor3f(0.9, 0.1, 0.1);
			glBegin(GL_POLYGON);
			glVertex2f(-13, 15.21);
			glVertex2f(-13, 4.95);
			glVertex2f(43.4, 4.95);
			glVertex2f(43.4, 15.21);
			glEnd();
		break;
		case 5:
			glColor3f(0.9, 0.1, 0.1);
			glBegin(GL_POLYGON);
			glVertex2f(-13, 4.95);
			glVertex2f(-13, -5.31);
			glVertex2f(43.4, -5.31);
			glVertex2f(43.4, 4.95);
			glEnd();
		break;
		case 6:	glColor3f(0.9, 0.1, 0.1);
			glBegin(GL_POLYGON);
			glVertex2f(-13, -5.31);
			glVertex2f(-13, -15.57);
			glVertex2f(43.4, -15.57);
			glVertex2f(43.4, -5.31);
			glEnd();
		break;
    }


	// -15.6 // 46
	glColor3f(0.1,0.1,0.1);
   	glBegin(GL_POLYGON);
	glVertex2f(-13, 46);
	glVertex2f(-13, 35.73);
	glVertex2f(43.4, 35.73);
	glVertex2f(43.4, 46);
	glEnd();

	glColor3f(0.12, 0.12, 0.12);
	glBegin(GL_POLYGON);
	glVertex2f(-13, 35.73);
	glVertex2f(-13, 25.47);
	glVertex2f(43.4, 25.47);
	glVertex2f(43.4, 35.73);
	glEnd();

	glColor3f(0.14,0.14,0.14);
	glBegin(GL_POLYGON);
	glVertex2f(-13, 25.47);
	glVertex2f(-13, 15.21);
	glVertex2f(43.4, 15.21);
	glVertex2f(43.4, 25.47);
	glEnd();

	glColor3f(0.16, 0.16, 0.16);
	glBegin(GL_POLYGON);
	glVertex2f(-13, 15.21);
	glVertex2f(-13, 4.95);
	glVertex2f(43.4, 4.95);
	glVertex2f(43.4, 15.21);
	glEnd();

	glColor3f(0.18, 0.18, 0.18);
	glBegin(GL_POLYGON);
	glVertex2f(-13, 4.95);
	glVertex2f(-13, -5.31);
	glVertex2f(43.4, -5.31);
	glVertex2f(43.4, 4.95);
	glEnd();

	glColor3f(0.2, 0.2, 0.2);
	glBegin(GL_POLYGON);
	glVertex2f(-13, -5.31);
	glVertex2f(-13, -15.57);
	glVertex2f(43.4, -15.57);
	glVertex2f(43.4, -5.31);
	glEnd();



	//BACKGROUND
	glColor3f(0.3,0.3,0.3);
	glBegin(GL_POLYGON);
	glVertex2f(-15.6, 46);
	glVertex2f(-15.6, -15.6);
	glVertex2f(46, -15.6);
	glVertex2f(46, 46);
	glEnd();
}

void which_param(char option)
{
	glMatrixMode(GL_MODELVIEW);
  	glLoadIdentity();

	glTranslatef(-15.5,-15.5,-53);


   	print_rgb(15.2, 40.865, "Probabilities", 0.8, 0.8, 0.8);
    print_rgb(15.2, 30.6, "Experiment size", 0.8, 0.8, 0.8);
    print_rgb(15.2, 20.335, "Experiment parameters", 0.8, 0.8, 0.8); //ADD A FACTORY RESET //ADD A BACK BUTTON
    print_rgb(15.2, 10.13, "Reset all values", 0.8, 0.8, 0.8);
    print_rgb(15.2, -0.135, "Back", 0.8, 0.8, 0.8);

    switch (option) {
    	case 1:	glColor3f(0.9,0.1,0.1);
		   	glBegin(GL_POLYGON);
			glVertex2f(-13, 46);
			glVertex2f(-13, 35.73);
			glVertex2f(43.4, 35.73);
			glVertex2f(43.4, 46);
			glEnd();
			break;
		case 2:	glColor3f(0.9, 0.1, 0.1);
			glBegin(GL_POLYGON);
			glVertex2f(-13, 35.73);
			glVertex2f(-13, 25.47);
			glVertex2f(43.4, 25.47);
			glVertex2f(43.4, 35.73);
			glEnd();
			break;
		case 3:	glColor3f(0.9,0.1,0.1);
			glBegin(GL_POLYGON);
			glVertex2f(-13, 25.47);
			glVertex2f(-13, 15.21);
			glVertex2f(43.4, 15.21);
			glVertex2f(43.4, 25.47);
			glEnd();
			break;
		case 4:	glColor3f(0.9, 0.1, 0.1);
			glBegin(GL_POLYGON);
			glVertex2f(-13, 15.21);
			glVertex2f(-13, 4.95);
			glVertex2f(43.4, 4.95);
			glVertex2f(43.4, 15.21);
			glEnd();
			break;
		case 5:	glColor3f(0.9, 0.1, 0.1);
			glBegin(GL_POLYGON);
			glVertex2f(-13, 4.95);
			glVertex2f(-13, -5.31);
			glVertex2f(43.4, -5.31);
			glVertex2f(43.4, 4.95);
			glEnd();
			break;
	}

	// -15.6 // 46
	glColor3f(0.1,0.1,0.1);
   	glBegin(GL_POLYGON);
	glVertex2f(-13, 46);
	glVertex2f(-13, 35.73);
	glVertex2f(43.4, 35.73);
	glVertex2f(43.4, 46);
	glEnd();

	glColor3f(0.12, 0.12, 0.12);
	glBegin(GL_POLYGON);
	glVertex2f(-13, 35.73);
	glVertex2f(-13, 25.47);
	glVertex2f(43.4, 25.47);
	glVertex2f(43.4, 35.73);
	glEnd();

	glColor3f(0.14,0.14,0.14);
	glBegin(GL_POLYGON);
	glVertex2f(-13, 25.47);
	glVertex2f(-13, 15.21);
	glVertex2f(43.4, 15.21);
	glVertex2f(43.4, 25.47);
	glEnd();

	glColor3f(0.16, 0.16, 0.16);
	glBegin(GL_POLYGON);
	glVertex2f(-13, 15.21);
	glVertex2f(-13, 4.95);
	glVertex2f(43.4, 4.95);
	glVertex2f(43.4, 15.21);
	glEnd();

	glColor3f(0.18, 0.18, 0.18);
	glBegin(GL_POLYGON);
	glVertex2f(-13, 4.95);
	glVertex2f(-13, -5.31);
	glVertex2f(43.4, -5.31);
	glVertex2f(43.4, 4.95);
	glEnd();



	//BACKGROUND
	glColor3f(0.3,0.3,0.3);
	glBegin(GL_POLYGON);
	glVertex2f(-15.6, 46);
	glVertex2f(-15.6, -15.6);
	glVertex2f(46, -15.6);
	glVertex2f(46, 46);
	glEnd();
}

void which_prob_param(char option)
{
	glMatrixMode(GL_MODELVIEW);
  	glLoadIdentity();

	glTranslatef(-15.5,-15.5,-53);

   	print_rgb(15.2, 42.15, "Probability to aggregate between cells", 0.8, 0.8, 0.8);
    print_rgb(15.2, 34.45, "Probability to aggregate alone", 0.8, 0.8, 0.8);
    print_rgb(15.2, 26.75, "Decrease of mitosis probability in aggregates, per component", 0.8, 0.8, 0.8);
    print_rgb(15.2, 19.05, "Probability of mitosis when alone", 0.8, 0.8, 0.8);
    print_rgb(15.2, 11.35, "Probability to get nutrients from environment", 0.8, 0.8, 0.8);
	print_rgb(15.2, 3.65, "Probability to change direction each time iteration", 0.8, 0.8, 0.8);
	print_rgb(15.2, -4.05, "Probability to die from stress", 0.8, 0.8, 0.8);
	print_rgb(15.2, -11.75, "Probability for an aggregate to disaggregate", 0.8, 0.8, 0.8);

    switch (option) {
    	case 1:	glColor3f(0.9,0.1,0.1);
		   	glBegin(GL_POLYGON);
			glVertex2f(-13, 46);
			glVertex2f(-13, 38.3);
			glVertex2f(43.4, 38.3);
			glVertex2f(43.4, 46);
			glEnd();
			break;
		case 2:	glColor3f(0.9, 0.1, 0.1);
			glBegin(GL_POLYGON);
			glVertex2f(-13, 38.3);
			glVertex2f(-13, 30.60);
			glVertex2f(43.4, 30.6);
			glVertex2f(43.4, 38.3);
			glEnd();
			break;
		case 3:	glColor3f(0.9,0.1,0.1);
			glBegin(GL_POLYGON);
			glVertex2f(-13, 30.6);
			glVertex2f(-13, 22.9);
			glVertex2f(43.4, 22.9);
			glVertex2f(43.4, 30.6);
			glEnd();
			break;
		case 4:	glColor3f(0.9, 0.1, 0.1);
			glBegin(GL_POLYGON);
			glVertex2f(-13, 22.9);
			glVertex2f(-13, 15.20);
			glVertex2f(43.4, 15.20);
			glVertex2f(43.4, 22.9);
			glEnd();
			break;
		case 5:glColor3f(0.9, 0.1, 0.1);
			glBegin(GL_POLYGON);
			glVertex2f(-13, 15.2);
			glVertex2f(-13, 7.5);
			glVertex2f(43.4, 7.5);
			glVertex2f(43.4, 15.2);
			glEnd();
			break;
		case 6:glColor3f(0.9, 0.1, 0.1);
			glBegin(GL_POLYGON);
			glVertex2f(-13, 7.5);
			glVertex2f(-13, -0.2);
			glVertex2f(43.4, -0.2);
			glVertex2f(43.4, 7.5);
			glEnd();
			break;
		case 7:glColor3f(0.9, 0.1, 0.1);
			glBegin(GL_POLYGON);
			glVertex2f(-13, -0.2);
			glVertex2f(-13, -7.9);
			glVertex2f(43.4, -7.9);
			glVertex2f(43.4, -0.2);
			glEnd();
			break;
		case 8:glColor3f(0.9, 0.1, 0.1);
			glBegin(GL_POLYGON);
			glVertex2f(-13, -7.9);
			glVertex2f(-13, -15.6);
			glVertex2f(43.4, -15.60);
			glVertex2f(43.4, -7.9);
			glEnd();
			break;
	}

	// -15.6 // 46
	glColor3f(0.1,0.1,0.1);
   	glBegin(GL_POLYGON);
	glVertex2f(-13, 46);
	glVertex2f(-13, 38.3);
	glVertex2f(43.4, 38.3);
	glVertex2f(43.4, 46);
	glEnd();

	glColor3f(0.12, 0.12, 0.12);
	glBegin(GL_POLYGON);
	glVertex2f(-13, 38.3);
	glVertex2f(-13, 30.60);
	glVertex2f(43.4, 30.6);
	glVertex2f(43.4, 38.3);
	glEnd();

	glColor3f(0.14,0.14,0.14);
	glBegin(GL_POLYGON);
	glVertex2f(-13, 30.6);
	glVertex2f(-13, 22.9);
	glVertex2f(43.4, 22.9);
	glVertex2f(43.4, 30.6);
	glEnd();

	glColor3f(0.16, 0.16, 0.16);
	glBegin(GL_POLYGON);
	glVertex2f(-13, 22.9);
	glVertex2f(-13, 15.20);
	glVertex2f(43.4, 15.20);
	glVertex2f(43.4, 22.9);
	glEnd();

	glColor3f(0.18, 0.18, 0.18);
	glBegin(GL_POLYGON);
	glVertex2f(-13, 15.2);
	glVertex2f(-13, 7.5);
	glVertex2f(43.4, 7.5);
	glVertex2f(43.4, 15.2);
	glEnd();

	glColor3f(0.2, 0.2, 0.2);
	glBegin(GL_POLYGON);
	glVertex2f(-13, 7.5);
	glVertex2f(-13, -0.2);
	glVertex2f(43.4, -0.2);
	glVertex2f(43.4, 7.5);
	glEnd();

	glColor3f(0.22, 0.22, 0.22);
	glBegin(GL_POLYGON);
	glVertex2f(-13, -0.2);
	glVertex2f(-13, -7.9);
	glVertex2f(43.4, -7.9);
	glVertex2f(43.4, -0.2);
	glEnd();

	glColor3f(0.24, 0.24, 0.24);
	glBegin(GL_POLYGON);
	glVertex2f(-13, -7.9);
	glVertex2f(-13, -15.6);
	glVertex2f(43.4, -15.6);
	glVertex2f(43.4, -7.9);
	glEnd();



	//BACKGROUND
	glColor3f(0.3,0.3,0.3);
	glBegin(GL_POLYGON);
	glVertex2f(-15.6, 46);
	glVertex2f(-15.6, -15.6);
	glVertex2f(46, -15.6);
	glVertex2f(46, 46);
	glEnd();
}

void which_model_param(char option)
{
	glMatrixMode(GL_MODELVIEW);
  	glLoadIdentity();

	glTranslatef(-15.5,-15.5,-53);

   	print_rgb(15.2, 40.865, "Minimal value for X", 0.8, 0.8, 0.8);
    print_rgb(15.2, 30.6, "Maximal value for X", 0.8, 0.8, 0.8);
    print_rgb(15.2, 20.335, "Minimal value for Y", 0.8, 0.8, 0.8);
    print_rgb(15.2, 10.13, "Maximal value for Y", 0.8, 0.8, 0.8);
    print_rgb(15.2, -0.135, "Minimal value for Z", 0.8, 0.8, 0.8);
    print_rgb(15.2, -10.4, "Maximal value for Z", 0.8, 0.8, 0.8);

    switch (option) {
    	case 1:	glColor3f(0.9,0.1,0.1);
		   	glBegin(GL_POLYGON);
			glVertex2f(-13, 46);
			glVertex2f(-13, 35.73);
			glVertex2f(43.4, 35.73);
			glVertex2f(43.4, 46);
			glEnd();
		break;
		case 2:	glColor3f(0.9, 0.1, 0.1);
			glBegin(GL_POLYGON);
			glVertex2f(-13, 35.73);
			glVertex2f(-13, 25.47);
			glVertex2f(43.4, 25.47);
			glVertex2f(43.4, 35.73);
			glEnd();
		break;
		case 3:	glColor3f(0.9,0.1,0.1);
			glBegin(GL_POLYGON);
			glVertex2f(-13, 25.47);
			glVertex2f(-13, 15.21);
			glVertex2f(43.4, 15.21);
			glVertex2f(43.4, 25.47);
			glEnd();
		break;
		case 4:	glColor3f(0.9, 0.1, 0.1);
			glBegin(GL_POLYGON);
			glVertex2f(-13, 15.21);
			glVertex2f(-13, 4.95);
			glVertex2f(43.4, 4.95);
			glVertex2f(43.4, 15.21);
			glEnd();
		break;
		case 5:
			glColor3f(0.9, 0.1, 0.1);
			glBegin(GL_POLYGON);
			glVertex2f(-13, 4.95);
			glVertex2f(-13, -5.31);
			glVertex2f(43.4, -5.31);
			glVertex2f(43.4, 4.95);
			glEnd();
		break;
		case 6:	glColor3f(0.9, 0.1, 0.1);
			glBegin(GL_POLYGON);
			glVertex2f(-13, -5.31);
			glVertex2f(-13, -15.57);
			glVertex2f(43.4, -15.57);
			glVertex2f(43.4, -5.31);
			glEnd();
		break;
    }


	// -15.6 // 46
	glColor3f(0.1,0.1,0.1);
   	glBegin(GL_POLYGON);
	glVertex2f(-13, 46);
	glVertex2f(-13, 35.73);
	glVertex2f(43.4, 35.73);
	glVertex2f(43.4, 46);
	glEnd();

	glColor3f(0.12, 0.12, 0.12);
	glBegin(GL_POLYGON);
	glVertex2f(-13, 35.73);
	glVertex2f(-13, 25.47);
	glVertex2f(43.4, 25.47);
	glVertex2f(43.4, 35.73);
	glEnd();

	glColor3f(0.14,0.14,0.14);
	glBegin(GL_POLYGON);
	glVertex2f(-13, 25.47);
	glVertex2f(-13, 15.21);
	glVertex2f(43.4, 15.21);
	glVertex2f(43.4, 25.47);
	glEnd();

	glColor3f(0.16, 0.16, 0.16);
	glBegin(GL_POLYGON);
	glVertex2f(-13, 15.21);
	glVertex2f(-13, 4.95);
	glVertex2f(43.4, 4.95);
	glVertex2f(43.4, 15.21);
	glEnd();

	glColor3f(0.18, 0.18, 0.18);
	glBegin(GL_POLYGON);
	glVertex2f(-13, 4.95);
	glVertex2f(-13, -5.31);
	glVertex2f(43.4, -5.31);
	glVertex2f(43.4, 4.95);
	glEnd();

	glColor3f(0.2, 0.2, 0.2);
	glBegin(GL_POLYGON);
	glVertex2f(-13, -5.31);
	glVertex2f(-13, -15.57);
	glVertex2f(43.4, -15.57);
	glVertex2f(43.4, -5.31);
	glEnd();



	//BACKGROUND
	glColor3f(0.3,0.3,0.3);
	glBegin(GL_POLYGON);
	glVertex2f(-15.6, 46);
	glVertex2f(-15.6, -15.6);
	glVertex2f(46, -15.6);
	glVertex2f(46, 46);
	glEnd();
}

void which_exp_param(char option)
{
	glMatrixMode(GL_MODELVIEW);
  	glLoadIdentity();

	glTranslatef(-15.5,-15.5,-53);

   	print_rgb(15.2, 40.865, "Number of Chlamydomonas to start the experiment", 0.8, 0.8, 0.8);
    print_rgb(15.2, 30.6, "Energy to start with", 0.8, 0.8, 0.8);
    print_rgb(15.2, 20.335, "Distance at which they enter an aggregate", 0.8, 0.8, 0.8);
    print_rgb(15.2, 10.13, "Energy increase when successful getting nutrients", 0.8, 0.8, 0.8);
    print_rgb(15.2, -0.135, "Energy decrease when failed getting nutrients", 0.8, 0.8, 0.8);

    switch (option) {
    	case 1:	glColor3f(0.9,0.1,0.1);
		   	glBegin(GL_POLYGON);
			glVertex2f(-13, 46);
			glVertex2f(-13, 35.73);
			glVertex2f(43.4, 35.73);
			glVertex2f(43.4, 46);
			glEnd();
		break;
		case 2:	glColor3f(0.9, 0.1, 0.1);
			glBegin(GL_POLYGON);
			glVertex2f(-13, 35.73);
			glVertex2f(-13, 25.47);
			glVertex2f(43.4, 25.47);
			glVertex2f(43.4, 35.73);
			glEnd();
		break;
		case 3:	glColor3f(0.9,0.1,0.1);
			glBegin(GL_POLYGON);
			glVertex2f(-13, 25.47);
			glVertex2f(-13, 15.21);
			glVertex2f(43.4, 15.21);
			glVertex2f(43.4, 25.47);
			glEnd();
		break;
		case 4:	glColor3f(0.9, 0.1, 0.1);
			glBegin(GL_POLYGON);
			glVertex2f(-13, 15.21);
			glVertex2f(-13, 4.95);
			glVertex2f(43.4, 4.95);
			glVertex2f(43.4, 15.21);
			glEnd();
		break;
		case 5:
			glColor3f(0.9, 0.1, 0.1);
			glBegin(GL_POLYGON);
			glVertex2f(-13, 4.95);
			glVertex2f(-13, -5.31);
			glVertex2f(43.4, -5.31);
			glVertex2f(43.4, 4.95);
			glEnd();
		break;
    }


	// -15.6 // 46
	glColor3f(0.1,0.1,0.1);
   	glBegin(GL_POLYGON);
	glVertex2f(-13, 46);
	glVertex2f(-13, 35.73);
	glVertex2f(43.4, 35.73);
	glVertex2f(43.4, 46);
	glEnd();

	glColor3f(0.12, 0.12, 0.12);
	glBegin(GL_POLYGON);
	glVertex2f(-13, 35.73);
	glVertex2f(-13, 25.47);
	glVertex2f(43.4, 25.47);
	glVertex2f(43.4, 35.73);
	glEnd();

	glColor3f(0.14,0.14,0.14);
	glBegin(GL_POLYGON);
	glVertex2f(-13, 25.47);
	glVertex2f(-13, 15.21);
	glVertex2f(43.4, 15.21);
	glVertex2f(43.4, 25.47);
	glEnd();

	glColor3f(0.16, 0.16, 0.16);
	glBegin(GL_POLYGON);
	glVertex2f(-13, 15.21);
	glVertex2f(-13, 4.95);
	glVertex2f(43.4, 4.95);
	glVertex2f(43.4, 15.21);
	glEnd();

	glColor3f(0.18, 0.18, 0.18);
	glBegin(GL_POLYGON);
	glVertex2f(-13, 4.95);
	glVertex2f(-13, -5.31);
	glVertex2f(43.4, -5.31);
	glVertex2f(43.4, 4.95);
	glEnd();



	//BACKGROUND
	glColor3f(0.3,0.3,0.3);
	glBegin(GL_POLYGON);
	glVertex2f(-15.6, 46);
	glVertex2f(-15.6, -15.6);
	glVertex2f(46, -15.6);
	glVertex2f(46, 46);
	glEnd();
}

void modif_param(int parameter)
{
	glMatrixMode(GL_MODELVIEW);
  	glLoadIdentity();

	glTranslatef(-15.5,-15.5,-53);

	print_rgb(-0.2, 21.36, "-", 0.8, 0.8, 0.8);
	print_rgb(30.6, 21.36, "+", 0.8, 0.8, 0.8);

	glColor3f(0.2,0.2,0.2);
	glBegin(GL_POLYGON);
	glVertex2f(-4.05, 17.71);
	glVertex2f(-4.05, 25.01);
	glVertex2f(3.65, 25.01);
	glVertex2f(3.65, 17.71);
	glEnd(); // 25% +- 6.25% // 60% +- 6.25%

	glBegin(GL_POLYGON);
	glVertex2f(26.75, 17.71);
	glVertex2f(26.75, 25.01);
	glVertex2f(34.45, 25.01);
	glVertex2f(34.45, 17.71);
	glEnd(); // 75% +- 6.25% // 60% +- 6.25%
	
	double temp = 0;
	char string[10];
	char test = 1;

	switch (parameter) {
		case 1: //prob_aggregation_between_cells
			print_rgb(15.2, 30, "Probability to aggregate between cells", 0.8, 0.8, 0.8);
			temp = prob_aggregation_between_cells / 10.0;
			break;
		case 2: //prob_self_aggregating;
			print_rgb(15.2, 30, "Probability to aggregate alone", 0.8, 0.8, 0.8);
			temp = prob_self_aggregating / 10.0;
			break;
		case 3: //dimin_prob_clonage;
			print_rgb(15.2, 30, "Decrease of mitosis probability in aggregates, per component", 0.8, 0.8, 0.8);
			temp = dimin_prob_clonage / 10.0;
			break;
		case 4: //prob_init_clonage;
			print_rgb(15.2, 30, "Probability of mitosis when alone", 0.8, 0.8, 0.8);
			temp = prob_init_clonage / 10.0;
			break;
		case 5: //prob_eat;
			print_rgb(15.2, 30, "Probability to get nutrients from environment", 0.8, 0.8, 0.8);
			temp = prob_eat / 10.0;
			break;
		case 6: //prob_change_direction;
			print_rgb(15.2, 30, "Probability to change direction each time iteration", 0.8, 0.8, 0.8);
			temp = prob_change_direction / 10.0;
			break;
		case 7: //prob_die;
			print_rgb(15.2, 30, "Probability to die from stress", 0.8, 0.8, 0.8);
			temp = prob_die / 10.0;
			break;
		case 8: //prob_disaggregation;
			print_rgb(15.2, 30, "Probability for an aggregate to disaggregate", 0.8, 0.8, 0.8);
			temp = prob_disaggregation / 10.0;
			break;
		case 9://XMIN;
			print_rgb(15.2, 30, "Minimal value for X", 0.8, 0.8, 0.8);
			temp = XMIN;
			test = 0;
			break;
		case 10: //XMAX;
			print_rgb(15.2, 30, "Maximal value for X", 0.8, 0.8, 0.8);
			temp = XMAX;
			test = 0;
			break;
		case 11: //YMIN;
			print_rgb(15.2, 30, "Minimal value for Y", 0.8, 0.8, 0.8);
			temp = YMIN;
			test = 0;
			break;
		case 12: //YMAX;
			print_rgb(15.2, 30, "Maximal value for Y", 0.8, 0.8, 0.8);
			temp = YMAX;
			test = 0;
			break;
		case 13: //ZMIN;
			print_rgb(15.2, 30, "Minimal value for Z", 0.8, 0.8, 0.8);
			temp = ZMIN;
			test = 0;
			break;
		case 14: //ZMAX;
			print_rgb(15.2, 30, "Maximal value for Z", 0.8, 0.8, 0.8);
			temp = ZMAX;
			test = 0;
			break;
		case 15: //NB_INIT;
			print_rgb(15.2, 30, "Number of Chlamydomonas to start the experiment", 0.8, 0.8, 0.8);
			temp = NB_INIT;
			test = 0;
			break;
		case 16: //FOOD_INIT;
			print_rgb(15.2, 30, "Energy to start with", 0.8, 0.8, 0.8);
			temp = FOOD_INIT;
			test = 0;
			break;
		case 17: //DIST_AGGREGATE;
			print_rgb(15.2, 30, "Distance at which they enter an aggregate", 0.8, 0.8, 0.8);
			temp = DIST_AGGREGATE;
			test = 0;
			break;
		case 18: //food_increase;
			print_rgb(15.2, 30, "Energy increase when successful getting nutrients", 0.8, 0.8, 0.8);
			temp = food_increase;
			test = 0;
			break;
		case 19: //food_decrease;
			print_rgb(15.2, 30, "Energy decrease when failed getting nutrients", 0.8, 0.8, 0.8);
			temp = food_decrease;
			test = 0;
			break;
	}


	if (test) {
		print_rgb(-0.2, 36.76, "+/-0.1%", 0.8,0.8,0.8);//AFFICHER LES BOUTONS DE MODIF D'incrementor
		print_rgb(15.2, 36.76, "+/-1%", 0.8, 0.8, 0.8);
		print_rgb(30.6, 36.76, "+/-10%", 0.8, 0.8, 0.8);

		sprintf(string, "%.1lf%%", temp);
	}
	else {
		print_rgb(-0.2, 36.76, "+/-1", 0.8,0.8,0.8);//AFFICHER LES BOUTONS DE MODIF D'incrementor
		print_rgb(15.2, 36.76, "+/-10", 0.8, 0.8, 0.8);
		print_rgb(30.6, 36.76, "+/-100", 0.8, 0.8, 0.8);

		sprintf(string, "%d", (int) temp);
	}
	print_rgb(15.2, 20, string, 0.8, 0.8, 0.8);

	
	glColor3f(0.2,0.2,0.2);
	glBegin(GL_POLYGON);
	glVertex2f(-3.28, 33.68);
	glVertex2f(-3.28, 39.84);
	glVertex2f(2.88, 39.84);
	glVertex2f(2.88, 33.68);
	glEnd(); //25% +- 5% // 85% +-5%

	glColor3f(0.2,0.2,0.2);
	glBegin(GL_POLYGON);
	glVertex2f(12.12, 33.68);
	glVertex2f(12.12, 39.84);
	glVertex2f(18.28, 39.84);
	glVertex2f(18.28, 33.68);
	glEnd();//50% +- 5% // 85% +- 5%

	glColor3f(0.2,0.2,0.2);
	glBegin(GL_POLYGON);
	glVertex2f(27.52, 33.68);
	glVertex2f(27.52, 39.84);
	glVertex2f(33.68, 39.84);
	glVertex2f(33.68, 33.68);
	glEnd();//75% +- 5%// 85% +- 5%

	print_rgb(15.2, 2.88, "Enter the value with console",0.8,0.8,0.8);
	glColor3f(0.2,0.2,0.2);
	glBegin(GL_POLYGON);
	glVertex2f(-0.2, 5.96);
	glVertex2f(-0.2, -0.2);
	glVertex2f(30.6, -0.2);
	glVertex2f(30.6, 5.96);
	glEnd(); // 50% +- 25% // 30% +- 5%
	

	print_rgb(15.2, -6.36, "Validate", 0.8,0.8,0.8);
	glColor3f(0.2,0.2,0.2);
	glBegin(GL_POLYGON);
	glVertex2f(9.04, -9.44);
	glVertex2f(9.04, -2.88);
	glVertex2f(21.36, -2.88);
	glVertex2f(21.36, -9.44);
	glEnd(); // 50% +- 10% // 15% +- 5%

	glColor3f(0.08,0.08,0.08);
	glBegin(GL_POLYGON);
	glVertex2f(-15.6, 46);
	glVertex2f(-15.6, -15.6);
	glVertex2f(46, -15.6);
	glVertex2f(46, 46);
	glEnd();
}

void draw3D()
{
	glClearColor(0,0,0,1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	if (NO_MORE_MEMORY)
		printf("A memory allocation failed, we closed the experiment\n");
	else if (is_tutorial)
		tutorial();
	else {
		switch (test_options) {
			case -1: 
				affich_message(pass);
				pass = 0;
				break;
			case 0: 
				glMatrixMode(GL_MODELVIEW);
			  	glLoadIdentity();

			  	glColor3f(0.1,0.1,0.1);
			  	glutSolidSphere(2 * radius, 10, 10);

			  	gluLookAt(camera_x, camera_y, camera_z,		 0, 0, 0,	 	0, 1, 0);
			  				//Position of our eye			Where we look 	Vertical axis

			  	glTranslatef(-(XMIN + XMAX)/2, -(YMIN + YMAX)/2, -(ZMIN + ZMAX)/2);


				print_chlam(head_chlam);
	        	print_aggregates(head_aggregate);

				break;
			case 1:	affich_menu(0);
			    break;
		    case 11: affich_menu(1);
			    break;
		    case 21: affich_menu(2);
			    break;
		    case 31: affich_menu(3);
			    break;
		    case 41: affich_menu(4);
			    break;
		    case 51 : affich_menu(5);
			    break;
		    case 100: affich_menu_opt1(0);
			    break;
		    case 110: affich_menu_opt1(1);
			    break;
		    case 120 : affich_menu_opt1(2);
			    break;
		    case 130 : affich_menu_opt1(3);
			    break;
		    case 140 : affich_menu_opt1(4);
			    break;
			case 150: affich_menu_opt1(5);
				break;
//			case 160: affich_menu_opt1(6);
//				break;
		    case 200: affich_menu_opt_patch(0);
			    break;
		    case 210: affich_menu_opt_patch(1);
			   	break;
		    case 220: affich_menu_opt_patch(2);
			    break;
		    case 230: affich_menu_opt_patch(3);
			    break;
		    case 240: affich_menu_opt_patch(4);
			    break;
		    case 250: affich_menu_opt_patch(5);
			    break;
		    case 260: affich_menu_opt_patch(6);
			    break;
		    case 302: affich_colors();
			    break;
		    case 301: affich_colors();
			    break;
			case 400: which_param(0); //modify to chose the parameter
				break;
			case 410: which_param(1);
				break;
			case 420: which_param(2);
				break;
			case 430: which_param(3);
				break;
			case 440: which_param(4);
				break;
			case 450: which_param(5);
				break;
		    case 500: affich_credits();
		    	temp = 0;
		    	pass = 0;
		    	test_options = 0;
		    	glutPostRedisplay();
			    break;
			case 600: which_prob_param(0);
				break;
			case 610: which_prob_param(1);
				break;
			case 620: which_prob_param(2);
				break;
			case 630: which_prob_param(3);
				break;
			case 640: which_prob_param(4);
				break;
			case 650: which_prob_param(5);
				break;
			case 660: which_prob_param(6);
				break;
			case 670: which_prob_param(7);
				break;
			case 680: which_prob_param(8);
				break;
			case 601: modif_param(1);
				break;
			case 602: modif_param(2);
				break;
			case 603: modif_param(3);
				break;
			case 604: modif_param(4);
				break;
			case 605: modif_param(5);
				break;
			case 606: modif_param(6);
				break;
			case 607: modif_param(7);
				break;
			case 608: modif_param(8);
				break;
			case 609: modif_param(9);
				break;
			case 611: modif_param(10);
				break;
			case 612: modif_param(11);
				break;
			case 613 : modif_param(12);
				break;
			case 614 : modif_param(13);
				break;
			case 615 : modif_param(14);
				break;
			case 616 : modif_param(15);
				break;
			case 617 : modif_param(16);
				break;
			case 618 : modif_param(17);
				break;
			case 619 : modif_param(18);
				break;
			case 621 : modif_param(19);
				break;
			case 700: which_model_param(0);
				break;
			case 710: which_model_param(1);
				break;
			case 720: which_model_param(2);
				break;
			case 730: which_model_param(3);
				break;
			case 740: which_model_param(4);
				break;
			case 750: which_model_param(5);
				break;
			case 760: which_model_param(6);
				break;
			case 800: which_exp_param(0);
				break;
			case 810: which_exp_param(1);
				break;
			case 820: which_exp_param(2);
				break;
			case 830: which_exp_param(3);
				break;
			case 840: which_exp_param(4);
				break;
			case 850: which_exp_param(5);
				break;
		}
	}

	glFlush();
    glutSwapBuffers();
}