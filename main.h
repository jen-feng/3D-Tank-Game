#ifndef MAIN_H
#define MAIN_H

#ifdef __APPLE__
#  include <OpenGL/gl.h>
#  include <OpenGL/glu.h>
#  include <GLUT/glut.h>
#else
#  include <GL/gl.h>
#  include <GL/glu.h>
#  include <GL/freeglut.h>
#endif

#include <stdlib.h>
#include <iostream>
#include <math.h>
#include "tank.h"
#include "world.h"


void camera();
void draw();

#endif