#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <math.h>

#include "structures.h"
#include "headers.h"

extern Numb_per_coord numb_per_coord;
extern Chlamydomonas *head_chlam;
extern Aggregate *head_aggregate;

#define WIDTH  800
#define HEIGHT  800


int XMIN = 1;
int XMAX = 30;
int YMIN = 1;
int YMAX = 30;
int ZMIN = 1;
int ZMAX = 30;
int NB_INIT = 2000;
int FOOD_INIT = 15;
float DIST_AGGREGATE = 1.0;
int food_increase = 2;
/* The food increase amount is how much energy eating gives minus the energy depleted per "round"*/
int food_decrease = 1;
float size = 0.075;
int test_options = 0;
int id_window = 0;
int patches_per_draw = 1;
int coord_maxima = 0;
int coord_minima = 0;
float radius = 0;
char NO_MORE_MEMORY = 0;
char is_initiated = 0;

float angle_up_down = 0;
float angle_right_left = 0;
int camera_x = 0;
int camera_y = 0;
int camera_z = 0;

int prob_aggregation_between_cells = 45; 
int prob_self_aggregating = 200;
int dimin_prob_clonage = 16; 
int prob_init_clonage = 100;
int prob_eat = 4000;
int prob_change_direction = 100;
int prob_die = 50;
int prob_disaggregation = 10;
int prob_max = 1000;

char is_tutorial = 1;

void radius_min_max() 
{
    if (XMIN > YMIN) {
        if (YMIN > ZMIN)
            coord_minima = ZMIN;
        else coord_minima = YMIN;
    }
    else if (XMIN > ZMIN) coord_minima = ZMIN;
    else coord_minima = XMIN;
    if (XMAX < YMAX) {
        if (YMAX < ZMAX) coord_maxima = ZMAX;
        else coord_maxima = YMAX;
    }
    else if (XMAX > ZMAX) coord_maxima = XMAX;
    else coord_maxima = ZMAX;
    if (XMAX - XMIN < YMAX - YMIN) {
        if (XMAX - XMIN > ZMAX - ZMIN)
            radius = sqrt((XMAX - XMIN)*(XMAX - XMIN) + (YMAX - YMIN)*(YMAX - YMIN));
        else radius = sqrt((ZMAX - ZMIN)*(ZMAX - ZMIN) + (YMAX - YMIN)*(YMAX - YMIN));
    }
    else if (YMAX - YMIN < ZMAX - ZMIN)
        radius = sqrt((XMAX - XMIN)*(XMAX - XMIN) + (ZMAX - ZMIN)*(ZMAX - ZMIN));
    else radius = sqrt((XMAX - XMIN)*(XMAX - XMIN) + (YMAX - YMIN)*(YMAX - YMIN));
}

int main(int argc, char *argv[])
{
    radius_min_max();
    camera_z = radius;
    glutInit(&argc, argv);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutInitWindowPosition(0,0);

    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE);

    id_window = glutCreateWindow(argv[0]);
    glutDisplayFunc(draw3D);

    glutKeyboardFunc(KeyboardManagement);
    glutMouseFunc(MouseManagement);
    glutSpecialUpFunc(ArrowkeysManagement);
    glutReshapeFunc(reshape);
    init_menu();

    if (test_options == 0) {
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();

        gluPerspective(60, 1, 1, 2 * radius);
        glViewport(0, 0, WIDTH, HEIGHT);

        glEnable(GL_DEPTH_TEST);
    }

    glutMainLoop();
}