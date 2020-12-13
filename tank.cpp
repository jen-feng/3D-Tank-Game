#include "main.h"

bool first1 = true;
Tank::Tank()
{
    light_pos[0] = -5; light_pos[1] = 5; light_pos[2] = 5; light_pos[3] = 1.0;
    amb[0] = 0.5; amb[1] = 0.5; amb[2] = 0.5; amb[3] = 1.0;
    diff[0] = 0.9; diff[1] = 0.9;diff[2] = 0.9;diff[3] = 1;
    spec[0] = 0.5; spec[0] = 0.5; spec[0] = 0.5; spec[0] = 1;
    bullet_num = 20;

    light_pos1[0] = 5;
    light_pos1[1] = 5;
    light_pos1[2] = -5;
    light_pos1[3] = 1.0;

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

    Motion movement = {false,false,false,false};

    lives = 3;
    score = 0;


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
    float minX = 10000;
    float minZ = 10000;
    float maxX = -10000;
    float maxZ = -10000;
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
            if(first1){

                minX = x;maxX = x;
                minZ = z;maxZ = z;
                first1 = false;
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
    boundaries.push_back(minX);
    boundaries.push_back(maxX);
    boundaries.push_back(minZ);
    boundaries.push_back(maxZ);
    first1 = false;

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
    
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    //glEnable(GL_LIGHT1);

    glLightfv(GL_LIGHT0 , GL_POSITION, light_pos);
    glLightfv(GL_LIGHT0 , GL_DIFFUSE, diff);
    glLightfv(GL_LIGHT0 , GL_AMBIENT, amb);
    glLightfv(GL_LIGHT0 , GL_SPECULAR, spec);
    // glLightfv(GL_LIGHT1 , GL_POSITION, light_pos1);
    // glLightfv(GL_LIGHT1 , GL_DIFFUSE, diff1);
    // glLightfv(GL_LIGHT1 , GL_AMBIENT, amb1);
    // glLightfv(GL_LIGHT1 , GL_SPECULAR, spec1);

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, m_ambient);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, m_diffuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, m_specular);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, m_shininess);
    glRotatef(-90, 1, 0, 0);
    glRotatef(90, 0, 0, 1);


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
    glDisable(GL_LIGHTING);
    
    
}

  
void Tank::move(){

    prevPos[0] = pos[0];
    prevPos[1] = pos[1];
    prevPos[2] = pos[2];


    if(movement.Forward){
        
        pos[0] += sin(angle * TO_RADIANS) * 0.1;
        pos[2] += cos(angle * TO_RADIANS) * 0.1;

        dir[0] += sin(angle * TO_RADIANS) * 0.1;
        dir[2] += cos(angle * TO_RADIANS) * 0.1;

    }
    if(movement.rLeft){

        angle++;

        dir[0] = sin(angle * TO_RADIANS) + pos[0];
        dir[2] = cos(angle * TO_RADIANS) + pos[2];
    }
    if(movement.Backward){

        pos[0] -= sin(angle * TO_RADIANS) * 0.1;
        pos[2] -= cos(angle * TO_RADIANS) * 0.1;

        dir[0] -= sin(angle * TO_RADIANS) * 0.1;
        dir[2] -= cos(angle * TO_RADIANS) * 0.1;
    }
    if(movement.rRight){

        angle--;

        dir[0] = sin(angle * TO_RADIANS) + pos[0];
        dir[2] = cos(angle * TO_RADIANS) + pos[2];

    }

    printf("pos: %f %f %f\ndir: %f %f %f\n",pos[0],pos[1],pos[2],dir[0],dir[1],dir[2]);

    aabb_min[0] = pos[0] - 1;
    aabb_min[1] = pos[1] - 1;
    aabb_min[2] = pos[2] - 1;

    aabb_max[0] = pos[0] + 1;
    aabb_max[1] = pos[1] + 1;
    aabb_max[2] = pos[2] + 1;

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
                glTranslatef(bullets[i][0], 0.75, bullets[i][1]);
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
        bullets[i][0] += sin(bullets[i][2] * TO_RADIANS) * 0.5;
        bullets[i][1] += cos(bullets[i][2] * TO_RADIANS) * 0.5;
        float len = sqrt((bullets[i][0] * bullets[i][0]) + (bullets[i][1] * bullets[i][1]));
        if (len > 60)
        {
            bullets[i][3] = 0;
        }
    }
}

