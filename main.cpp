#include "main.h"
#include "tank.h"

GLdouble eye[] = {0, 1.5, -1};
GLdouble lookAt[] = {0, 1, 0};
GLdouble up[] = {0, 1, 0};
Tank tank1 = Tank();
#define FPS 60
#define TO_RADIANS 3.14159265 / 180.0

bool mb = false;
int x, y, mx, my;
int size = 50;
float pitch = 0.0, yaw = 0.0;
float camX = 0.0, camZ = 0.0;
int pat = 1;
const int width = 16 * 50;
const int height = 9 * 50;
float pos[] = {0, 0, 0};
float rot[] = {0, 0, 0};
float angle = -135;
struct Motion
{
    bool Forward, Backward, rLeft, rRight;
};

Motion movement = {false, false};

void init(void)
{
    lookAt[0] = sin(angle) + eye[0];
    lookAt[2] = -cos(angle) + eye[2];
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
    draw();
    glTranslatef(0, -1, 0);
    glPushMatrix();
    glTranslatef(lookAt[0], 0, lookAt[2]);

    tank1.drawTank();
    glPopMatrix();

    glFlush();
}
void draw()
{
    for (int x = -25; x < size - 1 / 2.0; x++)
    {
        for (int z = -25; z < size - 1 / 2.0; z++)
        {

            glBegin(GL_QUADS);

            if (pat == 1)
            {
                glColor3f(0, 0, 0);
                glVertex3f(x, 0, z);
                glVertex3f(x, 0, z + 1);
                glVertex3f(x + 1, 0, z + 1);
                glVertex3f(x + 1, 0, z);
                pat = 0;
            }
            else
            {
                glColor3f(1, 1, 1);
                glVertex3f(x, 0, z);
                glVertex3f(x, 0, z + 1);
                glVertex3f(x + 1, 0, z + 1);
                glVertex3f(x + 1, 0, z);
                pat = 1;
            }

            glEnd();
        }
    }
    pat = 1;
}

void camera()
{
    if (movement.Forward)
    {
        camX += cos((yaw + 90 + 180) * TO_RADIANS) / 5.0;
        camZ -= sin((yaw + 90 + 180) * TO_RADIANS) / 5.0;
    }
    if (movement.Backward)
    {
        camX += cos((yaw + 90) * TO_RADIANS) / 5.0;
        camZ -= sin((yaw + 90) * TO_RADIANS) / 5.0;
    }
    if (movement.rLeft)
    {
        yaw++;
    }
    if (movement.rRight)
    {
        yaw--;
    }

    if (yaw > 360)
    {
        yaw = 0;
    }
    if (yaw < 0)
    {
        yaw = 360;
    }
    glRotatef(-yaw, 0, 1, 0);
    glTranslatef(-camX, 0.0, -camZ);
}

void timer(int x)
{

    glutPostRedisplay();
    glutTimerFunc(1000 / FPS, timer, 0);
}
// void keyboard(unsigned char key, int x, int y)
// {
//     bool toggle1 = false, toggle2 = false;

//     switch (key)
//     {
//     case 'w':
//     case 'W':
//         movement.Forward = true;
//         break;
//     case 'a':
//     case 'A':
//         movement.rLeft = true;
//         break;
//     case 's':
//     case 'S':
//         movement.Backward = true;
//         break;
//     case 'd':
//     case 'D':
//         movement.rRight = true;
//         break;
//     }
//     glutPostRedisplay();
// }
void keyboard_up(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'w':
    case 'W':
        movement.Forward = false;
        break;
    case 'a':
    case 'A':
        movement.rLeft = false;
        break;
    case 's':
    case 'S':
        movement.Backward = false;
        break;
    case 'd':
    case 'D':
        movement.rRight = false;
        break;
    }
    glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'w':
    case 'W':
        eye[0] += sin(angle) * 0.1;
        lookAt[0] += sin(angle) * 0.1;
        eye[2] -= cos(angle) * 0.1;
        lookAt[2] -= cos(angle) * 0.1;
        break;
    case 'a':
    case 'A':
        angle -= 0.1;
        lookAt[0] = sin(angle) + eye[0];
        lookAt[2] = -cos(angle) + eye[2];
        break;
    case 's':
    case 'S':
        eye[0] -= sin(angle) * 0.1;
        lookAt[0] -= sin(angle) * 0.1;
        eye[2] += cos(angle) * 0.1;
        lookAt[2] += cos(angle) * 0.1;
        break;
    case 'd':
    case 'D':
        angle += 0.1;
        lookAt[0] = sin(angle) + eye[0];
        lookAt[2] = -cos(angle) + eye[2];
        break;
    }
    glutPostRedisplay();
}

void mouse(int button, int state, int x, int y)
{

    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        mb = true;
    }
    else
    {
        mb = false;
    }
}

void special(int key, int x, int y)
{
    switch (key)
    {

    case GLUT_KEY_LEFT:
        pos[0] -= 0.1;
        rot[1] = -90;
        break;

    case GLUT_KEY_UP:
        pos[2] += 0.1;
        rot[1] = 180;
        break;

    case GLUT_KEY_RIGHT:
        pos[0] += 0.1;
        rot[1] = 90;
        break;

    case GLUT_KEY_DOWN:
        pos[2] -= 0.1;
        rot[1] = 0;
        break;
    }
    glutPostRedisplay();
}

void motion(int x, int y)
{

    if (mb)
    {
        mx = x;
        my = y;
    }
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

    //glutTimerFunc(1000/FPS,timer,0);

    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutKeyboardUpFunc(keyboard_up);
    glutSpecialFunc(special);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutPassiveMotionFunc(passiveMotion);
    glutMainLoop();
    return (0);
}