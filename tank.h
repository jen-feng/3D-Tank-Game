#ifndef TANK_H
#define TANK_H

class tank{
public: 

    float pos[2];
    int lives;

    tank();
    void drawTank();
    void camera();
    void shoot();

    struct Motion
    {
        bool Forward,Backward,rLeft,rRight;
    }movement;

private:

    float camX, camZ, yaw;

};

#endif