void Tank::collisionCheck(float aabb_min[],float aabb_max[]){
    float norm[3], len;
    bool intersect;


    norm[0] = dir[0] - pos[0];
    norm[1] = dir[1] - pos[1];
    norm[2] = dir[2] - pos[2];

    len = sqrt((norm[0]*norm[0])+(norm[1]*norm[1])+(norm[2]*norm[2]));

    norm[0] = norm[0]/len;
    norm[1] = norm[1]/len;
    norm[2] = norm[2]/len;

    intersect = intersectCheck(norm,this->aabb_min,this->aabb_max);

    if(intersect){

    }
}
bool Tank::intersectCheck(float norm[],float aabb_min[],float aabb_max[]){

    
    float tmin, tmax, tymin, tymax, tzmin, tzmax;
    bool result;
    
    
    tmin = (this->aabb_min[0] - pos[0]) / norm[0]; 
    tmax = (this->aabb_max[0] - pos[0]) / norm[0]; 
    
    if (tmin > tmax){
        float w=tmin;tmin=tmax;tmax=w;
    } 

    tymin = (this->aabb_min[1] - pos[1]) / norm[1]; 
    tymax = (this->aabb_max[1] - pos[1]) / norm[1]; 

    if (tymin > tymax){
        float w=tymin;tymin=tymax;tymax=w;
    }

    if ((tmin > tymax) || (tymin > tmax)) 
        return  false; 

    if (tymin > tmin) 
        tmin = tymin; 

    if (tymax < tmax) 
        tmax = tymax; 

    tzmin = (this->aabb_min[2] - pos[2]) / norm[2]; 
    tzmax = (this->aabb_max[2] - pos[2]) / norm[2];  

    if (tzmin > tzmax) {
        float w=tzmin;tzmin=tzmax;tzmax=w;
    }

    if ((tmin > tzmax) || (tzmin > tmax)) 
        return  false;  

    if (tzmin > tmin) 
        tmin = tzmin; 

    if (tzmax < tmax) 
        tmax = tzmax; 

    return  true; 
}

Player::Player():Tank(){

    m_ambient[0] = 0.0f; m_ambient[1] = 0.0f; m_ambient[2] = 0.0f;  m_ambient[3] = 1.0f;
    m_diffuse[0] = 0.1f; m_diffuse[1] = 0.35f; m_diffuse[2] = 0.1f; m_diffuse[3] = 1.0f;
    m_specular[0] = 0.45f; m_specular[1] = 0.55f; m_specular[2] = 0.45f; m_specular[3] = 1.0f;
    m_shininess = 32.0f;

    loadObj("14079_WWII_Tank_UK_Cromwell_v1_L2.obj", vertices, uvs, normals);

    pos[0] = -1; pos[1] = 1; pos[2] = 0;

    angle = 0;
    dir[0] = sin(angle * TO_RADIANS) + pos[0];
    dir[1] = 1;
    dir[2] = cos(angle * TO_RADIANS) + pos[2];

    truck = 0.0;
    dolly = 0;
    boom = 0.3;
    tilt = 0;

    updateCamera();

    aabb_min[0] = pos[0] - 1;
    // aabb_min[1] = pos[1] + 1;
    aabb_min[2] = pos[2] - 1;

    aabb_max[0] = pos[0] + 1;
    // aabb_max[1] = pos[1] - 1;
    aabb_max[2] = pos[2] + 1;

    //printf("%f %f\n%f %f\n",pos[0],pos[2], aabb_min[0],aabb_min[2]);
}

void Player::playerMove(){
    move();
    updateCamera();
}

void Player::draw(){
    glDisable(GL_LIGHTING);
    glPopMatrix();
    glPushMatrix();
        glColor3f(0,0,1);
        glTranslatef(aabb_min[0],0,aabb_min[2]);
        glutSolidSphere(0.1,10,10);
    glPopMatrix();
    glPushMatrix();
        glColor3f(1,0,0);
        glTranslatef(aabb_max[0],0,aabb_max[2]);
        glutSolidSphere(0.1,10,10);
    glPopMatrix();
    glEnable(GL_LIGHTING);

    drawProjectile();
    glPushMatrix();
        glTranslatef(pos[0], -1, pos[2]);
        glRotatef(angle, 0, 1, 0);
        drawTank();
    glPopMatrix();
}

