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

#define FPS 60
#define TO_RADIANS 3.14159265/180.0

#endif