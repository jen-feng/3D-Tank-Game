#ifndef MAIN_H
#define MAIN_H

// #ifdef __APPLE__
// #  include <OpenGL/gl.h>
// #  include <OpenGL/glu.h>
// #  include <GLUT/glut.h>
// #else
// #  include <GL/gl.h>
// #  include <GL/glu.h>
// #  include <GL/freeglut.h>
// #  include <GL/glext.h>
// #endif

#define GL_GLEXT_PROTOTYPES 1
#include <GL/gl.h>
#include <GL/glext.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <GL/freeglut.h>


#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <math.h>
#include <string>
#include "tank.h"
#include "world.h"
#include "image.h"

#define FPS 60
#define TO_RADIANS 3.14159265/180.0
#define TO_DEG 180.0/3.14159265

#endif