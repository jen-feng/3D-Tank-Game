#include "main.h"
#include "world.h"
#include "PPM.cc"

bool first = true;

world::world()
{
    m_ambient[0] = 0.1f; m_ambient[1] = 0.1f; m_ambient[2] = 0.05f;  m_ambient[3] = 1.0f;
    m_diffuse[0] = 0.5f; m_diffuse[1] = 0.5f; m_diffuse[2] = 0.5f; m_diffuse[3] = 1.0f;
    m_specular[0] = 0.7f; m_specular[1] = 0.7f; m_specular[2] = 0.7f; m_specular[3] = 1.0f;
    m_shininess = 27.8974f;
    
    size = 50;
    texture.load("wall.ppm");
    loadObj("map2.obj", vertices, uvs, normals);
}

void world::drawWorld()
{
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);

    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, m_ambient);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, m_diffuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, m_specular);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, m_shininess);
    // texture.texture();
    for (int i = 0; i < vertexIndices.size(); i = i + 4)
    {
        
        glBegin(GL_QUADS);
        glTexCoord2f(uvs[i][0], uvs[i][1]);
        glNormal3f(normals[i][0], normals[i][1], normals[i][2]);
        glVertex3f(vertices[i][0], vertices[i][1], vertices[i][2]);
        glTexCoord2f(uvs[i+1][0], uvs[i+1][1]);
        glNormal3f(normals[i + 1][0], normals[i + 1][1], normals[i + 1][2]);
        glVertex3f(vertices[i + 1][0], vertices[i + 1][1], vertices[i + 1][2]);
        glTexCoord2f(uvs[i+2][0], uvs[i+2][1]);
        glNormal3f(normals[i + 2][0], normals[i + 2][1], normals[i + 2][2]);
        glVertex3f(vertices[i + 2][0], vertices[i + 2][1], vertices[i + 2][2]);
        glTexCoord2f(uvs[i+3][0], uvs[i+3][1]);
        glNormal3f(normals[i + 3][0], normals[i + 3][1], normals[i + 3][2]);
        glVertex3f(vertices[i + 3][0], vertices[i + 3][1], vertices[i + 3][2]);
        glEnd();
    }
    glPopMatrix();

}

void world::drawAxis()
{

    glColor3f(1.0, 0.0, 0.0); // red x
    glBegin(GL_LINES);
    // x axis

    glVertex3f(-4.0, 0.0f, 0.0f);
    glVertex3f(4.0, 0.0f, 0.0f);

    // arrow
    glVertex3f(4.0, 0.0f, 0.0f);
    glVertex3f(3.0, 1.0f, 0.0f);

    glVertex3f(4.0, 0.0f, 0.0f);
    glVertex3f(3.0, -1.0f, 0.0f);

    // y
    glColor3f(0.0, 1.0, 0.0); // green y
    glVertex3f(0.0, -4.0f, 0.0f);
    glVertex3f(0.0, 4.0f, 0.0f);

    // arrow
    glVertex3f(0.0, 4.0f, 0.0f);
    glVertex3f(1.0, 3.0f, 0.0f);

    glVertex3f(0.0, 4.0f, 0.0f);
    glVertex3f(-1.0, 3.0f, 0.0f);

    // z
    glColor3f(0.0, 0.0, 1.0); // blue z
    glVertex3f(0.0, 0.0f, -4.0f);
    glVertex3f(0.0, 0.0f, 4.0f);

    // arrow
    glVertex3f(0.0, 0.0f, 4.0f);
    glVertex3f(0.0, 1.0f, 3.0f);

    glVertex3f(0.0, 0.0f, 4.0f);
    glVertex3f(0.0, -1.0f, 3.0f);
    glEnd();
}

bool world::loadObj(const char *fname,
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
    float minX;
    float minZ;
    float maxX;
    float maxZ;
    fp = fopen(fname, "r");
    if (!fp)
    {
        printf("can't open file %s\n", fname);
        exit(1);
    }

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

            if(first){

                minX = x;maxX = x;
                minZ = z;maxZ = z;
                first = false;
            }


            if(x < minX){
                minX = x;
            }
            else if(x > maxX){
                maxX = x;
            }
            if(z < minZ){
                minZ = z;
            }
            else if(z > maxZ){
                maxZ = z;
            }

            

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
        else if(strcmp(lineHeader, "o") == 0)
        {
            first = true;
            std::vector<GLfloat> b;
            b.push_back(minX);b.push_back(minZ);b.push_back(maxX);b.push_back(maxZ);
            boundaries.push_back(b);
        }
    }

    for (unsigned int i = 0; i < vertexIndices.size(); i++)
    {

        // Get the indices of its attributes
        unsigned int vertexIndex = vertexIndices[i];
        unsigned int uvIndex = uvIndices[i];
        unsigned int normalIndex = normalIndices[i];

        // Get the attributes thanks to the index
        std::vector<GLfloat> vertex = temp_vertices[vertexIndex - 1];
        std::vector<GLfloat> uv = temp_uvs[uvIndex - 1];
        std::vector<GLfloat> normal = temp_normals[normalIndex - 1];

        // Put the attributes in buffers
        out_vertices.push_back(vertex);
        out_uvs.push_back(uv);
        out_normals.push_back(normal);
    }
    fclose(fp);
    return true;
}