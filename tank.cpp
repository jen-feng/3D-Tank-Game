#include "main.h"

Tank::Tank()
{
    loadObj("14079_WWII_Tank_UK_Cromwell_v1_L2.obj", vertices, uvs, normals);
}

bool Tank::loadObj(const char *fname,
                   std::vector<std::vector<GLfloat>> &out_vertices,
                   std::vector<std::vector<GLfloat>> &out_uvs,
                   std::vector<std::vector<GLfloat>> &out_normals)
{
    printf("Loading OBJ file %s...\n", fname);
    std::vector<std::vector<GLfloat>> temp_vertices;
    std::vector<std::vector<GLfloat>> temp_uvs;
    std::vector<std::vector<GLfloat>> temp_normals;
    FILE *fp;
    int read;
    GLfloat x, y, z;
    char ch;
    fp = fopen(fname, "r");
    if (!fp)
    {
        printf("can't open file %s\n", fname);
        exit(1);
    }
    // glNewList(tank, GL_COMPILE);
    // {
    while (1)
    {
        char lineHeader[128];
        read = fscanf(fp, "%s", lineHeader);
        if (read == EOF)
        {
            break;
        }
        if (strcmp(lineHeader, "v") == 0)
        {
            std::vector<GLfloat> v;
            fscanf(fp, "%f %f %f\n", &x, &y, &z);
            v.push_back(x);
            v.push_back(y);
            v.push_back(z);
            temp_vertices.push_back(v);
            v.clear();
        }
        else if (strcmp(lineHeader, "vt") == 0)
        {
            std::vector<GLfloat> vt;
            fscanf(fp, "%f %f\n", &x, &y);
            vt.push_back(x);
            vt.push_back(y);
            temp_uvs.push_back(vt);
        }
        else if (strcmp(lineHeader, "vn") == 0)
        {
            std::vector<GLfloat> vn;
            fscanf(fp, "%f %f %f\n", &x, &y, &z);
            vn.push_back(x);
            vn.push_back(y);
            vn.push_back(z);
            temp_normals.push_back(vn);
        }
        else if (strcmp(lineHeader, "f") == 0)
        {
            std::string vertex1, vertex2, vertex3;
            unsigned int vertexIndex[4], uvIndex[4], normalIndex[4];
            int matches = fscanf(fp, "%d/%d/%d %d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2], &vertexIndex[3], &uvIndex[3], &normalIndex[3]);
            // int matches = fscanf(fp, "%d//%d %d//%d %d//%d\n",&vertexIndex[0], &normalIndex[0],&vertexIndex[1], &normalIndex[1],&vertexIndex[2], &normalIndex[2]);
            if (matches != 12)
            {
                printf("File can't be read by our simple parser : ( Try exporting with other options\n");
                return false;
            }
            else
            {
                vertexIndices.push_back(vertexIndex[0]);
                vertexIndices.push_back(vertexIndex[1]);
                vertexIndices.push_back(vertexIndex[2]);
                vertexIndices.push_back(vertexIndex[3]);
                uvIndices.push_back(uvIndex[0]);
                uvIndices.push_back(uvIndex[1]);
                uvIndices.push_back(uvIndex[2]);
                uvIndices.push_back(uvIndex[3]);
                normalIndices.push_back(normalIndex[0]);
                normalIndices.push_back(normalIndex[1]);
                normalIndices.push_back(normalIndex[2]);
                normalIndices.push_back(normalIndex[3]);
            }
        }
    }
    // glEndList();
    for (unsigned int i = 0; i < vertexIndices.size(); i++)
    {

        // Get the indices of its attributes
        unsigned int vertexIndex = vertexIndices[i];
        // unsigned int uvIndex = uvIndices[i];
        unsigned int normalIndex = normalIndices[i];

        // Get the attributes thanks to the index
        std::vector<GLfloat> vertex = temp_vertices[vertexIndex - 1];
        // std::vector<GLfloat> uv = temp_uvs[uvIndex - 1];
        std::vector<GLfloat> normal = temp_normals[normalIndex - 1];

        // Put the attributes in buffers
        out_vertices.push_back(vertex);
        // out_uvs.push_back(uv);
        out_normals.push_back(normal);
    }
    fclose(fp);
    return true;
}

void Tank::drawTank()
{
    glPushMatrix();
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    for (unsigned int i = 0; i < 2; i++)
    {
        glLightfv(GL_LIGHT0 + i, GL_POSITION, light_pos[i]);
        glLightfv(GL_LIGHT0 + i, GL_DIFFUSE, diff[i]);
        glLightfv(GL_LIGHT0 + i, GL_AMBIENT, amb[i]);
        glLightfv(GL_LIGHT0 + i, GL_SPECULAR, spec[i]);
    }
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, m_ambient);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, m_diffuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, m_specular);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, m_shininess);
    glRotatef(-90, 1, 0, 0);
    glRotatef(90, 0, 0, 1);
    glPushMatrix();
    for (int i = 0; i < vertexIndices.size(); i = i + 4)
    {

        glBegin(GL_QUADS);
        glNormal3f(normals[normalIndices[i] - 1][0], normals[normalIndices[i] - 1][1], normals[normalIndices[i] - 1][2]);
        glVertex3f(vertices[i][0], vertices[i][1], vertices[i][2]);
        glNormal3f(normals[normalIndices[i + 1] - 1][0], normals[normalIndices[i + 1] - 1][1], normals[normalIndices[i + 1] - 1][2]);
        glVertex3f(vertices[i + 1][0], vertices[i + 1][1], vertices[i + 1][2]);
        glNormal3f(normals[normalIndices[i + 2] - 1][0], normals[normalIndices[i + 2] - 1][1], normals[normalIndices[i + 2] - 1][2]);
        glVertex3f(vertices[i + 2][0], vertices[i + 2][1], vertices[i + 2][2]);
        glNormal3f(normals[normalIndices[i + 3] - 1][0], normals[normalIndices[i + 3] - 1][1], normals[normalIndices[i + 3] - 1][2]);
        glVertex3f(vertices[i + 3][0], vertices[i + 3][1], vertices[i + 3][2]);
        glEnd();
        // glBegin(GL_QUADS);
        // glNormal3f(normals[normalIndices[i] - 1][0], normals[normalIndices[i] - 1][1], normals[normalIndices[i] - 1][2]);
        // glVertex3f(vertices[vertexIndices[i] - 1][0], vertices[vertexIndices[i] - 1][1], vertices[vertexIndices[i] - 1][2]);
        // glNormal3f(normals[normalIndices[i + 1] - 1][0], normals[normalIndices[i + 1] - 1][1], normals[normalIndices[i + 1] - 1][2]);
        // glVertex3f(vertices[vertexIndices[i + 1] - 1][0], vertices[vertexIndices[i + 1] - 1][1], vertices[vertexIndices[i + 1] - 1][2]);
        // glNormal3f(normals[normalIndices[i + 2] - 1][0], normals[normalIndices[i + 2] - 1][1], normals[normalIndices[i + 2] - 1][2]);
        // glVertex3f(vertices[vertexIndices[i + 2] - 1][0], vertices[vertexIndices[i + 2] - 1][1], vertices[vertexIndices[i + 2] - 1][2]);
        // glNormal3f(normals[normalIndices[i + 3] - 1][0], normals[normalIndices[i + 3] - 1][1], normals[normalIndices[i + 3] - 1][2]);
        // glVertex3f(vertices[vertexIndices[i + 3] - 1][0], vertices[vertexIndices[i + 3] - 1][1], vertices[vertexIndices[i + 3] - 1][2]);
        // glEnd();
    }

    // glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(std::vector<std::vector<GLfloat>>), &vertices[0], GL_STATIC_DRAW);
    glPopMatrix();
    glPopMatrix();
    glDisable(GL_LIGHTING);
}

