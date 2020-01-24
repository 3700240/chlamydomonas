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
int pass = 0;

double tempo = 0;



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
            if (test_options)
                test_options = 0;
            else 
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
//                                test_options = 160;
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
                    case 400:
                        if (((x - 0.5 * xmax)/(0.5 * min) > -0.9) && ((x - 0.5 * xmax)/(0.5 * min) < 0.9)) {
                            if ((0.5 * ymax - y)/(0.5 * min) > 0.667) {
                                test_options = 410;
                                glutPostRedisplay();
                            }
                            else if ((0.5 * ymax - y)/(0.5 * min) > 0.333) {
                                test_options = 420;
                                glutPostRedisplay();
                            }
                            else if ((0.5*ymax - y)/(0.5 * min) > 0) {
                                test_options = 430;
                                glutPostRedisplay();
                            }
                            else if ((0.5*ymax - y)/(0.5 * min) > -0.333) {
                                test_options = 440;
                                glutPostRedisplay();
                            }
                            else if ((0.5 * ymax - y)/(0.5*min) > -0.67) {
                                //test_options = 450;
                                //glutPostRedisplay();
                            }
                            else {
                                //test_options = 460;
                                //glutPostRedisplay();
                            }
                        }
                        break;
                    case 600:
                        if (((x - 0.5 * xmax)/(0.5 * min) > -0.9) && ((x - 0.5 * xmax)/(0.5 * min) < 0.9)) {
                            if ((0.5 * ymax - y)/(0.5 * min) > 0.75)
                                test_options = 610;
                            else if ((0.5 * ymax - y)/(0.5 * min) > 0.5)
                                test_options = 620;
                            else if ((0.5 * ymax - y)/(0.5 * min) > 0.25)
                                test_options = 630;
                            else if ((0.5 * ymax - y)/(0.5 * min) > 0)
                                test_options = 640;
                            else if ((0.5 * ymax - y)/(0.5 * min) > -0.25)
                                test_options = 650;
                            else if ((0.5 * ymax - y)/(0.5 * min) > -0.5)
                                test_options = 660;
                            else if ((0.5 * ymax - y)/(0.5 * min) > -0.75)
                                test_options = 670;
                            else test_options = 680;
                            glutPostRedisplay();
                        }
                        break;
                    case 601:
                        if (((0.5 * ymax - y)/(0.5 * min) > 0.6) && ((0.5 * ymax - y)/(0.5 * min) <= 0.8)) {
                            if (((x - 0.5 * xmax)/(0.5 * min) > -0.6) && ((x - 0.5 * xmax)/(0.5 * min) < -0.4)) {
                                incrementor = 1;
                            }
                            else if (((x - 0.5 * xmax)/(0.5 * min) > -0.1) && ((x - 0.5 * xmax)/(0.5 * min) < 0.1)) {
                                incrementor = 10;
                            }
                            else if (((x - 0.5 * xmax)/(0.5 * min) > 0.4) && ((x - 0.5 * xmax)/(0.5 * min) < 0.6))
                                incrementor = 100;
                        }
                        else if (((0.5 * ymax - y)/(0.5 * min) > 0.075) && ((0.5 * ymax - y)/(0.5 * min) <= 0.325)) {
                            if (((x - 0.5 * xmax)/(0.5 * min) > -0.625) && ((x - 0.5 * xmax)/(0.5 * min) < -0.375)) {
                                prob_aggregation_between_cells -= incrementor;
                            }
                            else if (((x - 0.5 * xmax)/(0.5 * min) > 0.375) && ((x - 0.5 * xmax)/(0.5 * min) < 0.625))
                                prob_aggregation_between_cells += incrementor;
                        }
                        else if (((0.5 * ymax - y)/(0.5 * min) > -0.5) && ((0.5 * ymax - y)/(0.5 * min) <= -0.3)) {
                            if (((x - 0.5 * xmax)/(0.5 * min) > -0.5) && ((x - 0.5 * xmax)/(0.5 * min) < 0.5)) {
                                //Entrer avec le clavier
                                scanf("%lf", &tempo);
                                tempo *= 10;
                                prob_aggregation_between_cells = (int) tempo;
                            }
                        }

                        else if (((0.5 * ymax - y)/(0.5 * min) > -0.8) && ((0.5 * ymax - y)/(0.5 * min) <= -0.6)) {
                            if (((x - 0.5 * xmax)/(0.5 * min) > -0.2) && ((x - 0.5 * xmax)/(0.5 * min) < 0.2)) {
                                test_options = 400;
                                incrementor = 1;
                            }
                        }
                        if (prob_aggregation_between_cells < 0)
                            prob_aggregation_between_cells = 0;
                        if (prob_aggregation_between_cells > 1000)
                            prob_aggregation_between_cells = 1000;
                        glutPostRedisplay();
                        break;
                    case 602: 
                        if (((0.5 * ymax - y)/(0.5 * min) > 0.6) && ((0.5 * ymax - y)/(0.5 * min) <= 0.8)) {
                            if (((x - 0.5 * xmax)/(0.5 * min) > -0.6) && ((x - 0.5 * xmax)/(0.5 * min) < -0.4)) {
                                incrementor = 1;
                            }
                            else if (((x - 0.5 * xmax)/(0.5 * min) > -0.1) && ((x - 0.5 * xmax)/(0.5 * min) < 0.1)) {
                                incrementor = 10;
                            }
                            else if (((x - 0.5 * xmax)/(0.5 * min) > 0.4) && ((x - 0.5 * xmax)/(0.5 * min) < 0.6))
                                incrementor = 100;
                        }
                        else if (((0.5 * ymax - y)/(0.5 * min) > 0.075) && ((0.5 * ymax - y)/(0.5 * min) <= 0.325)) {
                            if (((x - 0.5 * xmax)/(0.5 * min) > -0.625) && ((x - 0.5 * xmax)/(0.5 * min) < -0.375)) {
                                prob_self_aggregating -= incrementor;
                            }
                            else if (((x - 0.5 * xmax)/(0.5 * min) > 0.375) && ((x - 0.5 * xmax)/(0.5 * min) < 0.625))
                                prob_self_aggregating += incrementor;
                        }
                        else if (((0.5 * ymax - y)/(0.5 * min) > -0.5) && ((0.5 * ymax - y)/(0.5 * min) <= -0.3)) {
                            if (((x - 0.5 * xmax)/(0.5 * min) > -0.5) && ((x - 0.5 * xmax)/(0.5 * min) < 0.5)) {
                                //Entrer avec le clavier
                                scanf("%lf", &tempo);
                                tempo *= 10;
                                prob_self_aggregating = (int) tempo;
                            }
                        }

                        else if (((0.5 * ymax - y)/(0.5 * min) > -0.8) && ((0.5 * ymax - y)/(0.5 * min) <= -0.6)) {
                            if (((x - 0.5 * xmax)/(0.5 * min) > -0.2) && ((x - 0.5 * xmax)/(0.5 * min) < 0.2)) {
                                test_options = 400;
                                incrementor = 1;
                            }
                        }
                        if (prob_self_aggregating < 0)
                            prob_self_aggregating = 0;
                        if (prob_self_aggregating > 1000)
                            prob_self_aggregating = 1000;
                        glutPostRedisplay();
                        break;
                    case 603:
                        if (((0.5 * ymax - y)/(0.5 * min) > 0.6) && ((0.5 * ymax - y)/(0.5 * min) <= 0.8)) {
                            if (((x - 0.5 * xmax)/(0.5 * min) > -0.6) && ((x - 0.5 * xmax)/(0.5 * min) < -0.4)) {
                                incrementor = 1;
                            }
                            else if (((x - 0.5 * xmax)/(0.5 * min) > -0.1) && ((x - 0.5 * xmax)/(0.5 * min) < 0.1))
                                incrementor = 10;
                            else if (((x - 0.5 * xmax)/(0.5 * min) > 0.4) && ((x - 0.5 * xmax)/(0.5 * min) < 0.6))
                                incrementor = 100;
                        }
                        else if (((0.5 * ymax - y)/(0.5 * min) > 0.075) && ((0.5 * ymax - y)/(0.5 * min) <= 0.325)) {
                            if (((x - 0.5 * xmax)/(0.5 * min) > -0.625) && ((x - 0.5 * xmax)/(0.5 * min) < -0.375)) {
                                dimin_prob_clonage -= incrementor;
                            }
                            else if (((x - 0.5 * xmax)/(0.5 * min) > 0.375) && ((x - 0.5 * xmax)/(0.5 * min) < 0.625))
                                dimin_prob_clonage += incrementor;
                        }
                        else if (((0.5 * ymax - y)/(0.5 * min) > -0.5) && ((0.5 * ymax - y)/(0.5 * min) <= -0.3)) {
                            if (((x - 0.5 * xmax)/(0.5 * min) > -0.5) && ((x - 0.5 * xmax)/(0.5 * min) < 0.5)) {
                                //Entrer avec le clavier
                                scanf("%lf", &tempo);
                                tempo *= 10;
                                dimin_prob_clonage = (int) tempo;
                            }
                        }

                        else if (((0.5 * ymax - y)/(0.5 * min) > -0.8) && ((0.5 * ymax - y)/(0.5 * min) <= -0.6)) {
                            if (((x - 0.5 * xmax)/(0.5 * min) > -0.2) && ((x - 0.5 * xmax)/(0.5 * min) < 0.2)) {
                                test_options = 400;
                                incrementor = 1;
                            }
                        }
                        if (dimin_prob_clonage < 0)
                            dimin_prob_clonage = 0;
                        if (dimin_prob_clonage > 1000)
                            dimin_prob_clonage = 1000;
                        glutPostRedisplay();
                        break;
                    case 604:
                        if (((0.5 * ymax - y)/(0.5 * min) > 0.6) && ((0.5 * ymax - y)/(0.5 * min) <= 0.8)) {
                            if (((x - 0.5 * xmax)/(0.5 * min) > -0.6) && ((x - 0.5 * xmax)/(0.5 * min) < -0.4)) {
                                incrementor = 1;
                            }
                            else if (((x - 0.5 * xmax)/(0.5 * min) > -0.1) && ((x - 0.5 * xmax)/(0.5 * min) < 0.1))
                                incrementor = 10;
                            else if (((x - 0.5 * xmax)/(0.5 * min) > 0.4) && ((x - 0.5 * xmax)/(0.5 * min) < 0.6))
                                incrementor = 100;
                        }
                        else if (((0.5 * ymax - y)/(0.5 * min) > 0.075) && ((0.5 * ymax - y)/(0.5 * min) <= 0.325)) {
                            if (((x - 0.5 * xmax)/(0.5 * min) > -0.625) && ((x - 0.5 * xmax)/(0.5 * min) < -0.375)) {
                                prob_init_clonage -= incrementor;
                            }
                            else if (((x - 0.5 * xmax)/(0.5 * min) > 0.375) && ((x - 0.5 * xmax)/(0.5 * min) < 0.625))
                                prob_init_clonage += incrementor;
                        }
                        else if (((0.5 * ymax - y)/(0.5 * min) > -0.5) && ((0.5 * ymax - y)/(0.5 * min) <= -0.3)) {
                            if (((x - 0.5 * xmax)/(0.5 * min) > -0.5) && ((x - 0.5 * xmax)/(0.5 * min) < 0.5)) {
                                //Entrer avec le clavier
                                scanf("%lf", &tempo);
                                tempo *= 10;
                                prob_init_clonage = (int) tempo;
                            }
                        }

                        else if (((0.5 * ymax - y)/(0.5 * min) > -0.8) && ((0.5 * ymax - y)/(0.5 * min) <= -0.6)) {
                            if (((x - 0.5 * xmax)/(0.5 * min) > -0.2) && ((x - 0.5 * xmax)/(0.5 * min) < 0.2)) {
                                test_options = 400;
                                incrementor = 1;
                            }
                        }
                        if (prob_init_clonage < 0)
                            prob_init_clonage = 0;
                        if (prob_init_clonage > 1000)
                            prob_init_clonage = 1000;
                        glutPostRedisplay();
                        break;
                    case 605:
                        if (((0.5 * ymax - y)/(0.5 * min) > 0.6) && ((0.5 * ymax - y)/(0.5 * min) <= 0.8)) {
                            if (((x - 0.5 * xmax)/(0.5 * min) > -0.6) && ((x - 0.5 * xmax)/(0.5 * min) < -0.4)) {
                                incrementor = 1;
                            }
                            else if (((x - 0.5 * xmax)/(0.5 * min) > -0.1) && ((x - 0.5 * xmax)/(0.5 * min) < 0.1))
                                incrementor = 10;
                            else if (((x - 0.5 * xmax)/(0.5 * min) > 0.4) && ((x - 0.5 * xmax)/(0.5 * min) < 0.6))
                                incrementor = 100;
                        }
                        else if (((0.5 * ymax - y)/(0.5 * min) > 0.075) && ((0.5 * ymax - y)/(0.5 * min) <= 0.325)) {
                            if (((x - 0.5 * xmax)/(0.5 * min) > -0.625) && ((x - 0.5 * xmax)/(0.5 * min) < -0.375)) {
                                prob_eat -= incrementor;
                            }
                            else if (((x - 0.5 * xmax)/(0.5 * min) > 0.375) && ((x - 0.5 * xmax)/(0.5 * min) < 0.625))
                                prob_eat += incrementor;
                        }
                        else if (((0.5 * ymax - y)/(0.5 * min) > -0.5) && ((0.5 * ymax - y)/(0.5 * min) <= -0.3)) {
                            if (((x - 0.5 * xmax)/(0.5 * min) > -0.5) && ((x - 0.5 * xmax)/(0.5 * min) < 0.5)) {
                                //Entrer avec le clavier
                                scanf("%lf", &tempo);
                                tempo *= 10;
                                prob_eat = (int) tempo;
                            }
                        }

                        else if (((0.5 * ymax - y)/(0.5 * min) > -0.8) && ((0.5 * ymax - y)/(0.5 * min) <= -0.6)) {
                            if (((x - 0.5 * xmax)/(0.5 * min) > -0.2) && ((x - 0.5 * xmax)/(0.5 * min) < 0.2)) {
                                test_options = 400;
                                incrementor = 1;
                            }
                        }
                        if (prob_eat < 0)
                            prob_eat = 0;
                        if (prob_eat > 1000)
                            prob_eat = 1000;
                        glutPostRedisplay();
                        break;
                    case 606:
                        if (((0.5 * ymax - y)/(0.5 * min) > 0.6) && ((0.5 * ymax - y)/(0.5 * min) <= 0.8)) {
                            if (((x - 0.5 * xmax)/(0.5 * min) > -0.6) && ((x - 0.5 * xmax)/(0.5 * min) < -0.4)) {
                                incrementor = 1;
                            }
                            else if (((x - 0.5 * xmax)/(0.5 * min) > -0.1) && ((x - 0.5 * xmax)/(0.5 * min) < 0.1))
                                incrementor = 10;
                            else if (((x - 0.5 * xmax)/(0.5 * min) > 0.4) && ((x - 0.5 * xmax)/(0.5 * min) < 0.6))
                                incrementor = 100;
                        }
                        else if (((0.5 * ymax - y)/(0.5 * min) > 0.075) && ((0.5 * ymax - y)/(0.5 * min) <= 0.325)) {
                            if (((x - 0.5 * xmax)/(0.5 * min) > -0.625) && ((x - 0.5 * xmax)/(0.5 * min) < -0.375)) {
                                prob_change_direction -= incrementor;
                            }
                            else if (((x - 0.5 * xmax)/(0.5 * min) > 0.375) && ((x - 0.5 * xmax)/(0.5 * min) < 0.625))
                                prob_change_direction += incrementor;
                        }
                        else if (((0.5 * ymax - y)/(0.5 * min) > -0.5) && ((0.5 * ymax - y)/(0.5 * min) <= -0.3)) {
                            if (((x - 0.5 * xmax)/(0.5 * min) > -0.5) && ((x - 0.5 * xmax)/(0.5 * min) < 0.5)) {
                                //Entrer avec le clavier
                                scanf("%lf", &tempo);
                                tempo *= 10;
                                prob_change_direction = (int) tempo;
                            }
                        }

                        else if (((0.5 * ymax - y)/(0.5 * min) > -0.8) && ((0.5 * ymax - y)/(0.5 * min) <= -0.6)) {
                            if (((x - 0.5 * xmax)/(0.5 * min) > -0.2) && ((x - 0.5 * xmax)/(0.5 * min) < 0.2)) {
                                test_options = 400;
                                incrementor = 1;
                            }
                        }
                        if (prob_change_direction < 0)
                            prob_change_direction = 0;
                        if (prob_change_direction > 1000)
                            prob_change_direction = 1000;
                        glutPostRedisplay();
                        break;
                    case 607:
                        if (((0.5 * ymax - y)/(0.5 * min) > 0.6) && ((0.5 * ymax - y)/(0.5 * min) <= 0.8)) {
                            if (((x - 0.5 * xmax)/(0.5 * min) > -0.6) && ((x - 0.5 * xmax)/(0.5 * min) < -0.4)) {
                                incrementor = 1;
                            }
                            else if (((x - 0.5 * xmax)/(0.5 * min) > -0.1) && ((x - 0.5 * xmax)/(0.5 * min) < 0.1))
                                incrementor = 10;
                            else if (((x - 0.5 * xmax)/(0.5 * min) > 0.4) && ((x - 0.5 * xmax)/(0.5 * min) < 0.6))
                                incrementor = 100;
                        }
                        else if (((0.5 * ymax - y)/(0.5 * min) > 0.075) && ((0.5 * ymax - y)/(0.5 * min) <= 0.325)) {
                            if (((x - 0.5 * xmax)/(0.5 * min) > -0.625) && ((x - 0.5 * xmax)/(0.5 * min) < -0.375)) {
                                prob_die -= incrementor;
                            }
                            else if (((x - 0.5 * xmax)/(0.5 * min) > 0.375) && ((x - 0.5 * xmax)/(0.5 * min) < 0.625))
                                prob_die += incrementor;
                        }
                        else if (((0.5 * ymax - y)/(0.5 * min) > -0.5) && ((0.5 * ymax - y)/(0.5 * min) <= -0.3)) {
                            if (((x - 0.5 * xmax)/(0.5 * min) > -0.5) && ((x - 0.5 * xmax)/(0.5 * min) < 0.5)) {
                                //Entrer avec le clavier
                                scanf("%lf", &tempo);
                                tempo *= 10;
                                prob_die = (int) tempo;
                            }
                        }

                        else if (((0.5 * ymax - y)/(0.5 * min) > -0.8) && ((0.5 * ymax - y)/(0.5 * min) <= -0.6)) {
                            if (((x - 0.5 * xmax)/(0.5 * min) > -0.2) && ((x - 0.5 * xmax)/(0.5 * min) < 0.2)) {
                                test_options = 400;
                                incrementor = 1;
                            }
                        }
                        if (prob_die < 0)
                            prob_die = 0;
                        if (prob_die > 1000)
                            prob_die = 1000;
                        glutPostRedisplay();
                        break;
                    case 608:
                        if (((0.5 * ymax - y)/(0.5 * min) > 0.6) && ((0.5 * ymax - y)/(0.5 * min) <= 0.8)) {
                            if (((x - 0.5 * xmax)/(0.5 * min) > -0.6) && ((x - 0.5 * xmax)/(0.5 * min) < -0.4)) {
                                incrementor = 1;
                            }
                            else if (((x - 0.5 * xmax)/(0.5 * min) > -0.1) && ((x - 0.5 * xmax)/(0.5 * min) < 0.1))
                                incrementor = 10;
                            else if (((x - 0.5 * xmax)/(0.5 * min) > 0.4) && ((x - 0.5 * xmax)/(0.5 * min) < 0.6))
                                incrementor = 100;
                        }
                        else if (((0.5 * ymax - y)/(0.5 * min) > 0.075) && ((0.5 * ymax - y)/(0.5 * min) <= 0.325)) {
                            if (((x - 0.5 * xmax)/(0.5 * min) > -0.625) && ((x - 0.5 * xmax)/(0.5 * min) < -0.375)) {
                                prob_disaggregation -= incrementor;
                            }
                            else if (((x - 0.5 * xmax)/(0.5 * min) > 0.375) && ((x - 0.5 * xmax)/(0.5 * min) < 0.625))
                                prob_disaggregation += incrementor;
                        }
                        else if (((0.5 * ymax - y)/(0.5 * min) > -0.5) && ((0.5 * ymax - y)/(0.5 * min) <= -0.3)) {
                            if (((x - 0.5 * xmax)/(0.5 * min) > -0.5) && ((x - 0.5 * xmax)/(0.5 * min) < 0.5)) {
                                //Entrer avec le clavier
                                scanf("%lf", &tempo);
                                tempo *= 10;
                                prob_disaggregation = (int) tempo;
                            }
                        }

                        else if (((0.5 * ymax - y)/(0.5 * min) > -0.8) && ((0.5 * ymax - y)/(0.5 * min) <= -0.6)) {
                            if (((x - 0.5 * xmax)/(0.5 * min) > -0.2) && ((x - 0.5 * xmax)/(0.5 * min) < 0.2)) {
                                test_options = 400;
                                incrementor = 1;
                            }
                        }
                        if (prob_disaggregation < 0)
                            prob_disaggregation = 0;
                        if (prob_disaggregation > 1000)
                            prob_disaggregation = 1000;
                        glutPostRedisplay();
                        break;
                    case 609:
                        if (((0.5 * ymax - y)/(0.5 * min) > 0.6) && ((0.5 * ymax - y)/(0.5 * min) <= 0.8)) {
                            if (((x - 0.5 * xmax)/(0.5 * min) > -0.6) && ((x - 0.5 * xmax)/(0.5 * min) < -0.4)) {
                                incrementor = 1;
                            }
                            else if (((x - 0.5 * xmax)/(0.5 * min) > -0.1) && ((x - 0.5 * xmax)/(0.5 * min) < 0.1))
                                incrementor = 10;
                            else if (((x - 0.5 * xmax)/(0.5 * min) > 0.4) && ((x - 0.5 * xmax)/(0.5 * min) < 0.6))
                                incrementor = 100;
                        }
                        else if (((0.5 * ymax - y)/(0.5 * min) > 0.075) && ((0.5 * ymax - y)/(0.5 * min) <= 0.325)) {
                            if (((x - 0.5 * xmax)/(0.5 * min) > -0.625) && ((x - 0.5 * xmax)/(0.5 * min) < -0.375)) {
                                XMIN -= incrementor;
                            }
                            else if (((x - 0.5 * xmax)/(0.5 * min) > 0.375) && ((x - 0.5 * xmax)/(0.5 * min) < 0.625))
                                XMIN += incrementor;
                        }
                        else if (((0.5 * ymax - y)/(0.5 * min) > -0.5) && ((0.5 * ymax - y)/(0.5 * min) <= -0.3)) {
                            if (((x - 0.5 * xmax)/(0.5 * min) > -0.5) && ((x - 0.5 * xmax)/(0.5 * min) < 0.5)) {
                                //Entrer avec le clavier
                                scanf("%lf", &tempo);
                                tempo *= 10;
                                XMIN = (int) tempo;
                            }
                        }

                        else if (((0.5 * ymax - y)/(0.5 * min) > -0.8) && ((0.5 * ymax - y)/(0.5 * min) <= -0.6)) {
                            if (((x - 0.5 * xmax)/(0.5 * min) > -0.2) && ((x - 0.5 * xmax)/(0.5 * min) < 0.2)) {
                                test_options = 400;
                                incrementor = 1;
                            }
                        }
                        if (XMIN < 0)
                            XMIN = 0;
                        if (XMIN > XMAX)
                            XMIN = XMAX;
                        glutPostRedisplay();
                        break;
                    case 611:
                        if (((0.5 * ymax - y)/(0.5 * min) > 0.6) && ((0.5 * ymax - y)/(0.5 * min) <= 0.8)) {
                            if (((x - 0.5 * xmax)/(0.5 * min) > -0.6) && ((x - 0.5 * xmax)/(0.5 * min) < -0.4)) {
                                incrementor = 1;
                            }
                            else if (((x - 0.5 * xmax)/(0.5 * min) > -0.1) && ((x - 0.5 * xmax)/(0.5 * min) < 0.1))
                                incrementor = 10;
                            else if (((x - 0.5 * xmax)/(0.5 * min) > 0.4) && ((x - 0.5 * xmax)/(0.5 * min) < 0.6))
                                incrementor = 100;
                        }
                        else if (((0.5 * ymax - y)/(0.5 * min) > 0.075) && ((0.5 * ymax - y)/(0.5 * min) <= 0.325)) {
                            if (((x - 0.5 * xmax)/(0.5 * min) > -0.625) && ((x - 0.5 * xmax)/(0.5 * min) < -0.375)) {
                                XMAX -= incrementor;
                            }
                            else if (((x - 0.5 * xmax)/(0.5 * min) > 0.375) && ((x - 0.5 * xmax)/(0.5 * min) < 0.625))
                                XMAX += incrementor;
                        }
                        else if (((0.5 * ymax - y)/(0.5 * min) > -0.5) && ((0.5 * ymax - y)/(0.5 * min) <= -0.3)) {
                            if (((x - 0.5 * xmax)/(0.5 * min) > -0.5) && ((x - 0.5 * xmax)/(0.5 * min) < 0.5)) {
                                //Entrer avec le clavier
                                scanf("%lf", &tempo);
                                tempo *= 10;
                                XMAX = (int) tempo;
                            }
                        }

                        else if (((0.5 * ymax - y)/(0.5 * min) > -0.8) && ((0.5 * ymax - y)/(0.5 * min) <= -0.6)) {
                            if (((x - 0.5 * xmax)/(0.5 * min) > -0.2) && ((x - 0.5 * xmax)/(0.5 * min) < 0.2)) {
                                test_options = 400;
                                incrementor = 1;
                            }
                        }
                        if (XMAX < XMIN)
                            XMAX = XMIN;
                        if (XMAX > 100)
                            XMAX = 100;
                        glutPostRedisplay();
                        break;
                    case 612:
                        if (((0.5 * ymax - y)/(0.5 * min) > 0.6) && ((0.5 * ymax - y)/(0.5 * min) <= 0.8)) {
                            if (((x - 0.5 * xmax)/(0.5 * min) > -0.6) && ((x - 0.5 * xmax)/(0.5 * min) < -0.4)) {
                                incrementor = 1;
                            }
                            else if (((x - 0.5 * xmax)/(0.5 * min) > -0.1) && ((x - 0.5 * xmax)/(0.5 * min) < 0.1))
                                incrementor = 10;
                            else if (((x - 0.5 * xmax)/(0.5 * min) > 0.4) && ((x - 0.5 * xmax)/(0.5 * min) < 0.6))
                                incrementor = 100;
                        }
                        else if (((0.5 * ymax - y)/(0.5 * min) > 0.075) && ((0.5 * ymax - y)/(0.5 * min) <= 0.325)) {
                            if (((x - 0.5 * xmax)/(0.5 * min) > -0.625) && ((x - 0.5 * xmax)/(0.5 * min) < -0.375)) {
                                YMIN -= incrementor;
                            }
                            else if (((x - 0.5 * xmax)/(0.5 * min) > 0.375) && ((x - 0.5 * xmax)/(0.5 * min) < 0.625))
                                YMIN += incrementor;
                        }
                        else if (((0.5 * ymax - y)/(0.5 * min) > -0.5) && ((0.5 * ymax - y)/(0.5 * min) <= -0.3)) {
                            if (((x - 0.5 * xmax)/(0.5 * min) > -0.5) && ((x - 0.5 * xmax)/(0.5 * min) < 0.5)) {
                                //Entrer avec le clavier
                                scanf("%lf", &tempo);
                                tempo *= 10;
                                YMIN = (int) tempo;
                            }
                        }

                        else if (((0.5 * ymax - y)/(0.5 * min) > -0.8) && ((0.5 * ymax - y)/(0.5 * min) <= -0.6)) {
                            if (((x - 0.5 * xmax)/(0.5 * min) > -0.2) && ((x - 0.5 * xmax)/(0.5 * min) < 0.2)) {
                                test_options = 400;
                                incrementor = 1;
                            }
                        }
                        if (YMIN < 0)
                            YMIN = 0;
                        if (YMIN > YMAX)
                            YMIN = YMAX;
                        glutPostRedisplay();
                        break;
                    case 613:
                        if (((0.5 * ymax - y)/(0.5 * min) > 0.6) && ((0.5 * ymax - y)/(0.5 * min) <= 0.8)) {
                            if (((x - 0.5 * xmax)/(0.5 * min) > -0.6) && ((x - 0.5 * xmax)/(0.5 * min) < -0.4)) {
                                incrementor = 1;
                            }
                            else if (((x - 0.5 * xmax)/(0.5 * min) > -0.1) && ((x - 0.5 * xmax)/(0.5 * min) < 0.1))
                                incrementor = 10;
                            else if (((x - 0.5 * xmax)/(0.5 * min) > 0.4) && ((x - 0.5 * xmax)/(0.5 * min) < 0.6))
                                incrementor = 100;
                        }
                        else if (((0.5 * ymax - y)/(0.5 * min) > 0.075) && ((0.5 * ymax - y)/(0.5 * min) <= 0.325)) {
                            if (((x - 0.5 * xmax)/(0.5 * min) > -0.625) && ((x - 0.5 * xmax)/(0.5 * min) < -0.375)) {
                                YMAX -= incrementor;
                            }
                            else if (((x - 0.5 * xmax)/(0.5 * min) > 0.375) && ((x - 0.5 * xmax)/(0.5 * min) < 0.625))
                                YMAX += incrementor;
                        }
                        else if (((0.5 * ymax - y)/(0.5 * min) > -0.5) && ((0.5 * ymax - y)/(0.5 * min) <= -0.3)) {
                            if (((x - 0.5 * xmax)/(0.5 * min) > -0.5) && ((x - 0.5 * xmax)/(0.5 * min) < 0.5)) {
                                //Entrer avec le clavier
                                scanf("%lf", &tempo);
                                tempo *= 10;
                                YMAX = (int) tempo;
                            }
                        }

                        else if (((0.5 * ymax - y)/(0.5 * min) > -0.8) && ((0.5 * ymax - y)/(0.5 * min) <= -0.6)) {
                            if (((x - 0.5 * xmax)/(0.5 * min) > -0.2) && ((x - 0.5 * xmax)/(0.5 * min) < 0.2)) {
                                test_options = 400;
                                incrementor = 1;
                            }
                        }
                        if (YMAX < YMIN)
                            YMAX = YMIN;
                        if (YMAX > 1000)
                            YMAX = 1000;
                        glutPostRedisplay();
                        break;
                    case 614:
                        if (((0.5 * ymax - y)/(0.5 * min) > 0.6) && ((0.5 * ymax - y)/(0.5 * min) <= 0.8)) {
                            if (((x - 0.5 * xmax)/(0.5 * min) > -0.6) && ((x - 0.5 * xmax)/(0.5 * min) < -0.4)) {
                                incrementor = 1;
                            }
                            else if (((x - 0.5 * xmax)/(0.5 * min) > -0.1) && ((x - 0.5 * xmax)/(0.5 * min) < 0.1))
                                incrementor = 10;
                            else if (((x - 0.5 * xmax)/(0.5 * min) > 0.4) && ((x - 0.5 * xmax)/(0.5 * min) < 0.6))
                                incrementor = 100;
                        }
                        else if (((0.5 * ymax - y)/(0.5 * min) > 0.075) && ((0.5 * ymax - y)/(0.5 * min) <= 0.325)) {
                            if (((x - 0.5 * xmax)/(0.5 * min) > -0.625) && ((x - 0.5 * xmax)/(0.5 * min) < -0.375)) {
                                ZMIN -= incrementor;
                            }
                            else if (((x - 0.5 * xmax)/(0.5 * min) > 0.375) && ((x - 0.5 * xmax)/(0.5 * min) < 0.625))
                                ZMIN += incrementor;
                        }
                        else if (((0.5 * ymax - y)/(0.5 * min) > -0.5) && ((0.5 * ymax - y)/(0.5 * min) <= -0.3)) {
                            if (((x - 0.5 * xmax)/(0.5 * min) > -0.5) && ((x - 0.5 * xmax)/(0.5 * min) < 0.5)) {
                                //Entrer avec le clavier
                                scanf("%lf", &tempo);
                                tempo *= 10;
                                ZMIN = (int) tempo;
                            }
                        }

                        else if (((0.5 * ymax - y)/(0.5 * min) > -0.8) && ((0.5 * ymax - y)/(0.5 * min) <= -0.6)) {
                            if (((x - 0.5 * xmax)/(0.5 * min) > -0.2) && ((x - 0.5 * xmax)/(0.5 * min) < 0.2)) {
                                test_options = 400;
                                incrementor = 1;
                            }
                        }
                        if (ZMIN < 0)
                            ZMIN = 0;
                        if (ZMIN > ZMAX)
                            ZMIN = ZMAX;
                        glutPostRedisplay();
                        break;
                    case 615:
                        if (((0.5 * ymax - y)/(0.5 * min) > 0.6) && ((0.5 * ymax - y)/(0.5 * min) <= 0.8)) {
                            if (((x - 0.5 * xmax)/(0.5 * min) > -0.6) && ((x - 0.5 * xmax)/(0.5 * min) < -0.4)) {
                                incrementor = 1;
                            }
                            else if (((x - 0.5 * xmax)/(0.5 * min) > -0.1) && ((x - 0.5 * xmax)/(0.5 * min) < 0.1))
                                incrementor = 10;
                            else if (((x - 0.5 * xmax)/(0.5 * min) > 0.4) && ((x - 0.5 * xmax)/(0.5 * min) < 0.6))
                                incrementor = 100;
                        }
                        else if (((0.5 * ymax - y)/(0.5 * min) > 0.075) && ((0.5 * ymax - y)/(0.5 * min) <= 0.325)) {
                            if (((x - 0.5 * xmax)/(0.5 * min) > -0.625) && ((x - 0.5 * xmax)/(0.5 * min) < -0.375)) {
                                ZMAX -= incrementor;
                            }
                            else if (((x - 0.5 * xmax)/(0.5 * min) > 0.375) && ((x - 0.5 * xmax)/(0.5 * min) < 0.625))
                                ZMAX += incrementor;
                        }
                        else if (((0.5 * ymax - y)/(0.5 * min) > -0.5) && ((0.5 * ymax - y)/(0.5 * min) <= -0.3)) {
                            if (((x - 0.5 * xmax)/(0.5 * min) > -0.5) && ((x - 0.5 * xmax)/(0.5 * min) < 0.5)) {
                                //Entrer avec le clavier
                                scanf("%lf", &tempo);
                                tempo *= 10;
                                ZMAX = (int) tempo;
                            }
                        }

                        else if (((0.5 * ymax - y)/(0.5 * min) > -0.8) && ((0.5 * ymax - y)/(0.5 * min) <= -0.6)) {
                            if (((x - 0.5 * xmax)/(0.5 * min) > -0.2) && ((x - 0.5 * xmax)/(0.5 * min) < 0.2)) {
                                test_options = 400;
                                incrementor = 1;
                            }
                        }
                        if (ZMAX < ZMIN)
                            ZMAX = ZMIN;
                        if (ZMAX > 1000)
                            ZMAX = 1000;
                        glutPostRedisplay();
                        break;
                    case 616:
                        if (((0.5 * ymax - y)/(0.5 * min) > 0.6) && ((0.5 * ymax - y)/(0.5 * min) <= 0.8)) {
                            if (((x - 0.5 * xmax)/(0.5 * min) > -0.6) && ((x - 0.5 * xmax)/(0.5 * min) < -0.4)) {
                                incrementor = 1;
                            }
                            else if (((x - 0.5 * xmax)/(0.5 * min) > -0.1) && ((x - 0.5 * xmax)/(0.5 * min) < 0.1))
                                incrementor = 10;
                            else if (((x - 0.5 * xmax)/(0.5 * min) > 0.4) && ((x - 0.5 * xmax)/(0.5 * min) < 0.6))
                                incrementor = 100;
                        }
                        else if (((0.5 * ymax - y)/(0.5 * min) > 0.075) && ((0.5 * ymax - y)/(0.5 * min) <= 0.325)) {
                            if (((x - 0.5 * xmax)/(0.5 * min) > -0.625) && ((x - 0.5 * xmax)/(0.5 * min) < -0.375)) {
                                NB_INIT -= incrementor;
                            }
                            else if (((x - 0.5 * xmax)/(0.5 * min) > 0.375) && ((x - 0.5 * xmax)/(0.5 * min) < 0.625))
                                NB_INIT += incrementor;
                        }
                        else if (((0.5 * ymax - y)/(0.5 * min) > -0.5) && ((0.5 * ymax - y)/(0.5 * min) <= -0.3)) {
                            if (((x - 0.5 * xmax)/(0.5 * min) > -0.5) && ((x - 0.5 * xmax)/(0.5 * min) < 0.5)) {
                                //Entrer avec le clavier
                                scanf("%lf", &tempo);
                                tempo *= 10;
                                NB_INIT = (int) tempo;
                            }
                        }

                        else if (((0.5 * ymax - y)/(0.5 * min) > -0.8) && ((0.5 * ymax - y)/(0.5 * min) <= -0.6)) {
                            if (((x - 0.5 * xmax)/(0.5 * min) > -0.2) && ((x - 0.5 * xmax)/(0.5 * min) < 0.2)) {
                                test_options = 400;
                                incrementor = 1;
                            }
                        }
                        if (NB_INIT < 0)
                            NB_INIT = 0;
                        if (NB_INIT > 20000)
                            NB_INIT = 20000;
                        glutPostRedisplay();
                        break;
                    case 617:
                        if (((0.5 * ymax - y)/(0.5 * min) > 0.6) && ((0.5 * ymax - y)/(0.5 * min) <= 0.8)) {
                            if (((x - 0.5 * xmax)/(0.5 * min) > -0.6) && ((x - 0.5 * xmax)/(0.5 * min) < -0.4)) {
                                incrementor = 1;
                            }
                            else if (((x - 0.5 * xmax)/(0.5 * min) > -0.1) && ((x - 0.5 * xmax)/(0.5 * min) < 0.1))
                                incrementor = 10;
                            else if (((x - 0.5 * xmax)/(0.5 * min) > 0.4) && ((x - 0.5 * xmax)/(0.5 * min) < 0.6))
                                incrementor = 100;
                        }
                        else if (((0.5 * ymax - y)/(0.5 * min) > 0.075) && ((0.5 * ymax - y)/(0.5 * min) <= 0.325)) {
                            if (((x - 0.5 * xmax)/(0.5 * min) > -0.625) && ((x - 0.5 * xmax)/(0.5 * min) < -0.375)) {
                                FOOD_INIT -= incrementor;
                            }
                            else if (((x - 0.5 * xmax)/(0.5 * min) > 0.375) && ((x - 0.5 * xmax)/(0.5 * min) < 0.625))
                                FOOD_INIT += incrementor;
                        }
                        else if (((0.5 * ymax - y)/(0.5 * min) > -0.5) && ((0.5 * ymax - y)/(0.5 * min) <= -0.3)) {
                            if (((x - 0.5 * xmax)/(0.5 * min) > -0.5) && ((x - 0.5 * xmax)/(0.5 * min) < 0.5)) {
                                //Entrer avec le clavier
                                scanf("%lf", &tempo);
                                tempo *= 10;
                                FOOD_INIT = (int) tempo;
                            }
                        }

                        else if (((0.5 * ymax - y)/(0.5 * min) > -0.8) && ((0.5 * ymax - y)/(0.5 * min) <= -0.6)) {
                            if (((x - 0.5 * xmax)/(0.5 * min) > -0.2) && ((x - 0.5 * xmax)/(0.5 * min) < 0.2)) {
                                test_options = 400;
                                incrementor = 1;
                            }
                        }
                        if (FOOD_INIT < 0)
                            FOOD_INIT = 0;
                        if (FOOD_INIT > 1000)
                            FOOD_INIT = 1000;
                        glutPostRedisplay();
                        break;
                    case 618:
                        if (((0.5 * ymax - y)/(0.5 * min) > 0.6) && ((0.5 * ymax - y)/(0.5 * min) <= 0.8)) {
                            if (((x - 0.5 * xmax)/(0.5 * min) > -0.6) && ((x - 0.5 * xmax)/(0.5 * min) < -0.4)) {
                                incrementor = 1;
                            }
                            else if (((x - 0.5 * xmax)/(0.5 * min) > -0.1) && ((x - 0.5 * xmax)/(0.5 * min) < 0.1))
                                incrementor = 10;
                            else if (((x - 0.5 * xmax)/(0.5 * min) > 0.4) && ((x - 0.5 * xmax)/(0.5 * min) < 0.6))
                                incrementor = 100;
                        }
                        else if (((0.5 * ymax - y)/(0.5 * min) > 0.075) && ((0.5 * ymax - y)/(0.5 * min) <= 0.325)) {
                            if (((x - 0.5 * xmax)/(0.5 * min) > -0.625) && ((x - 0.5 * xmax)/(0.5 * min) < -0.375)) {
                                DIST_AGGREGATE -= incrementor;
                            }
                            else if (((x - 0.5 * xmax)/(0.5 * min) > 0.375) && ((x - 0.5 * xmax)/(0.5 * min) < 0.625))
                                DIST_AGGREGATE += incrementor;
                        }
                        else if (((0.5 * ymax - y)/(0.5 * min) > -0.5) && ((0.5 * ymax - y)/(0.5 * min) <= -0.3)) {
                            if (((x - 0.5 * xmax)/(0.5 * min) > -0.5) && ((x - 0.5 * xmax)/(0.5 * min) < 0.5)) {
                                //Entrer avec le clavier
                                scanf("%lf", &tempo);
                                tempo *= 10;
                                DIST_AGGREGATE = (int) tempo;
                            }
                        }

                        else if (((0.5 * ymax - y)/(0.5 * min) > -0.8) && ((0.5 * ymax - y)/(0.5 * min) <= -0.6)) {
                            if (((x - 0.5 * xmax)/(0.5 * min) > -0.2) && ((x - 0.5 * xmax)/(0.5 * min) < 0.2)) {
                                test_options = 400;
                                incrementor = 1;
                            }
                        }
                        if (DIST_AGGREGATE < 0)
                            DIST_AGGREGATE = 0;
                        if (DIST_AGGREGATE > 10)
                            DIST_AGGREGATE = 10;
                        glutPostRedisplay();
                        break;
                    case 619:
                        if (((0.5 * ymax - y)/(0.5 * min) > 0.6) && ((0.5 * ymax - y)/(0.5 * min) <= 0.8)) {
                            if (((x - 0.5 * xmax)/(0.5 * min) > -0.6) && ((x - 0.5 * xmax)/(0.5 * min) < -0.4)) {
                                incrementor = 1;
                            }
                            else if (((x - 0.5 * xmax)/(0.5 * min) > -0.1) && ((x - 0.5 * xmax)/(0.5 * min) < 0.1))
                                incrementor = 10;
                            else if (((x - 0.5 * xmax)/(0.5 * min) > 0.4) && ((x - 0.5 * xmax)/(0.5 * min) < 0.6))
                                incrementor = 100;
                        }
                        else if (((0.5 * ymax - y)/(0.5 * min) > 0.075) && ((0.5 * ymax - y)/(0.5 * min) <= 0.325)) {
                            if (((x - 0.5 * xmax)/(0.5 * min) > -0.625) && ((x - 0.5 * xmax)/(0.5 * min) < -0.375)) {
                                food_increase -= incrementor;
                            }
                            else if (((x - 0.5 * xmax)/(0.5 * min) > 0.375) && ((x - 0.5 * xmax)/(0.5 * min) < 0.625))
                                food_increase += incrementor;
                        }
                        else if (((0.5 * ymax - y)/(0.5 * min) > -0.5) && ((0.5 * ymax - y)/(0.5 * min) <= -0.3)) {
                            if (((x - 0.5 * xmax)/(0.5 * min) > -0.5) && ((x - 0.5 * xmax)/(0.5 * min) < 0.5)) {
                                //Entrer avec le clavier
                                scanf("%lf", &tempo);
                                tempo *= 10;
                                food_increase = (int) tempo;
                            }
                        }

                        else if (((0.5 * ymax - y)/(0.5 * min) > -0.8) && ((0.5 * ymax - y)/(0.5 * min) <= -0.6)) {
                            if (((x - 0.5 * xmax)/(0.5 * min) > -0.2) && ((x - 0.5 * xmax)/(0.5 * min) < 0.2)) {
                                test_options = 400;
                                incrementor = 1;
                            }
                        }
                        if (food_increase < 0)
                            food_increase = 0;
                        if (food_increase > 1000)
                            food_increase = 1000;
                        glutPostRedisplay();
                        break;
                    case 621:
                        if (((0.5 * ymax - y)/(0.5 * min) > 0.6) && ((0.5 * ymax - y)/(0.5 * min) <= 0.8)) {
                            if (((x - 0.5 * xmax)/(0.5 * min) > -0.6) && ((x - 0.5 * xmax)/(0.5 * min) < -0.4)) {
                                incrementor = 1;
                            }
                            else if (((x - 0.5 * xmax)/(0.5 * min) > -0.1) && ((x - 0.5 * xmax)/(0.5 * min) < 0.1))
                                incrementor = 10;
                            else if (((x - 0.5 * xmax)/(0.5 * min) > 0.4) && ((x - 0.5 * xmax)/(0.5 * min) < 0.6))
                                incrementor = 100;
                        }
                        else if (((0.5 * ymax - y)/(0.5 * min) > 0.075) && ((0.5 * ymax - y)/(0.5 * min) <= 0.325)) {
                            if (((x - 0.5 * xmax)/(0.5 * min) > -0.625) && ((x - 0.5 * xmax)/(0.5 * min) < -0.375)) {
                                food_decrease -= incrementor;
                            }
                            else if (((x - 0.5 * xmax)/(0.5 * min) > 0.375) && ((x - 0.5 * xmax)/(0.5 * min) < 0.625))
                                food_decrease += incrementor;
                        }
                        else if (((0.5 * ymax - y)/(0.5 * min) > -0.5) && ((0.5 * ymax - y)/(0.5 * min) <= -0.3)) {
                            if (((x - 0.5 * xmax)/(0.5 * min) > -0.5) && ((x - 0.5 * xmax)/(0.5 * min) < 0.5)) {
                                //Entrer avec le clavier
                                scanf("%lf", &tempo);
                                tempo *= 10;
                                dimin_prob_clonage = (int) tempo;
                            }
                        }

                        else if (((0.5 * ymax - y)/(0.5 * min) > -0.8) && ((0.5 * ymax - y)/(0.5 * min) <= -0.6)) {
                            if (((x - 0.5 * xmax)/(0.5 * min) > -0.2) && ((x - 0.5 * xmax)/(0.5 * min) < 0.2)) {
                                test_options = 400;
                                incrementor = 1;
                            }
                        }
                        if (food_decrease < 0)
                            food_decrease = 0;
                        if (food_decrease > 1000)
                            food_decrease = 1000;
                        glutPostRedisplay();
                        break;
                    case 700: 
                        if (((x - 0.5 * xmax)/(0.5 * min) > -0.9) && ((x - 0.5 * xmax)/(0.5 * min) < 0.9)) {
                            if ((0.5 * ymax - y)/(0.5 * min) > 0.667) {
                                test_options = 710;
                                glutPostRedisplay();
                            }
                            else if ((0.5 * ymax - y)/(0.5 * min) > 0.333) {
                                test_options = 720;
                                glutPostRedisplay();
                            }
                            else if ((0.5*ymax - y)/(0.5 * min) > 0) {
                                test_options = 730;
                                glutPostRedisplay();
                            }
                            else if ((0.5*ymax - y)/(0.5 * min) > -0.333) {
                                test_options = 740;
                                glutPostRedisplay();
                            }
                            else if ((0.5 * ymax - y)/(0.5*min) > -0.67) {
                                test_options = 750;
                                glutPostRedisplay();
                            }
                            else {
                                test_options = 760;
                                glutPostRedisplay();
                            }
                        }
                        break;
                    case 800:
                        if (((x - 0.5 * xmax)/(0.5 * min) > -0.9) && ((x - 0.5 * xmax)/(0.5 * min) < 0.9)) {
                            if ((0.5 * ymax - y)/(0.5 * min) > 0.667) {
                                test_options = 810;
                                glutPostRedisplay();
                            }
                            else if ((0.5 * ymax - y)/(0.5 * min) > 0.333) {
                                test_options = 820;
                                glutPostRedisplay();
                            }
                            else if ((0.5*ymax - y)/(0.5 * min) > 0) {
                                test_options = 830;
                                glutPostRedisplay();
                            }
                            else if ((0.5*ymax - y)/(0.5 * min) > -0.333) {
                                test_options = 840;
                                glutPostRedisplay();
                            }
                            else if ((0.5 * ymax - y)/(0.5*min) > -0.67) {
                                test_options = 850;
                                glutPostRedisplay();
                            }
                            else {
//                                test_options = 160;
//                                glutPostRedisplay();
                            }
                        }
                        break;
                }
            }
            else if (state == GLUT_UP) {
                if (((x - 0.5 * xmax)/(0.5 * min) > -0.9) && ((x - 0.5 * xmax)/(0.5 * min) < 0.9)) {
                    switch (test_options) {
                        case 11: if ((0.5 * ymax - y)/(0.5 * min) > 0.667) {
                                if (is_initiated)
                                    delete_World();
                            }
                            else test_options = 1;
                            glutDestroyWindow(id_window);
                            break;
                        case 21: if (((0.5 * ymax - y)/(0.5 * min) > 0.333) && ((0.5 * ymax - y)/(0.5 * min) <= 0.667)) {
                                if (is_initiated)
                                    delete_World();
                                init_World();
                                is_initiated = 1;
                                test_options = 0;
                            }
                            else test_options = 1;
                            glutPostRedisplay();
                            break;
                        case 31: if (((0.5 * ymax - y)/(0.5 * min) > 0) && ((0.5 * ymax - y)/(0.5 * min) <= 0.333)) {
                                test_options = 100;
                            }
                            else test_options = 1;
                            glutPostRedisplay();
                            break;
                        case 41: if (((0.5 * ymax - y)/(0.5 * min) > -0.333) && ((0.5 * ymax - y)/(0.5 * min) <= 0)) {
                                is_tutorial = 1;
                            }
                            else test_options = 1;
                            glutPostRedisplay();
                            break;
                        case 51: if (((0.5 * ymax - y)/(0.5 * min) > -0.667) && ((0.5 * ymax - y)/(0.5 * min) <= -0.333)) {
                                test_options = 0;
                                //Resume
                            }
                            else test_options = 1;
                            glutPostRedisplay();
                            break;
                        case 110: if ((0.5 * ymax - y)/(0.5 * min) > 0.667) {
                                test_options = 302;
                            }
                            else test_options = 100;
                            glutPostRedisplay();
                            break;
                        case 120: if (((0.5 * ymax - y)/(0.5 * min) > 0.333) && ((0.5 * ymax - y)/(0.5 * min) <= 0.667)) {
                                test_options = 301;
                            }
                            else test_options = 100;
                            glutPostRedisplay();
                            break;
                        case 130: if (((0.5 * ymax - y)/(0.5 * min) > 0) && ((0.5 * ymax - y)/(0.5 * min) <= 0.333)) {
                                //Probs
                                test_options = 400;
                            }
                            else test_options = 100;
                            glutPostRedisplay();
                            break;
                        case 140: if (((0.5 * ymax - y)/(0.5 * min) > -0.333) && ((0.5 * ymax - y)/(0.5 * min) <= 0)) {
                                //Patches per draw
                                test_options = 200;
                            }
                            else test_options = 100;
                            glutPostRedisplay();
                            break;
                        case 150: if (((0.5 * ymax - y)/(0.5 * min) > -0.667) && ((0.5 * ymax - y)/(0.5 * min) <= -0.333)) {
                                //Resume 
                                test_options = 1;
                            }
                            else test_options = 100;
                            glutPostRedisplay();
                            break;
                        case 160: if ((0.5 * ymax - y)/(0.5 * min) <= -0.667) {
                                test_options = 1;
                            }
                            else test_options = 100;
                            glutPostRedisplay();
                            break;
                        case 210: if ((0.5 * ymax - y)/(0.5 * min) > 0.667) {
                                patches_per_draw = 1;
                                test_options = 0;
                            }
                            else test_options = 200;
                            glutPostRedisplay();
                            break;
                        case 220: if (((0.5 * ymax - y)/(0.5 * min) > 0.333) && ((0.5 * ymax - y)/(0.5 * min) <= 0.667)) {
                                patches_per_draw = 2;
                                test_options = 0;
                            }
                            else test_options = 200;
                            glutPostRedisplay();
                            break;
                        case 230: if (((0.5 * ymax - y)/(0.5 * min) > 0) && ((0.5 * ymax - y)/(0.5 * min) <= 0.333)) {
                                patches_per_draw = 3;
                                test_options = 0;
                            }
                            else test_options = 200;
                            glutPostRedisplay();
                            break;
                        case 240: if (((0.5 * ymax - y)/(0.5 * min) > -0.333) && ((0.5 * ymax - y)/(0.5 * min) <= 0)) {
                                patches_per_draw = 4;
                                test_options = 0;
                            }
                            else test_options = 200;
                            glutPostRedisplay();
                            break;
                        case 250: if (((0.5 * ymax - y)/(0.5 * min) > -0.667) && ((0.5 * ymax - y)/(0.5 * min) <= -0.333)) {
                                patches_per_draw = 5;
                                test_options = 0;
                            }
                            else test_options = 200;
                            glutPostRedisplay();
                            break;
                        case 260: if ((0.5 * ymax - y)/(0.5 * min) <= -0.667) {
                                test_options = 100;
                            }
                            else test_options = 200;
                            glutPostRedisplay();
                            break;
                        case 410: if ((0.5 * ymax - y)/(0.5 * min) > 0.667) {
                                test_options = 600;
                            }
                            else test_options = 400;
                            glutPostRedisplay();
                            break;
                        case 420: if (((0.5 * ymax - y)/(0.5 * min) > 0.333) && ((0.5 * ymax - y)/(0.5 * min) <= 0.667)) {
                                test_options = 700;
                            }
                            else test_options = 400;
                            glutPostRedisplay();
                            break;
                        case 430: if (((0.5 * ymax - y)/(0.5 * min) > 0) && ((0.5 * ymax - y)/(0.5 * min) <= 0.333)) {
                                test_options = 800;
                            }
                            else test_options = 400;
                            glutPostRedisplay();
                            break;
                        case 440: if (((0.5 * ymax - y)/(0.5 * min) > -0.333) && ((0.5 * ymax - y)/(0.5 * min) <= 0)) {
                                //FACTORY RESET;
                            }
                            else test_options = 400;
                            glutPostRedisplay();
                            break;
                        case 450: if (((0.5 * ymax - y)/(0.5 * min) > -0.667) && ((0.5 * ymax - y)/(0.5 * min) <= -0.333)) {
                                test_options = 100;
                            }
                            else test_options = 400;
                            glutPostRedisplay();
                            break;
                        case 610: if ((0.5 * ymax - y)/(0.5 * min) > 0.75) 
                                    test_options = 601;
                            else test_options = 600;
                            glutPostRedisplay();
                            break;
                        case 620 : if (((0.5 * ymax - y)/(0.5 * min) > 0.5) && ((0.5 * ymax - y)/(0.5 * min) <= 0.75))
                                test_options = 602;
                            else test_options = 600;
                            glutPostRedisplay();
                            break;
                        case 630: if (((0.5 * ymax - y)/(0.5 * min) > 0.25) && ((0.5 * ymax - y)/(0.5 * min) <= 0.5))
                                test_options = 603;
                            else test_options = 600;
                            glutPostRedisplay();
                            break;
                        case 640: if (((0.5 * ymax - y)/(0.5 * min) > 0) && ((0.5 * ymax - y)/(0.5 * min) <= 0.25))
                                test_options = 604;
                            else test_options = 600;
                            glutPostRedisplay();
                            break;
                        case 650: if (((0.5 * ymax - y)/(0.5 * min) > -0.25) && ((0.5 * ymax - y)/(0.5 * min) <= 0))
                                test_options = 605;
                            else test_options = 600;
                            glutPostRedisplay();
                            break;
                        case 660: if (((0.5 * ymax - y)/(0.5 * min) > -0.5) && ((0.5 * ymax - y)/(0.5 * min) <= -0.25))
                                test_options = 606;
                            else test_options = 600;
                            glutPostRedisplay();
                            break;
                        case 670: if (((0.5 * ymax - y)/(0.5 * min) > -0.75) && ((0.5 * ymax - y)/(0.5 * min) <= -0.5))
                                test_options = 607;
                            else test_options = 600;
                            glutPostRedisplay();
                            break;
                        case 680: if ((0.5 * ymax - y)/(0.5 * min) <= -0.75)
                                test_options = 608;
                            else test_options = 600;
                            glutPostRedisplay();
                            break;
                        case 710: if ((0.5 * ymax - y)/(0.5 * min) > 0.667) {
                                test_options = 609;
                            }
                            else test_options = 700;
                            glutPostRedisplay();
                            break;
                        case 720: if (((0.5 * ymax - y)/(0.5 * min) > 0.333) && ((0.5 * ymax - y)/(0.5 * min) <= 0.667)) {
                                test_options = 611;
                            }
                            else test_options = 700;
                            glutPostRedisplay();
                            break;
                        case 730: if (((0.5 * ymax - y)/(0.5 * min) > 0) && ((0.5 * ymax - y)/(0.5 * min) <= 0.333)) {
                                test_options = 612;
                            }
                            else test_options = 700;
                            glutPostRedisplay();
                            break;
                        case 740: if (((0.5 * ymax - y)/(0.5 * min) > -0.333) && ((0.5 * ymax - y)/(0.5 * min) <= 0)) {
                                test_options = 613;
                            }
                            else test_options = 700;
                            glutPostRedisplay();
                            break;
                        case 750: if (((0.5 * ymax - y)/(0.5 * min) > -0.667) && ((0.5 * ymax - y)/(0.5 * min) <= -0.333)) {
                                test_options = 614;
                            }
                            else test_options = 700;
                            glutPostRedisplay();
                            break;
                        case 760: if ((0.5 * ymax - y)/(0.5 * min) <= -0.667) {
                                test_options = 615;
                            }
                            else test_options = 700;
                            glutPostRedisplay();
                            break;
                        case 810: if ((0.5 * ymax - y)/(0.5 * min) > 0.667) {
                                test_options = 616;
                            }
                            else test_options = 800;
                            glutPostRedisplay();
                            break;
                        case 820: if (((0.5 * ymax - y)/(0.5 * min) > 0.333) && ((0.5 * ymax - y)/(0.5 * min) <= 0.667)) {
                                test_options = 617;
                            }
                            else test_options = 800;
                            glutPostRedisplay();
                            break;
                        case 830: if (((0.5 * ymax - y)/(0.5 * min) > 0) && ((0.5 * ymax - y)/(0.5 * min) <= 0.333)) {
                                test_options = 618;
                            }
                            else test_options = 800;
                            glutPostRedisplay();
                            break;
                        case 840: if (((0.5 * ymax - y)/(0.5 * min) > -0.333) && ((0.5 * ymax - y)/(0.5 * min) <= 0)) {
                                test_options = 619;
                            }
                            else test_options = 800;
                            glutPostRedisplay();
                            break;
                        case 850: if (((0.5 * ymax - y)/(0.5 * min) > -0.667) && ((0.5 * ymax - y)/(0.5 * min) <= -0.333)) {
                                test_options = 621;
                            }
                            else test_options = 800;
                            glutPostRedisplay();
                            break;
                    }
                }
                else if (test_options)
                    test_options = test_options - test_options % 100 + test_options % 10;
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