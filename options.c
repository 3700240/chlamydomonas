#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdio.h>
#include <math.h>

#include "structures.h"
#include "globales.h"
#include "headers.h"

extern Chlamydomonas *head_chlam;
extern Aggregate *head_aggregate;

extern float red_chlam;
extern float green_chlam;
extern float blue_chlam;
extern float red_aggr;
extern float green_aggr;
extern float blue_aggr;
extern char is_initiated;
int pass = 0;



void KeyboardManagement(unsigned char key, int x, int y)
{
    switch (key) {
        case 'a': 
            if (is_tutorial)
                is_tutorial = 0;
            if (test_options == -1) {
                pass = 0;
                test_options = 0;
                glutPostRedisplay();
            }
            else if (!test_options) {
                if (is_initiated) delete_World();
                init_World();
                glutPostRedisplay();
            }
            if (!pass) pass = 25;
            else if (pass == 21) pass = 22;
            else pass = 0;
            break;
        case 27:
            if (is_tutorial)
                is_tutorial = 0; 
            test_options = 1;
            glutPostRedisplay();
        //Reset probas = init_stats();
            break;
        case ' ': for (int i = 0; i < patches_per_draw; i++) 
                    patch();
            glutPostRedisplay();
            break;
        case 'k':
            if (is_initiated)
                delete_World();
            glutDestroyWindow(id_window);
            break;
        case 'z': if (!test_options) {
                camera_z --;
                glutPostRedisplay();
            }
            break;
        case 's':
            if (pass == 18) pass = 62;
            else if (pass == 3) {
                test_options = 500;
                pass = 1;
                glutPostRedisplay();
            }
            else if (pass == 15) pass = 13;
            else pass = 0;
            if (!test_options) {
                camera_z ++;
                glutPostRedisplay();
            }
            break;
        case 'c': if (!pass) pass = 5;
            else pass = 0;
            break;
        case 'd': if (pass == 16) pass = 14;
            else pass = 0;
            break;
        case 'e':
            switch (pass) {
                case 7: pass += 12;
                    break;
                case 11: pass = 16;
                    break;
                case 62 : pass = 1;
                    test_options = -1;
                    glutPostRedisplay();
                    break;
                default: pass = 0;
            }
            break;
        case 'h':
            if (!pass) pass = 7;
            else pass = 0;
            break;
        case 'i': if (pass == 12) pass = 18;
            else if (pass == 14) pass = 6;
            else if (pass == 17) pass = 15;
            else pass = 0;
            break;
        case 'l': if (pass == 19) pass = 16;
            else pass = 0;
            break;
        case 'n': if (pass == 22) {
                pass = 2;
                test_options = -1;
                glutPostRedisplay();
            }
            else pass = 0;
            break; 
        case 'o': if (pass == 16) pass = 12;
            else pass = 0;
            break;
        case 'r': if (pass == 5) pass = 11;
            else if (pass == 3) pass = 17;
            else pass = 0;
            break;
        case 't': if (!pass) pass = 3;
            else if (pass == 13) pass = 21;
            break;
    }
}

