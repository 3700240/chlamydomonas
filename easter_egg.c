#include <unistd.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <string.h>

extern float temp;

extern void *font;
void print_rgb(float x, float y, char *string, float r, float g, float b);

//TRAVAILLER LE CENTERING DU TEXTE

void affich_credits()
{
	if (temp >= 106) return;

	while (temp < 106) {
		glClearColor(0,0,0,1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		print_rgb(15.2, -16 + temp, "Developer team:", 0.8, 0.8, 0.8);
		print_rgb(15.2, -20 + temp, "Arthur GUILLEC", 0.8, 0.8, 0.8);
		print_rgb(15.2, -23 + temp, "Chaimae LAHRAIRI", 0.8, 0.8, 0.8);
		print_rgb(15.2, -26 + temp, "Heloise VIOSSAT", 0.8, 0.8, 0.8);
		print_rgb(15.2, -29 + temp, "Michele BONA", 0.8, 0.8, 0.8);
		print_rgb(15.2, -32 + temp, "Nael SENNOUN", 0.8, 0.8, 0.8);
		print_rgb(15.2, -35 + temp, "Victor DROUARD", 0.8, 0.8, 0.8);

		print_rgb(15.2, -41 + temp, "Project supervisor:", 0.8, 0.8, 0.8);
		print_rgb(15.2, -45 + temp, "Antoine DANON", 0.8, 0.8, 0.8);

		print_rgb(15.2, -51 + temp, "Special thanks to:", 0.8, 0.8, 0.8);
		print_rgb(15.2, -55 + temp, "Christophe RENAUD", 0.8, 0.8, 0.8);

		glFlush();
	    glutSwapBuffers();

	    usleep(4000); // sleeps 200ms

		temp += 0.1;		
	}
}

void draw_snowman()
{
	glClearColor(0,0,0,1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
  	glLoadIdentity();

  	gluLookAt(0, 1.3, 2, 0, 1, 0, 0, 1, 0);

  	glColor3f(1,1,1);

  	glTranslatef(0, 0.75, 0);
	glutSolidSphere(0.75, 100, 100); //Body

	glTranslatef(0, 1, 0);
	glutSolidSphere(0.25, 100, 100); //Head

	glPushMatrix();
	glColor3f(0,0,0);
	glTranslatef(0.05, 0.1, 0.18);
	glutSolidSphere(0.05, 10, 10);
	glTranslatef(-0.1, 0, 0);
	glutSolidSphere(0.05, 10, 10);
	glPopMatrix(); //Eyes

	glColor3f(1, 0.5, 0.5);
	glutSolidCone(0.08, 0.5, 10, 2);
}


void affich_message(unsigned char test) {
	switch (test) {
		case 1:
		   	print_rgb(15.2, 40.865, "Alors tu es arrivée là...?", 0.8, 0.8, 0.8);
		    print_rgb(15.2, 30.6, "2 patches per time", 0.8, 0.8, 0.8);
		    print_rgb(15.2, 20.335, "3 patches per time", 0.8, 0.8, 0.8);
		    print_rgb(15.2, 10.13, "4 patches per time", 0.8, 0.8, 0.8);
		    print_rgb(15.2, -0.135, "5 patches per time", 0.8, 0.8, 0.8);
		    print_rgb(15.2, -10.4, "Resume", 0.8, 0.8, 0.8);
			break;
		case 2:
			draw_snowman();
			glFlush();
			glutSwapBuffers();
			break;
	}
}