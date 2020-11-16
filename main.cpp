#include "main.h"

GLdouble eye[] = {0, 1.5, 0};
GLdouble lookAt[] = {0, 1.2, 0};
GLdouble up[] = {0, 1, 0};
Tank tank1 = Tank();
Tank tank2 = Tank();
world map = world();

bool mb = false;
int x, y, mx, my;
int size = 50;
float pitch = 0.0, yaw = 0.0;
float camX = 0.0, camZ = 0.0;

const int width = 16 * 50;
const int height = 9 * 50;
float pos[] = {0, 0, 0};
float rot[] = {0, 0, 0};
float angle = 0;

struct Motion
{
    bool Forward, Backward, rLeft, rRight;
};

Motion movement = {false, false};

void init(void)
{
    lookAt[0] = sin(angle * TO_RADIANS) + eye[0];
    lookAt[2] = cos(angle * TO_RADIANS) + eye[2];

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0, 0, 0, 0);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, 16.0 / 9.0, 1, 75);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(
        eye[0], eye[1], eye[2],
        lookAt[0], lookAt[1], lookAt[2],
        up[0], up[1], up[2]);

    map.drawWorld();
    glPushMatrix();
    glTranslatef(eye[0], -1, eye[2]);
    glRotatef(angle, 0, 1, 0);
    tank1.drawTank();
    glPopMatrix();

    tank1.drawProjectile();
    
    glPushMatrix();
    glTranslatef(10, -0.9, 10);
    tank2.drawTank();
    glPopMatrix();


    glFlush();
}

void timer(int x)
{
    tank1.projectileUpdate();
    glutPostRedisplay();
    glutTimerFunc(1000 / FPS, timer, 0);
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'w':
    case 'W':
        eye[0] += sin(angle * TO_RADIANS) * 0.2;
        lookAt[0] += sin(angle * TO_RADIANS) * 0.2;
        eye[2] += cos(angle * TO_RADIANS) * 0.2;
        lookAt[2] += cos(angle * TO_RADIANS) * 0.2;
        break;
    case 'a':
    case 'A':
        angle++;
        lookAt[0] = sin(angle * TO_RADIANS) + eye[0];
        lookAt[2] = cos(angle * TO_RADIANS) + eye[2];
        break;
    case 's':
    case 'S':
        eye[0] -= sin(angle * TO_RADIANS) * 0.2;
        lookAt[0] -= sin(angle * TO_RADIANS) * 0.2;
        eye[2] -= cos(angle * TO_RADIANS) * 0.2;
        lookAt[2] -= cos(angle * TO_RADIANS) * 0.2;
        break;
    case 'd':
    case 'D':
        angle--;
        lookAt[0] = sin(angle * TO_RADIANS) + eye[0];
        lookAt[2] = cos(angle * TO_RADIANS) + eye[2];
        break;

    case 32:

        tank1.shoot(eye[0], eye[2], angle);
        break;
    }
    glutPostRedisplay();
}

void passiveMotion(int x, int y)
{
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
    // glutKeyboardUpFunc(keyboard_up);
    //glutSpecialFunc(special);
    // glutMouseFunc(mouse);
    // glutMotionFunc(motion);
    glutPassiveMotionFunc(passiveMotion);
    glutMainLoop();
    return (0);
}