#include "main.h"


world::world(){

    size = 50;

}

void world::drawWorld(){
    int pat = 1;

    for(int x = -25; x < size-1/2.0; x++){
        for(int z = -25; z < size-1/2.0; z++){

            glBegin(GL_QUADS);

                if(pat == 1){
                    glColor3f(0,0,0);
                    glVertex3f(x,0,z);
                    glVertex3f(x,0,z+1);
                    glVertex3f(x+1,0,z+1);
                    glVertex3f(x+1,0,z);
                    pat = 0;
                } else {
                    glColor3f(1,1,1);
                    glVertex3f(x,0,z);
                    glVertex3f(x,0,z+1);
                    glVertex3f(x+1,0,z+1);
                    glVertex3f(x+1,0,z);
                    pat = 1;
                }

            glEnd();
        }
    }
    pat = 1;
}

void world::drawAxis(){


    glColor3f(1.0,0.0,0.0); // red x
    glBegin(GL_LINES);
    // x axis
 
    glVertex3f(-4.0, 0.0f, 0.0f);
    glVertex3f(4.0, 0.0f, 0.0f);
 
    // arrow
    glVertex3f(4.0, 0.0f, 0.0f);
    glVertex3f(3.0, 1.0f, 0.0f);
 
    glVertex3f(4.0, 0.0f, 0.0f);
    glVertex3f(3.0, -1.0f, 0.0f);
 
    // y 
    glColor3f(0.0,1.0,0.0); // green y
    glVertex3f(0.0, -4.0f, 0.0f);
    glVertex3f(0.0, 4.0f, 0.0f);
 
    // arrow
    glVertex3f(0.0, 4.0f, 0.0f);
    glVertex3f(1.0, 3.0f, 0.0f);
 
    glVertex3f(0.0, 4.0f, 0.0f);
    glVertex3f(-1.0, 3.0f, 0.0f);
 
    // z 
    glColor3f(0.0,0.0,1.0); // blue z
    glVertex3f(0.0, 0.0f ,-4.0f );
    glVertex3f(0.0, 0.0f ,4.0f );
 
    // arrow
    glVertex3f(0.0, 0.0f ,4.0f );
    glVertex3f(0.0, 1.0f ,3.0f );
 
    glVertex3f(0.0, 0.0f ,4.0f );
    glVertex3f(0.0, -1.0f ,3.0f );
    glEnd();
}