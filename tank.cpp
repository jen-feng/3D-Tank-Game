#include "main.h"

// GLfloat amb[4] = {0.1, 0.1, 0.1, 1};
// GLfloat diff[4] ={0.9, 0.9, 0.9, 1};
// GLfloat spec[4] = {0.5, 0.5, 0.5, 1};
// GLfloat m_ambient[4] = {0.329412f, 0.223529f, 0.027451f, 1.0f};
// GLfloat m_diffuse[4] = {0.5f, 0.5f, 0.0f, 1.0f};
// GLfloat m_specular[4] = {0.60f, 0.60f, 0.50f, 1.0f};
// GLfloat m_shininess = 27.8974f;
// int bullet_id = 0;

Tank::Tank()
{
    light_pos[0] = -20; light_pos[1] = 20; light_pos[2] = 20; light_pos[3] = 1.0;
    amb[0] = 0.1; amb[1] = 0.1; amb[2] = 0.1; amb[3] = 1;
    diff[0] = 0.9; diff[1] = 0.9;diff[2] = 0.9;diff[3] = 1;
    spec[0] = 0.5; spec[0] = 0.5; spec[0] = 0.5; spec[0] = 1;
    m_ambient[0] = 0.329412f; m_ambient[1] = 0.223529f; m_ambient[2] = 0.027451f;  m_ambient[3] = 1.0f;
    m_diffuse[0] = 0.5f; m_diffuse[1] = 0.5f; m_diffuse[2] = 0.0f; m_diffuse[3] = 1.0f;
    m_specular[0] = 0.6f; m_specular[1] = 0.6f; m_specular[2] = 0.5f; m_specular[3] = 1.0f;
    m_shininess = 27.8974f;
    bullet_num = 20;

    light_pos1[0] = 20;
    light_pos1[1] = 20;
    light_pos1[2] = -20;
    light_pos1[3] = 5.0;

    amb1[0] = 1.0f;
    amb1[1] = 1.0f;
    amb1[2] = 1.0f;
    amb1[3] = 1.0f;

    diff1[0] = 0;
    diff1[1] = 0;
    diff1[2] = 0;
    diff1[3] = 1;

    spec1[0] = 1;
    spec1[1] = 1;
    spec1[2] = 1;
    spec1[3] = 1;

    loadObj("14079_WWII_Tank_UK_Cromwell_v1_L2.obj", vertices, uvs, normals);

    pos[0] = 0; pos[1] = 1; pos[2] = 0;

    angle = 0;
    dir[0] = sin(angle * TO_RADIANS) + pos[0];
    dir[1] = 1;
    dir[2] = cos(angle * TO_RADIANS) + pos[2];
}

bool Tank::loadObj(const char *fname,
                   std::vector<std::vector<GLfloat> > &out_vertices,
                   std::vector<std::vector<GLfloat> > &out_uvs,
                   std::vector<std::vector<GLfloat> > &out_normals)
{
    printf("Loading OBJ file %s...\n", fname);
    std::vector<std::vector<GLfloat> > temp_vertices;
    std::vector<std::vector<GLfloat> > temp_uvs;
    std::vector<std::vector<GLfloat> > temp_normals;
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
            // vt.push_back(x);
            // vt.push_back(y);
            // temp_uvs.push_back(vt);
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
                // uvIndices.push_back(uvIndex[0]);
                // uvIndices.push_back(uvIndex[1]);
                // uvIndices.push_back(uvIndex[2]);
                // uvIndices.push_back(uvIndex[3]);
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
    glTranslatef(pos[0], -1, pos[2]);
    glRotatef(angle, 0, 1, 0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);

    glLightfv(GL_LIGHT0 , GL_POSITION, light_pos);
    glLightfv(GL_LIGHT0 , GL_DIFFUSE, diff);
    glLightfv(GL_LIGHT0 , GL_AMBIENT, amb);
    glLightfv(GL_LIGHT0 , GL_SPECULAR, spec);
    glLightfv(GL_LIGHT1 , GL_POSITION, light_pos1);
    glLightfv(GL_LIGHT1 , GL_DIFFUSE, diff1);
    glLightfv(GL_LIGHT1 , GL_AMBIENT, amb1);
    glLightfv(GL_LIGHT1 , GL_SPECULAR, spec1);

    
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
    }

    // glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(std::vector<std::vector<GLfloat>>), &vertices[0], GL_STATIC_DRAW);
    glPopMatrix();
    glDisable(GL_LIGHTING);
}

  
void Tank::move(unsigned char key){

    if(key == 'W'||key == 'w'){

        pos[0] += sin(angle * TO_RADIANS) * 0.2;
        pos[2] += cos(angle * TO_RADIANS) * 0.2;

        dir[0] += sin(angle * TO_RADIANS) * 0.2;
        dir[2] += cos(angle * TO_RADIANS) * 0.2;

    }
    if(key == 'A'||key == 'a'){

        angle++;

        dir[0] = sin(angle * TO_RADIANS) + pos[0];
        dir[2] = cos(angle * TO_RADIANS) + pos[2];
        
    }
    if(key == 'S'||key == 's'){

        pos[0] -= sin(angle * TO_RADIANS) * 0.2;
        pos[2] -= cos(angle * TO_RADIANS) * 0.2;

        dir[0] -= sin(angle * TO_RADIANS) * 0.2;
        dir[2] -= cos(angle * TO_RADIANS) * 0.2;
        
    }
    if(key == 'D'||key == 'd'){

        angle--;

        dir[0] = sin(angle * TO_RADIANS) + pos[0];
        dir[2] = cos(angle * TO_RADIANS) + pos[2];
        
    }

}
void Tank::shoot()
{
    
   
    int size = bullets.size();
    if (size <= bullet_num)
    {
        
        std::vector<GLfloat> bullet;
        bullet.push_back(pos[0]);
        bullet.push_back(pos[2]);
        bullet.push_back(angle);
        bullet.push_back(1);
        bullets.push_back(bullet);
        bullet.clear();
    }
    else
    {
        bullet_id = (bullet_id + 1) % bullet_num;
        bullets[bullet_id][0] = pos[0];
        bullets[bullet_id][1] = pos[2];
        bullets[bullet_id][2] = angle;
        bullets[bullet_id][3] = 1;
    }
} 

void Tank::drawProjectile()
{
    
    for (int i = 0; i < bullets.size(); i++)
    {
        if (fabs(bullets[i][3]) >= 1)
        {
            glPushMatrix();
                glTranslatef(bullets[i][0], 1, bullets[i][1]);
                glColor3f(0.5, 0.5, 0.5);
                glScalef(0.2, 0.2, 0.2);
                glutSolidSphere(1, 10, 10);
            glPopMatrix();
            glutPostRedisplay();
        }
    }
}

void Tank::projectileUpdate()
{
    for (int i = 0; i < bullets.size(); i++)
    {
        bullets[i][0] += sin(bullets[i][2] * TO_RADIANS) * 3;
        bullets[i][1] += cos(bullets[i][2] * TO_RADIANS) * 3;
        float len = sqrt((bullets[i][0] * bullets[i][0]) + (bullets[i][1] * bullets[i][1]));
        if (len > 60)
        {
            bullets[i][3] = 0;
        }
    }
}