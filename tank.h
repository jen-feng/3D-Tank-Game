#ifndef TANK_H
#define TANK_H
#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/freeglut.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <string>
#include <iostream>
#include <string.h>

class Tank
{
public:
    GLfloat light_pos[4];
    GLfloat amb[4];
    GLfloat diff[4];
    GLfloat spec[4];
    GLfloat light_pos1[4];
    GLfloat amb1[4];
    GLfloat diff1[4];
    GLfloat spec1[4];
    GLfloat m_ambient[4];
    GLfloat m_diffuse[4];
    GLfloat m_specular[4];
    GLfloat m_shininess;
    std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
    std::vector<std::vector<GLfloat> > vertices;
    std::vector<std::vector<GLfloat> > uvs;
    std::vector<std::vector<GLfloat> > normals;
    std::vector<float> boundaries;

    struct Motion
    {
    bool Forward, Backward, rLeft, rRight;
    }movement;
    
    float pos[3];
    float dir[3];

    float camPos[3];
    float camDir[3];
    float dolly;//left right
    float truck;//forward back
    float boom; //up down
    float tilt; //look up look down

    float angle;

    int lives;
    int score;
    int bullet_num;
    int bullet_id;
    std::vector<std::vector<GLfloat> > bullets;

    Tank();
    void drawTank();
    bool loadObj(const char *fname,
                 std::vector<std::vector<GLfloat> > &out_vertices,
                 std::vector<std::vector<GLfloat> > &out_uvs,
                 std::vector<std::vector<GLfloat> > &out_normals);
    void shoot();
    void move();
    
    void projectileUpdate();
    void drawProjectile();

};

class Player: public Tank
{
    public:

    Player();

    void playerMove();
    void updateCamera();
    void draw();
    void drawHUD();
    void drawText(float x, float y, char *inString, int val);
};

class Enemy: public Tank
{
    public:

    Enemy(float x, float y, float z, float ang);

    void findPath(std::vector<std::vector<GLfloat> > boundaries);
    void updatePosition();

    void draw();

};

#endif
