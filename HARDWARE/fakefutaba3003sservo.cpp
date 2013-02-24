#include "fakefutaba3003sservo.h"

FakeFutaba3003sServo::FakeFutaba3003sServo(): BasicServo()
{
    //-- Servo body dimensions:
    //---------------------------------------------------------------------------------
    //-- Main dimensions:
    width = 20.5;
    length = 41;
    height = 39.5;

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

    //-- Horn placement:
    horn_dist_axis = 4;

    //-- Tolerances:
    width_tol = 0;
    length_tol = 0;
    height_tol = 0;

    //-- Horn dimensions:
    //----------------------------------------------------------------------------------
    set_horn( 0 );

    rebuild();
}

void FakeFutaba3003sServo::set_horn( int arms, bool visibility, double cut)
{
    horn_num_arms = arms;
    display_horn = visibility;
    horn_cut = cut;

    horn_tol = 0;

    //-- Set parameters depending on the number of arms of the servo horn.
    //-- For fake futaba:
    switch( horn_num_arms )
    {
    case 0: default:
	//-- Rounded horn:
	horn_h_top = 3;
	horn_r_top = 20.5 / 2.0;
	horn_h_axis = 3.5;
	horn_r_axis = 9 / 2.0;
	//-- Not needed for rounded horn:
	horn_arm_r = 0;
	horn_arm_shift = 0;
	horn_arm_dist = 0;
	break;

    case 2:
	//-- 2-arms horn:
	horn_h_top = 3;
	horn_r_top = 12.5 / 2.0;
	horn_h_axis = 3;
	horn_r_axis = 9 / 2.0;
	horn_arm_r = 5 / 2.0;
	horn_arm_shift = 0;
	horn_arm_dist = 19 - 5 / 2.0;
	break;

    case 4:
	//-- 4-arms horn:
	horn_h_top = 3;
	horn_r_top = 13.5 / 2.0;
	horn_h_axis = 3;
	horn_r_axis = 9 / 2.0;
	horn_arm_r = 4.5 / 2.0;
	horn_arm_shift = 7;
	horn_arm_dist = 18 - 4.5 / 2.0;
	break;

    case 6:
	//-- 6-arms horn:
	horn_h_top = 3;
	horn_r_top = 15 / 2.0;
	horn_h_axis = 3;
	horn_r_axis = 9 / 2.0;
	horn_arm_r = 5 / 2.0;
	horn_arm_shift = 0;
	horn_arm_dist = (31.5 - 5) / 2.0;
	break;
    }

    rebuild();
}

Component FakeFutaba3003sServo::build()
{
    //-- Create body
    Component body = Cube::create( width + width_tol, length + length_tol, height + height_tol, false);
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

    //-- Add a link for the horn:
    servo.addLink( RefSys( 0, axis_y, height + horn_dist_axis));

    //-- Add several links for the screws:
    servo.addLink( RefSys(  hole_x, length + hole_y, leg_h + leg_z/2.0));
    servo.addLink( RefSys( -hole_x, length + hole_y, leg_h + leg_z/2.0));
    servo.addLink( RefSys(  hole_x,         -hole_y, leg_h + leg_z/2.0));
    servo.addLink( RefSys( -hole_x,         -hole_y, leg_h + leg_z/2.0));

    //-- Paint it black:
    servo.color( 0.2, 0.2, 0.2);

    //-- Attach the horn:
    if ( display_horn)
    {
	//! \todo Change this
	horn = make_horn();
	horn.color( 0.2, 0.2, 0.2);
	horn.relRotate(0,0,-90); //-- Temporal fix
	servo.attach( 0, horn, 2 );

    }

    return servo;
}
