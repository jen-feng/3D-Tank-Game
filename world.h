
#ifndef WORLD_H
#define WORLD_H

class world
{
public:
    int size;
    GLfloat m_ambient[4];
    GLfloat m_diffuse[4];
    GLfloat m_specular[4];
    GLfloat m_shininess;
    std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
    std::vector<std::vector<GLfloat>> vertices;
    std::vector<std::vector<GLfloat>> uvs;
    std::vector<std::vector<GLfloat>> normals;
    std::vector<char[255]> materials; // Name

    world();
    void drawWorld();
    void drawAxis();
    bool loadObj(const char *fname,
                 std::vector<std::vector<GLfloat>> &out_vertices,
                 std::vector<std::vector<GLfloat>> &out_uvs,
                 std::vector<std::vector<GLfloat>> &out_normals);
};

#endif