void Player::drawHUD(){
    /*  
    HUD:
    Lives
    Points
    Crosshair
    MiniMap?
    */

    int w = glutGet(GLUT_WINDOW_WIDTH);
    int h = glutGet(GLUT_WINDOW_HEIGHT);

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();

    gluOrtho2D(0,w, 0, h);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    //Draw HUD STUFF

    // > +x
    // ^ +y
    
    glBegin(GL_LINES);
        glColor3f(0, 1, 0);
        glScalef(0.2, 0.2, 0.2);
        glVertex2f((w/2)-15,(h/2)-25);
        glVertex2f((w/2)+15,(h/2)-25);
        glVertex2f((w/2),(h/2)-10);
        glVertex2f((w/2),(h/2)-40);
	glEnd();

    glBegin(GL_QUADS);
        glColor3f(0.5, 0.5, 0.5);
        glVertex2f(0,0);
        glVertex2f(160,0);
        glVertex2f(105,105);
        glVertex2f(0,105);

        glColor3f(1, 1, 1);
        glVertex2f(5,5);
        glVertex2f(150,5);
        glVertex2f(100,100);
        glVertex2f(5,100);
	glEnd();
    
    char livesStr[] = "Lives: %d\0";
    char scoreStr[] = "Score: %d\0";

    
    drawText(8,55,livesStr,lives);

    drawText(10,10,scoreStr,score);


    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();


}

void Player::drawText(float x, float y, char *inString, int val){

    char outputStr[50];

    sprintf(outputStr, inString, val);

    glPushMatrix();

    glColor3f(1, 0, 0);
    glTranslatef(x, y, 0);
    glLineWidth(3);
    glScalef(0.2, 0.2, 0.2);

    
    for (char *c = outputStr; *c != '\0'; c++) {
		glutStrokeCharacter(GLUT_STROKE_ROMAN, *c);
	}
    glPopMatrix();
}

void Player::updateCamera(){
    camPos[0] = ((sin(angle * TO_RADIANS) * truck) + pos[0]) + (sin((angle-90) * TO_RADIANS)*dolly);
    camPos[1] = 1 + boom;
    camPos[2] = ((cos(angle * TO_RADIANS) * truck) + pos[2]) + (cos((angle-90) * TO_RADIANS)*dolly);

    camDir[0] = ((sin((angle-90) * TO_RADIANS)*dolly) + dir[0]);
    camDir[1] = (dir[1] + boom) + tilt;
    camDir[2] = ((cos((angle-90) * TO_RADIANS)*dolly) + dir[2]);

    //printf("%f %f %f\n%f %f %f\n",tilt,camPos[1],camPos[2],camDir[0],camDir[1],camDir[2]);
}

void Player::cameraReset(){
    truck = 0.0;
    dolly = 0;
    boom = 0.3;
    tilt = -0.01;

    updateCamera();
}

Enemy::Enemy(float x, float y, float z, float angle):Tank(){

    m_ambient[0] = 0.0f; m_ambient[1] = 0.0f; m_ambient[2] = 0.0f;  m_ambient[3] = 1.0f;
    m_diffuse[0] = 0.5f; m_diffuse[1] = 0.0f; m_diffuse[2] = 0.0f; m_diffuse[3] = 1.0f;
    m_specular[0] = 0.7f; m_specular[1] = 0.6f; m_specular[2] = 0.6f; m_specular[3] = 1.0f;
    m_shininess = 32.0f;

    loadObj("14079_WWII_Tank_UK_Cromwell_v1_L2.obj", vertices, uvs, normals);

    pos[0] = x; pos[1] = y; pos[2] = z;

    this->angle = angle;
    dir[0] = sin(this->angle * TO_RADIANS) + pos[0];
    dir[1] = 1;
    dir[2] = cos(this->angle * TO_RADIANS) + pos[2];

    nextPos[0] = 0; nextPos[1] = 0; nextPos[2] = 0;

    ang = 0;
    dist = 0;

    aabb_min[0] = pos[0] - 1;
    aabb_min[1] = 1;
    aabb_min[2] = pos[2] - 1;

    aabb_max[0] = pos[0] + 1;
    aabb_max[1] = 0;
    aabb_max[2] = pos[2] + 1;

}


