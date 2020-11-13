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

// class tank{
// public: 

//     float pos[2];
//     int lives;

//     tank();
//     void drawTank();
//     void camera();
//     void shoot();

//     struct Motion
//     {
//         bool Forward,Backward,rLeft,rRight;
//     }movement;

// private:

//     float camX, camZ, yaw;
class Tank
{
public:
    float light_pos[2][4] = {
        {-20, 20, 20, 1.0},
        {20, 20, -20, 5.0},
    };
    float amb[2][4] = {
        {0.1, 0.1, 0.1, 1},
        {1, 1, 1, 1}};
    float diff[2][4] = {
        {0.9, 0.9, 0.9, 1},
        {0, 0, 0, 1}};
    float spec[2][4] = {
        {0.5, 0.5, 0.5, 1},
        {1, 1, 1, 1}};
    GLfloat m_ambient[4] = {0.329412f, 0.223529f, 0.027451f, 1.0f};
    GLfloat m_diffuse[4] = {0.5f, 0.5f, 0.0f, 1.0f};
    GLfloat m_specular[4] = {0.60f, 0.60f, 0.50f, 1.0f};
    GLfloat m_shininess = 27.8974f;
    std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
    std::vector<std::vector<GLfloat>> vertices;
    std::vector<std::vector<GLfloat>> uvs;
    std::vector<std::vector<GLfloat>> normals;
    std::vector<char[255]> materials; // Name

    struct Motion
    {
        bool Forward,Backward,rLeft,rRight;
    }movement;

    Motion direction = {false,false,false,false};

    float pos[3];
    float dir[3];
    float projectile_pos[3];
    float projectile_dir[3];
    int lives;

    Tank();
    void drawTank();
    bool loadObj(const char *fname,
                 std::vector<std::vector<GLfloat>> &out_vertices,
                 std::vector<std::vector<GLfloat>> &out_uvs,
                 std::vector<std::vector<GLfloat>> &out_normals);
    void move();

    void shoot();
    void projectileUpdate();
    void drawProjectile();

};

#endif
