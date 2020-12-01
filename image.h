#ifdef __APPLE__
#  define GL_SILENCE_DEPRECATION
#  include <OpenGL/gl.h>
#  include <OpenGL/glu.h>
#  include <GLUT/glut.h>
#else
#  include <GL/gl.h>
#  include <GL/glu.h>
#  include <GL/glut.h>
#  include <GL/freeglut.h>
#endif

#ifndef IMAGE_H
#define IMAGE_H

#include "PPM.h"
#include <stdio.h>
#include <stdlib.h>


struct Image {
    int mWidth;
    int mHeight;
    int mMax;
    GLubyte * mImage;
    GLuint text;

    void load(char * filename);
    void draw(unsigned int x, unsigned int y);
    void texture();
};

#endif