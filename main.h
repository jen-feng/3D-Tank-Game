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
#include <stdio.h>
#include <iostream>
#include <vector>
#include <math.h>
#include <string>
#include "tank.h"
#include "world.h"

#define FPS 10
#define TO_RADIANS 3.14159265/180.0

void drawProjectile(GLfloat x, GLfloat y);

#endif