void MouseManagement(int button, int state, int x, int y)
{
    int xmax = glutGet(GLUT_WINDOW_WIDTH);
    int ymax = glutGet(GLUT_WINDOW_HEIGHT);
    int min = 0;
    if (xmax < ymax)
        min = xmax;
    else min = ymax;
    if ((x - 0.5*xmax)/(0.5*min) >= -1 && (0.5*ymax - y)/(0.5*min) <= 1 && (x-0.5*xmax)/(0.5*min) <= 1 && (0.5*ymax-y)/(0.5*min) >= -1) {
        if (button == GLUT_LEFT_BUTTON) {
            if (state == GLUT_DOWN) {
                switch (test_options) {
                    case 1:
                        if (((x - 0.5 * xmax)/(0.5 * min) > -0.9) && ((x - 0.5 * xmax)/(0.5 * min) < 0.9)) {
                            if ((0.5 * ymax - y)/(0.5 * min) > 0.667) {
                                test_options = 11;
                                glutPostRedisplay();
                            }
                            else if ((0.5 * ymax - y)/(0.5 * min) > 0.333) {
                                test_options = 21;
                                glutPostRedisplay();
                            }
                            else if ((0.5*ymax - y)/(0.5 * min) > 0) {
                                test_options = 31;
                                glutPostRedisplay();
                            }
                            else if ((0.5*ymax - y)/(0.5 * min) > -0.333) {
                                test_options = 41;
                                glutPostRedisplay();
                            }
                            else if ((0.5 * ymax - y)/(0.5*min) > -0.67) {
                                test_options = 51;
                                glutPostRedisplay();
                            }
                        }
                        break;
                    case 100:
                        if (((x - 0.5 * xmax)/(0.5 * min) > -0.9) && ((x - 0.5 * xmax)/(0.5 * min) < 0.9)) {
                            if ((0.5 * ymax - y)/(0.5 * min) > 0.667) {
                                test_options = 110;
                                glutPostRedisplay();
                            }
                            else if ((0.5 * ymax - y)/(0.5 * min) > 0.333) {
                                test_options = 120;
                                glutPostRedisplay();
                            }
                            else if ((0.5*ymax - y)/(0.5 * min) > 0) {
                                test_options = 130;
                                glutPostRedisplay();
                            }
                            else if ((0.5*ymax - y)/(0.5 * min) > -0.333) {
                                test_options = 140;
                                glutPostRedisplay();
                            }
                            else if ((0.5 * ymax - y)/(0.5*min) > -0.67) {
                                test_options = 150;
                                glutPostRedisplay();
                            }
                            else {
                                test_options = 160;
                                glutPostRedisplay();
                            }
                        }
                        break;
                    case 200: 
                        if (((x - 0.5 * xmax)/(0.5 * min) > -0.9) && ((x - 0.5 * xmax)/(0.5 * min) < 0.9)) {
                            if ((0.5 * ymax - y)/(0.5 * min) > 0.667) {
                                test_options = 210;
                                glutPostRedisplay();
                            }
                            else if ((0.5 * ymax - y)/(0.5 * min) > 0.333) {
                                test_options = 220;
                                glutPostRedisplay();
                            }
                            else if ((0.5*ymax - y)/(0.5 * min) > 0) {
                                test_options = 230;
                                glutPostRedisplay();
                            }
                            else if ((0.5*ymax - y)/(0.5 * min) > -0.333) {
                                test_options = 240;
                                glutPostRedisplay();
                            }
                            else if ((0.5 * ymax - y)/(0.5*min) > -0.67) {
                                test_options = 250;
                                glutPostRedisplay();
                            }
                            else {
                                test_options = 260;
                                glutPostRedisplay();
                            }
                        }
                        break;
                    case 301:
                        if ((x - 0.5*xmax)/(0.5*min) >= -1 && (0.5*ymax - y)/(0.5*min) <= 1) {
                            if ((0.5*ymax - y)/(0.5*min) > 0.6) {
                                if ((x - 0.5*xmax)/(0.5*min) < -0.75) {
                                    red_aggr = 0.968627;
                                    green_aggr = 0.968627;
                                    blue_aggr = 0.968627;
                                    test_options = 0;
                                }
                                else if ((x - 0.5*xmax)/(0.5*min) < -0.5) {
                                    red_aggr = 227./255;
                                    green_aggr = 227./255;
                                    blue_aggr = 227./255;
                                    test_options = 0;
                                }
                                else if ((x - 0.5*xmax)/(0.5*min) < -0.25) {
                                    red_aggr = 208./255;
                                    green_aggr = 208./255;
                                    blue_aggr = 208./255;
                                    test_options = 0;
                                }
                                else if ((x - 0.5*xmax)/(0.5*min) < 0) {
                                    red_aggr = 173./255;
                                    green_aggr = 173./255;
                                    blue_aggr = 173./255;
                                    test_options = 0;
                                }
                                else if ((x - 0.5*xmax)/(0.5*min) < 0.25) {
                                    red_aggr = 153./255;
                                    green_aggr = 153./255;
                                    blue_aggr = 153./255;
                                    test_options = 0;
                                }
                                else if ((x - 0.5*xmax)/(0.5*min) < 0.5) {
                                    red_aggr = 102./255;
                                    green_aggr = 102./255;
                                    blue_aggr = 102./255;
                                    test_options = 0;
                                }
                                else if ((x - 0.5*xmax)/(0.5*min) < 0.75) {
                                    red_aggr = 51./255;
                                    green_aggr = 51./255;
                                    blue_aggr = 51./255;
                                    test_options = 0;
                                }
                                else if ((x - 0.5*xmax)/(0.5*min) < 1) {
                                    red_aggr = 0;
                                    green_aggr = 0;
                                    blue_aggr = 0;
                                    test_options = 0;
                                }
                            }
                            else if ((0.5*ymax - y)/(0.5*min) > 0.2) {
                                if ((x - 0.5*xmax)/(0.5*min) < -0.75) {
                                    red_aggr = 1;
                                    green_aggr = 216./255;
                                    blue_aggr = 52./255;
                                    test_options = 0;
                                }
                                else if ((x - 0.5*xmax)/(0.5*min) < -0.5) {
                                    red_aggr = 1;
                                    green_aggr = 149./255;
                                    blue_aggr = 149./255;
                                    test_options = 0;
                                }
                                else if ((x - 0.5*xmax)/(0.5*min) < -0.25) {
                                    red_aggr = 142./255;
                                    green_aggr = 222./255;
                                    blue_aggr = 153./255;
                                    test_options = 0;
                                }
                                else if ((x - 0.5*xmax)/(0.5*min) < 0) {
                                    red_aggr = 12./255;
                                    green_aggr = 230./255;
                                    blue_aggr = 207./255;
                                    test_options = 0;
                                }
                                else if ((x - 0.5*xmax)/(0.5*min) < 0.25) {
                                    red_aggr = 161./255;
                                    green_aggr = 217./255;
                                    blue_aggr = 237./255;
                                    test_options = 0;
                                }
                                else if ((x - 0.5*xmax)/(0.5*min) < 0.5) {
                                    red_aggr = 121./255;
                                    green_aggr = 134./255;
                                    blue_aggr = 203./255;
                                    test_options = 0;
                                }
                                else if ((x - 0.5*xmax)/(0.5*min) < 0.75) {
                                    red_aggr = 186./255;
                                    green_aggr = 105./255;
                                    blue_aggr = 200./255;
                                    test_options = 0;
                                }
                                else if ((x - 0.5*xmax)/(0.5*min) < 1) {
                                    red_aggr = 1;
                                    green_aggr = 171./255;
                                    blue_aggr = 213./255;
                                    test_options = 0;
                                }
                            }
                            else if ((0.5*ymax - y)/(0.5*min) > -0.2) {
                                if ((x - 0.5*xmax)/(0.5*min) < -0.75) {
                                    red_aggr = 1;
                                    green_aggr = 192./255;
                                    blue_aggr = 9./255;
                                    test_options = 0;
                                }
                                else if ((x - 0.5*xmax)/(0.5*min) < -0.5) {
                                    red_aggr = 1;
                                    green_aggr = 82./255;
                                    blue_aggr = 82./255;
                                    test_options = 0;
                                }
                                else if ((x - 0.5*xmax)/(0.5*min) < -0.25) {
                                    red_aggr = 44./255;
                                    green_aggr = 213./255;
                                    blue_aggr = 81./255;
                                    test_options = 0;
                                }
                                else if ((x - 0.5*xmax)/(0.5*min) < 0) {
                                    red_aggr = 0;
                                    green_aggr = 169./255;
                                    blue_aggr = 157./255;
                                    test_options = 0;
                                }
                                else if ((x - 0.5*xmax)/(0.5*min) < 0.25) {
                                    red_aggr = 5./255;
                                    green_aggr = 168./255;
                                    blue_aggr = 244./255;
                                    test_options = 0;
                                }
                                else if ((x - 0.5*xmax)/(0.5*min) < 0.5) {
                                    red_aggr = 64./255;
                                    green_aggr = 81./255;
                                    blue_aggr = 181./255;
                                    test_options = 0;
                                }
                                else if ((x - 0.5*xmax)/(0.5*min) < 0.75) {
                                    red_aggr = 156./255;
                                    green_aggr = 39./255;
                                    blue_aggr = 176./255;
                                    test_options = 0;
                                }
                                else if ((x - 0.5*xmax)/(0.5*min) < 1) {
                                    red_aggr = 234./255;
                                    green_aggr = 138./255;
                                    blue_aggr = 1;
                                    test_options = 0;
                                }
                            }
                            else if ((0.5*ymax - y)/(0.5*min) > -0.6) {
                                if ((x - 0.5*xmax)/(0.5*min) < -0.75) {
                                    red_aggr = 1;
                                    green_aggr = 159./255;
                                    blue_aggr = 0;
                                    test_options = 0;
                                }
                                else if ((x - 0.5*xmax)/(0.5*min) < -0.5) {
                                    red_aggr = 1;
                                    green_aggr = 60./255;
                                    blue_aggr = 0;
                                    test_options = 0;
                                }
                                else if ((x - 0.5*xmax)/(0.5*min) < -0.25) {
                                    red_aggr = 25./255;
                                    green_aggr = 167./255;
                                    blue_aggr = 25./255;
                                    test_options = 0;
                                }
                                else if ((x - 0.5*xmax)/(0.5*min) < 0) {
                                    red_aggr = 0;
                                    green_aggr = 124./255;
                                    blue_aggr = 116./255;
                                    test_options = 0;
                                }
                                else if ((x - 0.5*xmax)/(0.5*min) < 0.25) {
                                    red_aggr = 2./255;
                                    green_aggr = 136./255;
                                    blue_aggr = 209./255;
                                    test_options = 0;
                                }
                                else if ((x - 0.5*xmax)/(0.5*min) < 0.5) {
                                    red_aggr = 48./255;
                                    green_aggr = 63./255;
                                    blue_aggr = 159./255;
                                    test_options = 0;
                                }
                                else if ((x - 0.5*xmax)/(0.5*min) < 0.75) {
                                    red_aggr = 123./255;
                                    green_aggr = 31./255;
                                    blue_aggr = 162./255;
                                    test_options = 0;
                                }
                                else if ((x - 0.5*xmax)/(0.5*min) < 1) {
                                    red_aggr = 206./255;
                                    green_aggr = 66./255;
                                    blue_aggr = 137./255;
                                    test_options = 0;
                                }
                            }
                            else {
                                if ((x - 0.5*xmax)/(0.5*min) < -0.75) {
                                    red_aggr = 1;
                                    green_aggr = 111./255;
                                    blue_aggr = 0;
                                    test_options = 0;
                                }
                                else if ((x - 0.5*xmax)/(0.5*min) < -0.5) {
                                    red_aggr = 246./255;
                                    green_aggr = 33./255;
                                    blue_aggr = 45./255;
                                    test_options = 0;
                                }
                                else if ((x - 0.5*xmax)/(0.5*min) < -0.25) {
                                    red_aggr = 21./255;
                                    green_aggr = 131./255;
                                    blue_aggr = 28./255;
                                    test_options = 0;
                                }
                                else if ((x - 0.5*xmax)/(0.5*min) < 0) {
                                    red_aggr = 2./255;
                                    green_aggr = 90./255;
                                    blue_aggr = 90./255;
                                    test_options = 0;
                                }
                                else if ((x - 0.5*xmax)/(0.5*min) < 0.25) {
                                    red_aggr = 0;
                                    green_aggr = 87./255;
                                    blue_aggr = 155./255;
                                    test_options = 0;
                                }
                                else if ((x - 0.5*xmax)/(0.5*min) < 0.5) {
                                    red_aggr = 26./255;
                                    green_aggr = 34./255;
                                    blue_aggr = 126./255;
                                    test_options = 0;
                                }
                                else if ((x - 0.5*xmax)/(0.5*min) < 0.75) {
                                    red_aggr = 74./255;
                                    green_aggr = 20./255;
                                    blue_aggr = 140./255;
                                    test_options = 0;
                                }
                                else if ((x - 0.5*xmax)/(0.5*min) < 1) {
                                    red_aggr = 163./255;
                                    green_aggr = 64./255;
                                    blue_aggr = 117./255;
                                    test_options = 0;
                                }
                            }
                        }
                        break;
                    case 302:
                        if ((x - 0.5*xmax)/(0.5*min) >= -1 && (0.5*ymax - y)/(0.5*min) <= 1) {
                            if ((0.5*ymax - y)/(0.5*min) > 0.6) {
                                if ((x - 0.5*xmax)/(0.5*min) < -0.75) {
                                    red_chlam = 0.968627;
                                    green_chlam = 0.968627;
                                    blue_chlam = 0.968627;
                                    test_options = 0;
                                }
                                else if ((x - 0.5*xmax)/(0.5*min) < -0.5) {
                                    red_chlam = 227./255;
                                    green_chlam = 227./255;
                                    blue_chlam = 227./255;
                                    test_options = 0;
                                }
                                else if ((x - 0.5*xmax)/(0.5*min) < -0.25) {
                                    red_chlam = 208./255;
                                    green_chlam = 208./255;
                                    blue_chlam = 208./255;
                                    test_options = 0;
                                }
                                else if ((x - 0.5*xmax)/(0.5*min) < 0) {
                                    red_chlam = 173./255;
                                    green_chlam = 173./255;
                                    blue_chlam = 173./255;
                                    test_options = 0;
                                }
                                else if ((x - 0.5*xmax)/(0.5*min) < 0.25) {
                                    red_chlam = 153./255;
                                    green_chlam = 153./255;
                                    blue_chlam = 153./255;
                                    test_options = 0;
                                }
                                else if ((x - 0.5*xmax)/(0.5*min) < 0.5) {
                                    red_chlam = 102./255;
                                    green_chlam = 102./255;
                                    blue_chlam = 102./255;
                                    test_options = 0;
                                }
                                else if ((x - 0.5*xmax)/(0.5*min) < 0.75) {
                                    red_chlam = 51./255;
                                    green_chlam = 51./255;
                                    blue_chlam = 51./255;
                                    test_options = 0;
                                }
                                else if ((x - 0.5*xmax)/(0.5*min) < 1) {
                                    red_chlam = 0;
                                    green_chlam = 0;
                                    blue_chlam = 0;
                                    test_options = 0;
                                }
                            }
                            else if ((0.5*ymax - y)/(0.5*min) > 0.2) {
                                if ((x - 0.5*xmax)/(0.5*min) < -0.75) {
                                    red_chlam = 1;
                                    green_chlam = 216./255;
                                    blue_chlam = 52./255;
                                    test_options = 0;
                                }
                                else if ((x - 0.5*xmax)/(0.5*min) < -0.5) {
                                    red_chlam = 1;
                                    green_chlam = 149./255;
                                    blue_chlam = 149./255;
                                    test_options = 0;
                                }
                                else if ((x - 0.5*xmax)/(0.5*min) < -0.25) {
                                    red_chlam = 142./255;
                                    green_chlam = 222./255;
                                    blue_chlam = 153./255;
                                    test_options = 0;
                                }
                                else if ((x - 0.5*xmax)/(0.5*min) < 0) {
                                    red_chlam = 12./255;
                                    green_chlam = 230./255;
                                    blue_chlam = 207./255;
                                    test_options = 0;
                                }
                                else if ((x - 0.5*xmax)/(0.5*min) < 0.25) {
                                    red_chlam = 161./255;
                                    green_chlam = 217./255;
                                    blue_chlam = 237./255;
                                    test_options = 0;
                                }
                                else if ((x - 0.5*xmax)/(0.5*min) < 0.5) {
                                    red_chlam = 121./255;
                                    green_chlam = 134./255;
                                    blue_chlam = 203./255;
                                    test_options = 0;
                                }
                                else if ((x - 0.5*xmax)/(0.5*min) < 0.75) {
                                    red_chlam = 186./255;
                                    green_chlam = 105./255;
                                    blue_chlam = 200./255;
                                    test_options = 0;
                                }
                                else if ((x - 0.5*xmax)/(0.5*min) < 1) {
                                    red_chlam = 1;
                                    green_chlam = 171./255;
                                    blue_chlam = 213./255;
                                    test_options = 0;
                                }
                            }
                            else if ((0.5*ymax - y)/(0.5*min) > -0.2) {
                                if ((x - 0.5*xmax)/(0.5*min) < -0.75) {
                                    red_chlam = 1;
                                    green_chlam = 192./255;
                                    blue_chlam = 9./255;
                                    test_options = 0;
                                }
                                else if ((x - 0.5*xmax)/(0.5*min) < -0.5) {
                                    red_chlam = 1;
                                    green_chlam = 82./255;
                                    blue_chlam = 82./255;
                                    test_options = 0;
                                }
                                else if ((x - 0.5*xmax)/(0.5*min) < -0.25) {
                                    red_chlam = 44./255;
                                    green_chlam = 213./255;
                                    blue_chlam = 81./255;
                                    test_options = 0;
                                }
                                else if ((x - 0.5*xmax)/(0.5*min) < 0) {
                                    red_chlam = 0;
                                    green_chlam = 169./255;
                                    blue_chlam = 157./255;
                                    test_options = 0;
                                }
                                else if ((x - 0.5*xmax)/(0.5*min) < 0.25) {
                                    red_chlam = 5./255;
                                    green_chlam = 168./255;
                                    blue_chlam = 244./255;
                                    test_options = 0;
                                }
                                else if ((x - 0.5*xmax)/(0.5*min) < 0.5) {
                                    red_chlam = 64./255;
                                    green_chlam = 81./255;
                                    blue_chlam = 181./255;
                                    test_options = 0;
                                }
                                else if ((x - 0.5*xmax)/(0.5*min) < 0.75) {
                                    red_chlam = 156./255;
                                    green_chlam = 39./255;
                                    blue_chlam = 176./255;
                                    test_options = 0;
                                }
                                else if ((x - 0.5*xmax)/(0.5*min) < 1) {
                                    red_chlam = 234./255;
                                    green_chlam = 138./255;
                                    blue_chlam = 1;
                                    test_options = 0;
                                }
                            }
                            else if ((0.5*ymax - y)/(0.5*min) > -0.6) {
                                if ((x - 0.5*xmax)/(0.5*min) < -0.75) {
                                    red_chlam = 1;
                                    green_chlam = 159./255;
                                    blue_chlam = 0;
                                    test_options = 0;
                                }
                                else if ((x - 0.5*xmax)/(0.5*min) < -0.5) {
                                    red_chlam = 1;
                                    green_chlam = 60./255;
                                    blue_chlam = 0;
                                    test_options = 0;
                                }
                                else if ((x - 0.5*xmax)/(0.5*min) < -0.25) {
                                    red_chlam = 25./255;
                                    green_chlam = 167./255;
                                    blue_chlam = 25./255;
                                    test_options = 0;
                                }
                                else if ((x - 0.5*xmax)/(0.5*min) < 0) {
                                    red_chlam = 0;
                                    green_chlam = 124./255;
                                    blue_chlam = 116./255;
                                    test_options = 0;
                                }
                                else if ((x - 0.5*xmax)/(0.5*min) < 0.25) {
                                    red_chlam = 2./255;
                                    green_chlam = 136./255;
                                    blue_chlam = 209./255;
                                    test_options = 0;
                                }
                                else if ((x - 0.5*xmax)/(0.5*min) < 0.5) {
                                    red_chlam = 48./255;
                                    green_chlam = 63./255;
                                    blue_chlam = 159./255;
                                    test_options = 0;
                                }
                                else if ((x - 0.5*xmax)/(0.5*min) < 0.75) {
                                    red_chlam = 123./255;
                                    green_chlam = 31./255;
                                    blue_chlam = 162./255;
                                    test_options = 0;
                                }
                                else if ((x - 0.5*xmax)/(0.5*min) < 1) {
                                    red_chlam = 206./255;
                                    green_chlam = 66./255;
                                    blue_chlam = 137./255;
                                    test_options = 0;
                                }
                            }
                            else {
                                if ((x - 0.5*xmax)/(0.5*min) < -0.75) {
                                    red_chlam = 1;
                                    green_chlam = 111./255;
                                    blue_chlam = 0;
                                    test_options = 0;
                                }
                                else if ((x - 0.5*xmax)/(0.5*min) < -0.5) {
                                    red_chlam = 246./255;
                                    green_chlam = 33./255;
                                    blue_chlam = 45./255;
                                    test_options = 0;
                                }
                                else if ((x - 0.5*xmax)/(0.5*min) < -0.25) {
                                    red_chlam = 21./255;
                                    green_chlam = 131./255;
                                    blue_chlam = 28./255;
                                    test_options = 0;
                                }
                                else if ((x - 0.5*xmax)/(0.5*min) < 0) {
                                    red_chlam = 2./255;
                                    green_chlam = 90./255;
                                    blue_chlam = 90./255;
                                    test_options = 0;
                                }
                                else if ((x - 0.5*xmax)/(0.5*min) < 0.25) {
                                    red_chlam = 0;
                                    green_chlam = 87./255;
                                    blue_chlam = 155./255;
                                    test_options = 0;
                                }
                                else if ((x - 0.5*xmax)/(0.5*min) < 0.5) {
                                    red_chlam = 26./255;
                                    green_chlam = 34./255;
                                    blue_chlam = 126./255;
                                    test_options = 0;
                                }
                                else if ((x - 0.5*xmax)/(0.5*min) < 0.75) {
                                    red_chlam = 74./255;
                                    green_chlam = 20./255;
                                    blue_chlam = 140./255;
                                    test_options = 0;
                                }
                                else if ((x - 0.5*xmax)/(0.5*min) < 1) {
                                    red_chlam = 163./255;
                                    green_chlam = 64./255;
                                    blue_chlam = 117./255;
                                    test_options = 0;
                                }
                            }
                        }
                        break;
                }
            }
            else if (state == GLUT_UP) {
                if (((x - 0.5 * xmax)/(0.5 * min) > -0.9) && ((x - 0.5 * xmax)/(0.5 * min) < 0.9)) {
                    if ((0.5 * ymax - y)/(0.5 * min) > 0.667) {
                        switch (test_options) {
                            case 11: if (is_initiated) delete_World();
                                glutDestroyWindow(id_window);
                                break;
                            case 110: test_options = 302;
                                glutPostRedisplay();
                                break;
                            case 210: patches_per_draw = 1;
                                test_options = 0;
                                glutPostRedisplay();
                                break;
                            default: test_options = test_options - test_options % 100 + test_options % 10;
                                glutPostRedisplay();
                        }
                    }
                    else if ((0.5 * ymax - y)/(0.5 * min) > 0.333) {
                        switch (test_options) {
                            case 21: if (is_initiated)
                                    delete_World();
                                init_World();
                                is_initiated = 1;
                                test_options = 0;
                                glutPostRedisplay();
                                break;
                            case 120: test_options = 301;
                                glutPostRedisplay();
                                break;
                            case 220: patches_per_draw = 2;
                                test_options = 0;
                                glutPostRedisplay();
                                break;
                            default: test_options = test_options - test_options % 100 + test_options % 10;
                                glutPostRedisplay();
                        }
                    }
                    else if ((0.5 * ymax - y)/(0.5 * min) > 0) {
                        switch (test_options) {
                            case 31: test_options = 100;
                                glutPostRedisplay();
                                break;
                            case 130: //PROBS
                                test_options = 400;
                                glutPostRedisplay();
                                break;
                            case 230: patches_per_draw = 3;
                                test_options = 0;
                                glutPostRedisplay();
                                break;
                            default: test_options = test_options - test_options % 100 + test_options % 10;
                                glutPostRedisplay();
                        }
                    }
                    else if ((0.5 * ymax - y)/(0.5 * min) > -0.333) {
                        switch (test_options) {
                            case 41: is_tutorial = 1;
                                glutPostRedisplay();
                                break;
                            case 140: //Patches per draw
                            test_options = 200;
                                glutPostRedisplay();
                                break;
                            case 240: patches_per_draw = 4;
                                test_options = 0;
                                glutPostRedisplay();
                                break;
                            default: test_options = test_options - test_options % 100 + test_options % 10;
                                glutPostRedisplay();
                        }
                    }
                    else if ((0.5 * ymax - y)/(0.5 * min) > -0.667) {
                        switch (test_options) {
                            case 51: test_options = 0;
                                //Resume
                                glutPostRedisplay();
                                break;
                            case 150: //OPTION 5
                                glutPostRedisplay();
                                break;
                            case 250: patches_per_draw = 5;
                                test_options = 0;
                                glutPostRedisplay();
                                break;
                            default: test_options = test_options - test_options % 100 + test_options % 10;
                                glutPostRedisplay();
                        }
                    }
                    else {
                        switch (test_options) {
                        case 160: test_options = 1;
                            glutPostRedisplay();
                            break;
                        case 260: test_options = 100;
                            glutPostRedisplay();
                            break;
                        default: test_options = test_options - (test_options % 100) + (test_options % 10);
                            glutPostRedisplay();
                        }
                    }
                }
                else {
                    test_options = test_options - (test_options % 10) + (test_options % 100);
                    glutPostRedisplay();
                }
            }
        }
    }
}

