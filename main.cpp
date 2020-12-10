#include "main.h"
#include "image.h"
#include "image.cpp"

GLdouble eye[] = {0, 1, 0};
GLdouble lookAt[] = {0, 1, 0};
GLdouble up[] = {0, 1, 0};
float light_pos[2][4] = {
    {-20, 20, 20, 1.0},
    {20, 20, 20, 1.0},
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
Player player = Player();
Enemy enemy = Enemy(0, 0, 10, 90);
world map = world();
Image texture;
const int width = 16 * 80;
const int height = 9 * 80;
const int miniWidth = 300;
const int miniHeight = 300;
GLint mainWindow, subWindow;
unsigned int fbo;

bool move = false;

void minimap();

void init(void)
{

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0, 0, 0, 0);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, 16.0 / 9.0, 0.1, 75);
}

void display()
{
    glutSetWindow(mainWindow);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
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
    gluLookAt(
        player.camPos[0], player.camPos[1], player.camPos[2],
        player.camDir[0], player.camDir[1], player.camDir[2],
        up[0], up[1], up[2]);

    //map.drawWorld();

    enemy.draw();
    //enemy.findPath(map.boundaries);
    player.draw();
    player.drawHUD();
    minimap();
    glFlush();
}

void minimap(){
    glutSetWindow(subWindow);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();


    gluLookAt(
        player.pos[0], 30, player.pos[2],
        player.pos[0], player.pos[1], player.pos[2],
        1, 0, 0);
    

    map.drawWorld();
    enemy.draw();
    player.draw();
}

void timer(int x)
{

    player.projectileUpdate();
    glutPostRedisplay();
    glutTimerFunc(1000 / FPS, timer, 0);
    // player.projectileUpdate();
    // enemy.projectileUpdate();
    // for (int i = 0; i < player.bullets.size(); i++)
    // {
    //     float dx = (enemy.pos[0] + sin(enemy.angle * TO_RADIANS) * 0.5) - (player.bullets[i][0] + sin(player.bullets[i][2] * TO_RADIANS) * 0.5);
    //     float dy = (enemy.pos[2] + cos(enemy.angle * TO_RADIANS) * 0.5) - (player.bullets[i][1] + cos(player.bullets[i][2] * TO_RADIANS) * 0.5);
    //     float dist = sqrt(dx * dx + dy * dy);
    //     if (dist < 1 + 1 && player.bullets[i][3] > 0)
    //     {
    //         player.score += 1;
    //         player.bullets[i][3] = 0;
    //     }
    // }
    // glutPostRedisplay();
    // glutTimerFunc(1000 / FPS, timer, 0);
}
void keyboard_up(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'w':
    case 'W':
        player.movement.Forward = false;
        break;
    case 'a':
    case 'A':
        player.movement.rLeft = false;
        break;
    case 's':
    case 'S':
        player.movement.Backward = false;
        break;
    case 'd':
    case 'D':
        player.movement.rRight = false;
        break;
    }
    player.playerMove();
    glutPostRedisplay();
}

// void collisionCheck(float aabb_min[],float aabb_max[]){
//     float norm[3], len;
//     bool intersect;


//     norm[0] = dir[0] - pos[0];
//     norm[1] = dir[1] - pos[1];
//     norm[2] = dir[2] - pos[2];

//     len = sqrt((norm[0]*norm[0])+(norm[1]*norm[1])+(norm[2]*norm[2]));

//     norm[0] = norm[0]/len;
//     norm[1] = norm[1]/len;
//     norm[2] = norm[2]/len;

//     intersect = intersectCheck(norm,aabb_min,aabb_max);

//     if(intersect)
// }
// bool intersectCheck(float norm[],float aabb_min[],float aabb_max[]){

    
//     float tmin, tmax, tymin, tymax, tzmin, tzmax;
//     bool result;
    
    
//     tmin = (aabb_min[0] - pos[0]) / norm[0]; 
//     tmax = (aabb_max[0] - pos[0]) / norm[0]; 
    
//     if (tmin > tmax){
//         float w=tmin;tmin=tmax;tmax=w;
//     } 

