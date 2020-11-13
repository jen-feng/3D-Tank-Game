#include "main.h"

GLdouble eye[] = {0, 1, 0};
GLdouble lookAt[] = {0, 1, 0};
GLdouble up[] = {0, 1, 0};
Tank tank1 = Tank();
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

float proj_pos[] = {0, 0, 0};
float proj_dir[] = {0, 0, 0};
bool fire = false;
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

    if(fire){
        drawProjectile();
    }

    glFlush();
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

    if(fire){
        proj_pos[0] += proj_dir[0];
        proj_pos[2] += proj_dir[2];

        float len = sqrt((proj_pos[0]*proj_pos[0]) + (proj_pos[2]*proj_pos[2]));
        if(len > 25){
            fire = false;
        }
    }

    glutPostRedisplay();
    glutTimerFunc(1000 / FPS, timer, 0);
}
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

void shoot(){
    proj_pos[0] = eye[0];
    proj_pos[1] = eye[1];
    proj_pos[2] = eye[2];

    proj_dir[0] = lookAt[0];
    proj_dir[1] = lookAt[1];
    proj_dir[2] = lookAt[2];
    fire=true;
}

void drawProjectile(){

    glPushMatrix();
        glTranslatef(proj_pos[0],proj_pos[1],proj_pos[2]);
        glColor3f(0.5,0.5,0.5);
        glScalef(0.2,0.2,0.2);
        glutSolidSphere(1, 10, 10);
    glPopMatrix();

}

void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'w':
    case 'W':
        tank1.movement.Forward = true;

        eye[0] += sin(angle * TO_RADIANS) * 0.2;
        lookAt[0] += sin(angle * TO_RADIANS) * 0.2;
        eye[2] += cos(angle * TO_RADIANS) * 0.2;
        lookAt[2] += cos(angle * TO_RADIANS) * 0.2;
        break;
    case 'a':
    case 'A':
        tank1.movement.Forward = true;

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

        shoot();
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

    glutTimerFunc(1000/FPS,timer,0);

    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutKeyboardUpFunc(keyboard_up);
    //glutSpecialFunc(special);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutPassiveMotionFunc(passiveMotion);
    glutMainLoop();
    return (0);
}