void Enemy::findPath(std::vector<std::vector<GLfloat> > boundaries){
    pos[0] += sin(angle * TO_RADIANS)*0.1;
    pos[2] += cos(angle * TO_RADIANS)*0.1;
    for (int i = 0; i < boundaries.size(); i++)
    {
        float dx = (pos[0] + sin(angle * TO_RADIANS) * 0.5) - (boundaries[i][0] + 1);
        float dy = (pos[2] + cos(angle * TO_RADIANS) * 0.5) - (boundaries[i][2] + 1);
        float dist = sqrt(dx * dx + dy * dy);
        float ddx = (pos[0] + sin((angle+90) * TO_RADIANS) * 0.5) - (boundaries[i][0] + 1);
        float ddy = (pos[2] + cos((angle+90) * TO_RADIANS) * 0.5) - (boundaries[i][2] + 1);
        float dist2 = sqrt(ddx * ddx + ddy * ddy);
        float dddx = (pos[0] + sin((angle-90) * TO_RADIANS) * 0.5) - (boundaries[i][0] + 1);
        float dddy = (pos[2] + cos((angle-90) * TO_RADIANS) * 0.5) - (boundaries[i][2] + 1);
        float dist3 = sqrt(dddx * dddx + dddy * dddy);
        int n = rand() % 12;
        int n1 = rand() % 1000;
        if (dist < 1 + 0.8)
        {
            pos[0] -= sin(angle * TO_RADIANS);
            pos[2] -= cos(angle * TO_RADIANS);
            if(n == 0) angle += 90;
            if(n == 2) angle += 180;
            if(n == 3) angle -= 90;
            if(n == 4) angle += 45;
            if(n == 6) angle += 90;
            if(n == 7) angle -= 45;
            if(n == 8) angle += 180;
            if(n == 9) angle -= 90;
            if(n == 10) angle += 45;
            if(n == 1) angle += 90;
            dir[0] = sin(angle * TO_RADIANS) + pos[0];
            dir[2] = cos(angle * TO_RADIANS) + pos[2];
            break;
        }
        if (dist2 > 3 && dist2 < 6 && n1 == 50 || (dist3 > 3 && dist3 < 6 && n1 == 150)) {
            angle += 90;
            dir[0] = sin(angle * TO_RADIANS) + pos[0];
            dir[2] = cos(angle * TO_RADIANS) + pos[2];
            break;
        }
    }
    int n3 = rand() % 100;
    if (n3 == 56 || n3 == 78) shoot();
}

void Enemy::updatePosition(){
    rotate = true;

    if(rotate){
        if(angle > ang){
            movement.rRight = true;
        }
        else
            movement.rLeft = true;
        

        if(ang == angle){
            
            rotate = false;
            movement.rRight = false;
            movement.rLeft = false;
        }
    }
    if(rotate == false){

        if((pos[0] == nextPos[0]) && (pos[2] == nextPos[2])){
            movement.Forward = false;
        }
        else
            movement.Forward = true;

    }

    move();

}

void Enemy::draw(){
    
    glDisable(GL_LIGHTING);
    glPopMatrix();
    glPushMatrix();
        glColor3f(0,0,1);
        glTranslatef(aabb_min[0],aabb_min[1],aabb_min[2]);
        glutSolidSphere(0.5,10,10);
    glPopMatrix();
    glPushMatrix();
        glColor3f(1,0,0);
        glTranslatef(aabb_max[0],aabb_max[1],aabb_max[2]);
        glutSolidSphere(0.5,10,10);
    glPopMatrix();
    glEnable(GL_LIGHTING);
    glPushMatrix();
        glTranslatef(pos[0], -1, pos[2]);
        glRotatef(angle, 0, 1, 0);
        glPushMatrix();
        glTranslatef(0, 5,0);
        glutSolidCube(1);
        glPopMatrix();
        drawTank();
    glPopMatrix();
}