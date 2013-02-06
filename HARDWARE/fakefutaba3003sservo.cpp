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
    //-- Screw length:
    screw_length = 20;

    //-- Axis dimensions:
    axis_h = 6;
    axis_r = 3;
    axis_y = 30;

    rebuild();
}

Component FakeFutaba3003sServo::build()
{
    //-- Create body
    Component body = Cube::create( width, length, height, false);
    body.translate( -width/2, 0,0);

    //-- Create axis
    Component axis = Cylinder::create( axis_r, axis_h, 20, true);
    axis.translate( 0, axis_y, height + axis_h / 2);

    //-- Create legs
    Component leg_top = Cube::create( leg_x, leg_y, leg_z, false);
    leg_top.translate( -leg_x/2, length, leg_h);

    Component leg_bottom = leg_top.translatedCopy( 0, -( length + leg_y), 0);


    //-- Create holes:
    Component hole_base = Cylinder::create( hole_r, leg_z + 0.2, 20, true);
    Component hole01 = hole_base.translatedCopy(  hole_x, length + hole_y, leg_h + leg_z/2.0);
    Component hole02 = hole_base.translatedCopy( -hole_x, length + hole_y, leg_h + leg_z/2.0);
    Component hole03 = hole_base.translatedCopy(  hole_x,         -hole_y, leg_h + leg_z/2.0);
    Component hole04 = hole_base.translatedCopy( -hole_x,         -hole_y, leg_h + leg_z/2.0);
    Component holes = hole01 + hole02 + hole03 + hole04;

    //-- Composing the servo:
    Component servo = body + axis + leg_top + leg_bottom - holes;

    //-- Paint it black:
   // servo.color( 0.2, 0.2, 0.2);

    //-- Add a link for the horn:
    servo.addLink( RefSys( 0, axis_y, height + axis_h));

    //-- Attach the horn:
    if ( display_horn)
    {
	Component horn = Servo_Horn( horn_arms);
	horn.color( 0.2, 0.2, 0.2, 0.3);
	servo.attach( 0, horn, 2 );
    }


    return servo; //-- Dummy cube
}
