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
Enemy enemy = Enemy(-6, 0, -10, 90);
world map = world();
Image texture;
const int width = 16 * 80;
const int height = 9 * 80;
const int miniWidth = 300;
const int miniHeight = 300;
GLint mainWindow, subWindow;
unsigned int fbo;
bool col = true;

bool move = false;
float prevPos[3];

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

// AABB collision is used for the players Tank 
bool collisionTest(int i){

    float d1z = map.boundaries[i][1] - player.aabb_max[2];
    float d1x = map.boundaries[i][0] - player.aabb_max[0];

    float d2z = player.aabb_min[2] - map.boundaries[i][3];
    float d2x = player.aabb_min[0] - map.boundaries[i][2];

    if (d1x > 0.0f || d1z > 0.0f){
        return false;
    }

    if (d2x > 0.0f || d2z > 0.0f){
        return false;
    }
    return true;


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

    map.drawWorld();

    enemy.draw();
    enemy.findPath(map.boundaries);
    player.draw();
    player.drawHUD();
    minimap();
    player.detectEnemy(enemy.pos[0], enemy.pos[2], enemy.angle);
    glFlush();
}
//minimap draw function
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

//timer function that handles the projectile collision and updating
void timer(int x)
{
    enemy.projectileUpdate();
    player.projectileUpdate();
    //player's bullets collision detection with walls and enemy
    for (int i = 0; i < player.bullets.size(); i++)
    {
        float dx = (enemy.pos[0] + sin(enemy.angle * TO_RADIANS) * 0.3) - (player.bullets[i][0] + sin(player.bullets[i][2] * TO_RADIANS) * 0.5);
        float dy = (enemy.pos[2] + cos(enemy.angle * TO_RADIANS) * 0.3) - (player.bullets[i][1] + cos(player.bullets[i][2] * TO_RADIANS) * 0.5);
        float dist = sqrt(dx * dx + dy * dy);
        if (dist < 1 + 1 && player.bullets[i][3] > 0)
        {
            player.score += 1;
            player.bullets[i][3] = 0;
        }
        for(int j =0; j< map.boundaries.size();j++){
            dx = (player.bullets[i][0] + sin(player.bullets[i][2] * TO_RADIANS) * 0.5) - (map.boundaries[j][0]+1);
            dy = (player.bullets[i][1] + cos(player.bullets[i][2] * TO_RADIANS) * 0.5) - (map.boundaries[j][1]+1);
            dist = sqrt(dx*dx+dy*dy);
            if(dist < 1 + 0.5 && player.bullets[i][3] > 0)
            {
                player.bullets[i][3] = 0;
                break;
            }

        }
    }
    //Enemy's bullets collision detection with walls and player
    for (int i = 0; i < enemy.bullets.size(); i++)
    {
        float dx = (player.pos[0] + sin(player.angle * TO_RADIANS) * 0.3) - (enemy.bullets[i][0] + sin(enemy.bullets[i][2] * TO_RADIANS) * 0.5);
        float dy = (player.pos[2] + cos(player.angle * TO_RADIANS) * 0.3) - (enemy.bullets[i][1] + cos(enemy.bullets[i][2] * TO_RADIANS) * 0.5);
        float dist = sqrt(dx * dx + dy * dy);
        if (dist < 1 + 1 && enemy.bullets[i][3] > 0)
        {
            player.lives -= 1;
            enemy.bullets[i][3] = 0;
        }
        for (int j = 0; j < map.boundaries.size(); j++)
        {
            dx = (enemy.bullets[i][0] + sin(enemy.bullets[i][2] * TO_RADIANS) * 0.5) - (map.boundaries[j][0] + 1);
            dy = (enemy.bullets[i][1] + cos(enemy.bullets[i][2] * TO_RADIANS) * 0.5) - (map.boundaries[j][1] + 1);
            dist = sqrt(dx * dx + dy * dy);
            if (dist < 1 + 0.5 && enemy.bullets[i][3] > 0)
            {
                enemy.bullets[i][3] = 0;
                break;
            }
        }
    }
    glutPostRedisplay();
    glutTimerFunc(1000 / FPS, timer, 0);

}
//check for keyboard release to disable movement in that direction
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

//
void keyboard(unsigned char key, int x, int y)
{
    bool collision;

    if (player.lives > 0)
    {
        //the maze boundaries are checked against the bounding box on the players tank
        //if there is a collision then the pos reverts back to the previous non collided position
        for (int i = 1; i < map.boundaries.size(); i++)
        {
            collision = collisionTest(i);
            if (collision)
            {
                player.pos[0] = prevPos[0];
                player.pos[1] = prevPos[1];
                player.pos[2] = prevPos[2];
                player.updateCamera();
                break;
            }
        }

        if (!collision)
        {
            prevPos[0] = player.pos[0];
            prevPos[1] = player.pos[1];
            prevPos[2] = player.pos[2];

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
            }

            player.playerMove();

            glutPostRedisplay();
        }
    }
}


void special(int key, int x, int y)
{
    if (key == GLUT_KEY_RIGHT)
    {
        if (glutGetModifiers() == GLUT_ACTIVE_SHIFT)
            player.tilt += 0.01;
        else
            player.dolly += 0.1;
    }
    if (key == GLUT_KEY_LEFT)
    {
        if (glutGetModifiers() == GLUT_ACTIVE_SHIFT)
            player.tilt -= 0.01;
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

void mouse(int button, int state, int x, int y)
{
    if( button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && player.lives < 1 )
    {
        if (450 < x && x < 830 && 175 < y && y < 830) {
            Player newP = Player();
            player = newP;
            enemy = Enemy(20, -1, 10, 90);
        }
    }
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


    glutInitWindowPosition((width-miniWidth), (width-miniHeight));
    glutInitWindowSize(miniWidth, miniHeight);
    subWindow = glutCreateWindow("MiniMap");
    
    glutDisplayFunc(minimap);
    glutReshapeFunc(reshape);

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
    glutMouseFunc(mouse);

    map.texture.texture();
    player.bullets.clear();

    glutMainLoop();
    return (0);
}