void Tank::shoot(GLfloat x, GLfloat z, GLfloat angle)
{

    if (bullets.size() <= bullet_num)
    {
        std::vector<GLfloat> bullet;
        bullet.push_back(x);
        bullet.push_back(z);
        bullet.push_back(angle);
        bullet.push_back(GL_TRUE);
        bullets.push_back(bullet);
    }
    else
    {
        bullet_id = (bullet_id + 1) % bullet_num;
        bullets[bullet_id][0] = x;
        bullets[bullet_id][1] = z;
        bullets[bullet_id][2] = angle;
        bullets[bullet_id][3] = GL_TRUE;
    }
}

void Tank::drawProjectile()
{
    for (int i = 0; i < bullets.size(); i++)
    {
        if (fabs(bullets[i][3]) >= GL_TRUE)
        {
            glPushMatrix();
            glTranslatef(bullets[i][0], 0.3, bullets[i][1]);
            glColor3f(0.5, 0.5, 0.5);
            glScalef(0.2, 0.2, 0.2);
            glutSolidSphere(1, 10, 10);
            glPopMatrix();
        }
    }
}

void Tank::projectileUpdate()
{
    for (int i = 0; i < bullets.size(); i++)
    {
        bullets[i][0] += sin(bullets[i][2] * TO_RADIANS)*3;
        bullets[i][1] += cos(bullets[i][2] * TO_RADIANS)*3;
        float len = sqrt((bullets[i][0] * bullets[i][0]) + (bullets[i][1] * bullets[i][1]));
        if (len > 60)
        {
            bullets[i][3] = GL_FALSE;
        }
    }
}