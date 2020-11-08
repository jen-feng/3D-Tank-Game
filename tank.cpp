#include "main.h"

tank::tank(){
    movement.Forward = false;
}

void tank::drawTank(){

}

void tank::camera(){


    if(movement.Forward){
    camX += cos((yaw+90+180)*TO_RADIANS)/5.0;
    camZ -= sin((yaw+90+180)*TO_RADIANS)/5.0;
    }
    if(movement.Backward){
        camX += cos((yaw+90)*TO_RADIANS)/5.0;
        camZ -= sin((yaw+90)*TO_RADIANS)/5.0;
    }
    if(movement.rLeft){
        yaw++;
    }
    if(movement.rRight){
        yaw--;
    }

    if(yaw > 360){
        yaw = 0;
    }
    if(yaw < 0){
        yaw = 360;
    }

    glRotatef(-yaw,0,1,0);
    glTranslatef(-camX,0.0,-camZ);
}