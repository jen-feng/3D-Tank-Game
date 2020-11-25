#include "main.h"

GLdouble eye[] = {0, 1, 0};
GLdouble lookAt[] = {0, 1, 0};
GLdouble up[] = {0, 1, 0};
Player player = Player();
Enemy enemy = Enemy(0,-1,10,90);
world map = world();

const int width = 16 * 80;
const int height = 9 * 80;

bool move = false;

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
    gluPerspective(60, 16.0/9.0, 0.1, 75);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(
        player.camPos[0], player.camPos[1], player.camPos[2],
        player.camDir[0], player.camDir[1], player.camDir[2],
        up[0], up[1], up[2]);
    

    map.drawWorld();

    enemy.draw();
    player.draw();
    player.drawHUD();
    

    glFlush();
}

void timer(int x)
{
    player.projectileUpdate();
    if(move)
        enemy.updatePosition();
    glutPostRedisplay();
    glutTimerFunc(1000 / FPS, timer, 0);
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
        break;
    case 'r':
    case 'R':
        player.cameraReset();
        break;
    case 't':
    case 'T':
        move = !move;
        enemy.findPath(-10,10);
        break;
    }
    player.playerMove();
    glutPostRedisplay();
}
void special(int key, int x, int y)
{
    if(key == GLUT_KEY_RIGHT)
    {
        if(glutGetModifiers()== GLUT_ACTIVE_SHIFT)
            player.tilt += 0.01;
        else
            player.dolly += 0.1;
    }
    if(key == GLUT_KEY_LEFT)
    {
        if(glutGetModifiers()== GLUT_ACTIVE_SHIFT)
            player.tilt -= 0.01;
        else
            player.dolly -= 0.1;
    }
    if(key == GLUT_KEY_UP)
    {
        if(glutGetModifiers()== GLUT_ACTIVE_SHIFT)
            player.boom += 0.1;
        else
            player.truck += 0.1;
        
    }
    if(key == GLUT_KEY_DOWN)
    {
        if(glutGetModifiers()== GLUT_ACTIVE_SHIFT)
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
    gluPerspective(60, 16.0/9.0, 0.1, 75);
    glMatrixMode(GL_MODELVIEW);
}
int main(int argc, char **argv)
{

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH);

    glutInitWindowPosition(0, 0);
    glutInitWindowSize(width, height);

    glutCreateWindow("Tank Game");

    glutTimerFunc(1000 / FPS, timer, 0);

    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutKeyboardUpFunc(keyboard_up);
    glutSpecialFunc(special);
    // glutMouseFunc(mouse);
    // glutMotionFunc(motion);
    // glutPassiveMotionFunc(passiveMotion);
    glutMainLoop();
    player.bullets.clear();
    return (0);
}