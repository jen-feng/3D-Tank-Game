#include "main.h"


GLdouble eye[] = { 0, 1, -1};
GLdouble lookAt[] = { 0, 1, 0};
GLdouble up[] = { 0, 1, 0 };



bool mb = false;
int x, y, mx, my;
int size = 50;
const int width = 16*50;
const int height = 9*50;



world map;
tank tank1;


void init(void){

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0, 0, 0, 0);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60,16.0/9.0,1,75);

}

void display(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(
        eye[0], eye[1], eye[2],
        lookAt[0], lookAt[1], lookAt[2],
        up[0], up[1], up[2]
    );

    tank1.camera();
    map.drawWorld();
    
    
    glFlush();
}

// void timer(int x){


//     glutPostRedisplay();
//     glutTimerFunc(1000/FPS,timer,0);
// }
void keyboard(unsigned char key, int x, int y){
    
    switch(key){
		case 'w': case 'W':
            tank1.movement.Forward = true;
			break;
		case 'a': case 'A': 
            tank1.movement.rLeft = true;
			break;
        case 's': case 'S':
            tank1.movement.Backward = true;
            break;
        case 'd': case 'D':
            tank1.movement.rRight = true;
            break;
	}
    glutPostRedisplay();
}
void keyboard_up(unsigned char key,int x,int y){
    switch(key){
		case 'w': case 'W':
            tank1.movement.Forward = false; 
			break;
		case 'a': case 'A': 
            tank1.movement.rLeft = false;
			break;
        case 's': case 'S':
            tank1.movement.Backward = false;
            break;
        case 'd': case 'D':
            tank1.movement.rRight = false;
            break;
	}
    glutPostRedisplay();
}

void mouse(int button, int state, int x, int y){

	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
		mb = true;
	} else {
		mb = false;
	}
}

void motion(int x, int y){

	if(mb){
		mx = x;
	    my = y;
	}
}

void passiveMotion(int x, int y){

}

void reshape(int w,int h)
{
    glViewport(0,0,w,h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60,16.0/9.0,1,75);
    glMatrixMode(GL_MODELVIEW);

}
int main(int argc, char** argv){

    glutInit(&argc, argv);		
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH);

    glutInitWindowPosition(0,0);
    glutInitWindowSize(width,height);

    glutCreateWindow("Terrain");

    
    //glutTimerFunc(1000/FPS,timer,0);

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
    return(0);				
}