//     tymin = (aabb_min[1] - pos[1]) / norm[1]; 
//     tymax = (aabb_max[1] - pos[1]) / norm[1]; 

//     if (tymin > tymax){
//         float w=tymin;tymin=tymax;tymax=w;
//     }

//     if ((tmin > tymax) || (tymin > tmax)) 
//         return  false; 

//     if (tymin > tmin) 
//         tmin = tymin; 

//     if (tymax < tmax) 
//         tmax = tymax; 

//     tzmin = (aabb_min[2] - pos[2]) / norm[2]; 
//     tzmax = (aabb_max[2] - pos[2]) / norm[2];  

//     if (tzmin > tzmax) {
//         float w=tzmin;tzmin=tzmax;tzmax=w;
//     }

//     if ((tmin > tzmax) || (tzmin > tmax)) 
//         return  false;  

//     if (tzmin > tmin) 
//         tmin = tzmin; 

//     if (tzmax < tmax) 
//         tmax = tzmax; 

//     return  true; 
// }
void keyboard(unsigned char key, int x, int y)
{
    


    switch (key)
    {
    case 'w':
    case 'W':
        player.movement.Forward = true;
        break;
    case 'a':
    case 'A':
        player.movement.rLeft = true;
        break;
    case 's':
    case 'S':
        player.movement.Backward = true;
        break;
    case 'd':
    case 'D':
        player.movement.rRight = true;
        break;
    case 32:
        player.shoot();
        player.collisionCheck(enemy.aabb_min,enemy.aabb_max);
        break;
    case 'r':
    case 'R':
        player.cameraReset();
        break;
    }

    player.playerMove();

    glutPostRedisplay();
}

// bool collisionTest(){

//     for(int i =0; i< map.boundaries.size();i++){

//         float d1x = b->min.x - a->max.x;
//         float d1y = b->min.y - a->max.y;
//         float d2x = a->min.x - b->max.x;
//         float d2y = a->min.y - b->max.y;

//         float d1x = map.boundaries[i][0] - player.boundaries[]
//         float d1z = 
//         float d2x = 
//         float d2z = 

//         if (d1x > 0.0f || d1y > 0.0f)
//             return FALSE;

//         if (d2x > 0.0f || d2y > 0.0f)
//             return FALSE;

//         return TRUE;
//     }

// }
void special(int key, int x, int y)
{
    if (key == GLUT_KEY_RIGHT)
    {
        if (glutGetModifiers() == GLUT_ACTIVE_SHIFT)
            player.tilt += 0.1;
        else
            player.dolly += 0.1;
    }
    if (key == GLUT_KEY_LEFT)
    {
        if (glutGetModifiers() == GLUT_ACTIVE_SHIFT)
            player.tilt -= 0.1;
        else
            player.dolly -= 0.1;
    }
    if (key == GLUT_KEY_UP)
    {
        if (glutGetModifiers() == GLUT_ACTIVE_SHIFT)
            player.boom += 0.1;
        else
            player.truck += 0.1;
    }
    if (key == GLUT_KEY_DOWN)
    {
        if (glutGetModifiers() == GLUT_ACTIVE_SHIFT)
            player.boom -= 0.1;
        else
            player.truck -= 0.1;
    }
    player.updateCamera();
    glutPostRedisplay();
}

void reshape(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, 16.0 / 9.0, 0.1, 75);
    glMatrixMode(GL_MODELVIEW);
}
int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH );

    glutInitWindowPosition(0, 0);
    glutInitWindowSize(width, height);
    mainWindow = glutCreateWindow("Tank Game");
    
    glutDisplayFunc(display);

    glutTimerFunc(1000 / FPS, timer, 0);

    init();
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutKeyboardUpFunc(keyboard_up);
    glutSpecialFunc(special);
    
    
    glutInitWindowPosition((width-miniWidth), (width-miniHeight));
    glutInitWindowSize(miniWidth, miniHeight);
    subWindow = glutCreateWindow("MiniMap");
    
    glutDisplayFunc(minimap);
    glutReshapeFunc(reshape);

    map.texture.texture();
    player.bullets.clear();

    glutMainLoop();
    return (0);
}