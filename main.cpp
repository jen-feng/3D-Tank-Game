#include "main.h"

GLdouble eye[] = {0, 1, 0};
GLdouble lookAt[] = {0, 1, 0};
GLdouble up[] = {0, 1, 0};
Tank tank1 = Tank();
//Tank tank2 = Tank();
world map = world();

bool mb = false;
int x, y, mx, my;

const int width = 16 * 50;
const int height = 9 * 50;

void init(void)
{

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0, 0, 0, 0);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, 16.0 / 9.0, 0, 75);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(
        tank1.camPos[0], tank1.camPos[1], tank1.camPos[2],
        tank1.camDir[0], tank1.camDir[1], tank1.camDir[2],
        up[0], up[1], up[2]);
    

    map.drawWorld();

    tank1.drawProjectile();

    tank1.drawTank();


    // glPushMatrix();
    // glTranslatef(10, -0.9, 10);
    // tank2.drawTank();
    // glPopMatrix();

    glFlush();
}

void timer(int x)
{
    tank1.projectileUpdate();
    glutPostRedisplay();
    glutTimerFunc(1000 / FPS, timer, 0);
}
void keyboard_up(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'w':
    case 'W':
        tank1.movement.Forward = false;
        break;
    case 'a':
    case 'A':
        tank1.movement.rLeft = false;
        break;
    case 's':
    case 'S':
        tank1.movement.Backward = false;
        break;
    case 'd':
    case 'D':
        tank1.movement.rRight = false;
        break;
    }
    tank1.move();
    glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y)
{

    switch (key)
    {
    case 'w':
    case 'W':
        tank1.movement.Forward = true;
        break;
    case 'a':
    case 'A':
        tank1.movement.rLeft = true;
        break;
    case 's':
    case 'S':
        tank1.movement.Backward = true;
        break;
    case 'd':
    case 'D':
        tank1.movement.rRight = true;
        break;
    case 32:
        tank1.shoot();
        break;
    }
    tank1.move();
    glutPostRedisplay();
}
void special(int key, int x, int y)
{
    if(key == GLUT_KEY_RIGHT)
    {
        if(glutGetModifiers()== GLUT_ACTIVE_SHIFT)
            tank1.tilt += 0.1;
        else
            tank1.dolly += 0.1;
    }
    if(key == GLUT_KEY_LEFT)
    {
        if(glutGetModifiers()== GLUT_ACTIVE_SHIFT)
            tank1.tilt -= 0.1;
        else
            tank1.dolly -= 0.1;
    }
    if(key == GLUT_KEY_UP)
    {
        if(glutGetModifiers()== GLUT_ACTIVE_SHIFT)
            tank1.boom += 0.1;
        else
            tank1.truck += 0.1;
        
    }
    if(key == GLUT_KEY_DOWN)
    {
        if(glutGetModifiers()== GLUT_ACTIVE_SHIFT)
            tank1.boom -= 0.1;
        else
            tank1.truck -= 0.1;
        
    }
    tank1.camera();
    glutPostRedisplay();
}

void reshape(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, 16.0 / 9.0, 1, 75);
    glMatrixMode(GL_MODELVIEW);
}
int main(int argc, char **argv)
{

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH);

    glutInitWindowPosition(0, 0);
    glutInitWindowSize(width, height);

    glutCreateWindow("Terrain");

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
    tank1.bullets.clear();
    return (0);
}