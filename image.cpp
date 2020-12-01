#include "image.h"

void Image::load(char *filename)
{
    mImage = LoadPPM(filename, &mWidth, &mHeight);
};

void Image::draw(unsigned int x, unsigned int y)
{
    glRasterPos2i(x + mWidth, y);
    glPixelZoom(-1, 1);
    glDrawPixels(mWidth, mHeight, GL_RGB, GL_UNSIGNED_BYTE, mImage);
};

void Image::texture()
{
    glGenTextures(1, &text);
    glBindTexture(GL_TEXTURE_2D, text);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, mWidth, mHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, mImage);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
};
