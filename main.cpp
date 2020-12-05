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
Enemy enemy = Enemy(0, -1, 10, 90);
world map = world();
Image texture;
const int width = 16 * 80;
const int height = 9 * 80;

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
    gluPerspective(60, 16.0 / 9.0, 0.1, 75);
}

void display()
{

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

    map.drawWorld();

    enemy.draw();
    enemy.findPath(map.boundaries);
    player.draw();
    player.drawHUD();

    glFlush();
}

void timer(int x)
{
    player.projectileUpdate();
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
    for(int i =0; i< map.boundaries.size();i++){
        float dx = (player.pos[0]+sin(player.angle * TO_RADIANS) * 0.5) - (map.boundaries[i][0]+1);
        float dy = (player.pos[2]+cos(player.angle * TO_RADIANS) * 0.5) - (map.boundaries[i][2]+1);
        float dist = sqrt(dx*dx+dy*dy);
        if(dist < 1 + 0.8)
        {
            player.pos[0] -= sin(player.angle * TO_RADIANS);
            player.pos[2] -= cos(player.angle * TO_RADIANS); 
            break;
        }
    }

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
    }
    player.playerMove();

    glutPostRedisplay();
}
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

    glutCreateWindow("Tank Game");

    glutTimerFunc(1000 / FPS, timer, 0);

    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutKeyboardUpFunc(keyboard_up);
    glutSpecialFunc(special);
    map.texture.texture();
    glutMainLoop();
    player.bullets.clear();
    return (0);
}