void ArrowkeysManagement(int key, int x, int y)
{
    switch (key) {
        case GLUT_KEY_UP:
            if (angle_up_down == 88.5)
                angle_up_down = 91.5;
            else if (angle_up_down == 268.5)
                angle_up_down = 271.5;
            else if (angle_up_down == 358.5)
                angle_up_down = 0;
            else angle_up_down += 1.5;
            break;
        case GLUT_KEY_DOWN:
            if (angle_up_down == 91.5)
                angle_up_down = 88.5;
            else if (angle_up_down == 271.5)
                angle_up_down = 268.5;
            else if (angle_up_down > 0)
                angle_up_down -= 1.5;
            else angle_up_down = 368.5;
            break;
        case GLUT_KEY_RIGHT:
            if (angle_right_left == 358.5)
                angle_right_left = 0;
            else angle_right_left += 1.5;
            break;
        case GLUT_KEY_LEFT:
            if (angle_right_left == 0)
                angle_right_left = 358.5;
            else angle_right_left -= 1.5;
            break;

            //Vecteur où il regarde :   x = cos(angle_up_down * M_PI / 180)*sin(angle_right_left * M_PI / 180); 
            //                          y = sin(angle_up_down * M_PI / 180);
            //                          z = cos(angle_up_down * M_PI / 180) * cos(angle_right_left * M_PI / 180);

            //Side-step Vecteur :   normalize(cross(0,1,0 //AXE Y,  Vect_look //up there, 3 coordinated)) //Vector is normalized 
            //      CAN BE MY MOVE_LEFT_RIGHT_VECTOR

            //UP_DOWN Vecteur might be : 
            //  Vect_look =>            x = sin(angle_up_down * M_PI / 180);
            //                          y = cos(angle_up_down * M_PI / 180) * cos(angle_right_left * M_PI / 180);
            //                          z = cos(angle_up_down * M_PI / 180) * sin(angle_right_left * M_PI / 180);
            // Side-step =>         normalize(cross(1,0,0 //AXE X,  Vect_look //up there)) //Vector is normalized
    }
    camera_x = radius * cos(angle_up_down * M_PI / 180) * sin(angle_right_left * M_PI / 180);
    camera_y = radius * sin(angle_up_down * M_PI / 180);
    camera_z = radius * cos(angle_up_down * M_PI / 180) * cos(angle_right_left * M_PI / 180);
    gluLookAt(camera_x, camera_y, camera_z,      0, 0, 0,       0, 1, 0);
    glutPostRedisplay();
    //CODER LA FONCTION DE DEPLACEMENT
}

void menu_options(int key)
{
    switch (key) {
        case 1:delete_World();
            glutDestroyWindow(id_window);
            break;
        case 2: if(is_initiated)
                delete_World();
            init_World ();
            glutPostRedisplay();
            break;
        case 3:test_options = 1;
            glutPostRedisplay();
            break;
    }
}

void init_menu()
{
/*    int id_change_speed = glutCreateMenu(change_speed);
    glutAddMenuEntry("Manually", 1);
    glutAddMenuEntry("0.5s", 2);
    glutAddMenuEntry("1s", 3);
    glutAddMenuEntry("1.5s", 4);
    glutAddMenuEntry("2s", 5);
*/
    glutCreateMenu(menu_options);
    glutAddMenuEntry("End program", 1);
    glutAddMenuEntry("Start new experiment", 2);
    glutAddMenuEntry("Change parameters", 3);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}