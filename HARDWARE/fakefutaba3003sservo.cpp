#include "fakefutaba3003sservo.h"

FakeFutaba3003sServo::FakeFutaba3003sServo(): Basic_Servo()
{
    //-- Main dimensions:
    width = 20;
    length = 41;
    height = 40;

    //-- Leg dimensions:
    leg_h = 27;
    leg_x = 20;
    leg_y = 6.5;
    leg_z = 4;

    //-- Leg holes
    num_holes = 4; //-- ??
    hole_r = 2;
    hole_x = 5;
    hole_y = 4;

    //-- Axis dimensions:
    axis_h = 6;
    axis_r = 3;
    axis_y = 30;

    rebuild();
}

Component FakeFutaba3003sServo::build()
{
    return Cube::create(1); //-- Dummy cube
}
