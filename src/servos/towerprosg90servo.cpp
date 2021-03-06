//------------------------------------------------------------------------------
//-- Tower Pro SG90 servo
//------------------------------------------------------------------------------
//-- This file belongs to the REPY-2.0 module project:
//--
//--	· http://www.dsquaredrobotics.com/wiki/index.php?title=REPY-2.0
//--
//--
//-- REPY-2.0 was designed using the 00ML (Object-Oriented Mechanics Library).
//-- More info about the OOML at:
//--	· http://iearobotics.com/oomlwiki/doku.php
//--
//-- REPY-2.0 concept is deeply based on Juan Gonzalez-Gomez REPY module. More
//-- info about the original REPY at:
//--	· http://www.thingiverse.com/thing:13442
//--	· http://www.iearobotics.com/wiki/index.php?title=M%C3%B3dulos_REPY-1
//--
//------------------------------------------------------------------------------
//-- Author: David Estevez (DEF)
//--
//-- Released under the GPL license (more info on LICENSE.txt file)
//------------------------------------------------------------------------------

/*! \file towerprosg90servo.h
 *  \brief Tower Pro SG90 servo
 *
 * \author David Estévez Fernández ( http://github.com/David-Estevez )
 * \date Apr 8th, 2013
 */

#include "towerprosg90servo.h"


TowerProSG90servo::TowerProSG90servo(): BasicServo()
{
    //-- Servo body dimensions:
    //---------------------------------------------------------------------------------
    //-- Main dimensions:
    width = 12.7;
    length = 22.7;
    height = 27;

    //-- Leg dimensions:
    leg_h = 15.7;
    leg_x = 12;
    leg_y = 5;
    leg_z = 2.5;

    //-- Leg holes
    num_holes = 2;
    hole_r = 1.1;
    hole_x = 0;
    hole_y = 2.5;

    //-- Axis dimensions:
    axis_h = 2.5;
    axis_r = 4.7/2.0;
    axis_y = 17;

    //-- Horn placement:
    horn_dist_axis = 2.9;

    //-- Tolerances by default:
    width_tol = 0;
    length_tol = 0;
    height_tol = 0;

    //-- Color (blue):
    servo_color.push_back( 0); //-- Red
    servo_color.push_back( 0.); //-- Green
    servo_color.push_back( 1); //-- Blue
    servo_color.push_back( 1.0); //-- Alpha channel

    //-- Horn dimensions:
    //----------------------------------------------------------------------------------
    set_horn( 1 );

    //-- TowerPro SG90 servo specific dimensions:
    gearbox_h = 4.5;
    gearbox_big_r = 11.8 /2.0;
    gearbox_small_r = 5 / 2.0;
    gearbox_small_y = axis_y - 14.5 + gearbox_small_r + gearbox_big_r;

    rebuild();
}

void TowerProSG90servo::update_horn()
{
    //-- Horn tolerance
    horn_tol = 0;

    //-- Color (white)
    horn_color.push_back( 1); //-- Red
    horn_color.push_back( 1); //-- Green
    horn_color.push_back( 1); //-- Blue
    horn_color.push_back( 1.0); //-- Alpha channel

    //-- Set parameters depending on the number of arms of the servo horn:
    //--------------------------------------------------------------------
    switch( horn_num_arms )
    {
    default:
	horn_num_arms = 1;

    case 1:
	//-- 1-arm horn:
	horn_h_top = 1.7;
	horn_r_top = 7.2 / 2.0;
	horn_h_axis = 2.7;
	horn_r_axis = 7.2 / 2.0;
	horn_arm_r = 3.6/2.0;
	horn_arm_shift = 0;
	horn_arm_dist = 19.6 -horn_r_top -horn_arm_r;
	break;

    case 2:
	//-- 2-arms horn:
	horn_h_top = 1.7;
	horn_r_top = 7.2 / 2.0;
	horn_h_axis = 2.7;
	horn_r_axis = 7.2 / 2.0;
	horn_arm_r = 3.6 / 2.0;
	horn_arm_shift = 0;
	horn_arm_dist = 32 /2.0 - horn_arm_r / 2.0;
	break;

    case 4:
	//-- 4-arms horn:
	horn_h_top = 1.7;
	horn_r_top = 8 / 2.0;
	horn_h_axis = 2.8;
	horn_r_axis = 7.2 / 2.0;
	horn_arm_r = 3.6 / 2.0;
	horn_arm_shift = 7;
	horn_arm_dist = 18 - 4.5 / 2.0;

	//-- Extra parameters:
	horn_arm_r_small = 3.8 / 2.0;
	horn_arm_dist_small = 16.8 / 2.0 - horn_arm_r_small;
	break;
    }

    rebuild();
}


double TowerProSG90servo::get_gearbox_h()	    { return gearbox_h;		    }
double TowerProSG90servo::get_gearbox_big_r()	    { return gearbox_big_r;	    }
double TowerProSG90servo::get_gearbox_small_r()	    { return gearbox_small_r;	    }
double TowerProSG90servo::get_gearbox_small_y()	    { return gearbox_small_y;	    }

double TowerProSG90servo::get_horn_arm_r_small()    { return horn_arm_r_small;	    }
double TowerProSG90servo::get_horn_arm_dist_small() { return horn_arm_dist_small;   }


Component TowerProSG90servo::build()
{
    //-- Create body
    Component body = Cube( width + width_tol, length + length_tol, height + height_tol - gearbox_h, false);
    body.translate( -width/2, 0,0);

    Component gearbox_big = Cylinder( gearbox_big_r + width_tol/2.0, gearbox_h, 100, false);
    gearbox_big.translate(0, axis_y, height + height_tol - gearbox_h);

    Component gearbox_small = Cylinder( gearbox_small_r, gearbox_h, 100, false);
    gearbox_small.translate( 0, gearbox_small_y, height + height_tol - gearbox_h);

    body = body + gearbox_big + gearbox_small;

    //-- Create axis
    Component axis = Cylinder( axis_r, axis_h, 20, true);
    axis.translate( 0, axis_y, height + axis_h / 2);

    //-- Create legs
    Component leg_top = Cube( leg_x, leg_y, leg_z, false);
    leg_top.translate( -leg_x/2, length, leg_h);

    Component leg_bottom = leg_top.translatedCopy( 0, -( length + leg_y), 0);


    //-- Create holes:
    Component holes;
    Component hole_base = Cylinder( hole_r, leg_z + 0.2, 20, true);

    if (num_holes == 4) //-- 4 holes, 2 on each leg
    {

	Component hole01 = hole_base.translatedCopy(  hole_x, length + hole_y, leg_h + leg_z/2.0);
	Component hole02 = hole_base.translatedCopy( -hole_x, length + hole_y, leg_h + leg_z/2.0);
	Component hole03 = hole_base.translatedCopy(  hole_x,         -hole_y, leg_h + leg_z/2.0);
	Component hole04 = hole_base.translatedCopy( -hole_x,         -hole_y, leg_h + leg_z/2.0);
	holes = hole01 + hole02 + hole03 + hole04;
    }
    else if (num_holes == 2) //-- 2 holes, 1 on each leg
    {
	Component hole01 = hole_base.translatedCopy( hole_x, length + hole_y, leg_h + leg_z/2.0);
	Component hole02 = hole_base.translatedCopy( hole_x,	     -hole_y ,leg_h + leg_z/2.0);
	holes = hole01 + hole02;
    }

    //-- Composing the servo:
    Component servo = body + axis + leg_top + leg_bottom - holes;

    //-- Add a link for the horn:
    servo.addLink( RefSys( 0, axis_y, height + horn_dist_axis));

    //-- Add several links for the screws:
    if (num_holes == 4) //-- 4 holes, 2 on each leg
    {
	servo.addLink( RefSys(  hole_x, length + hole_y, leg_h + leg_z/2.0));
	servo.addLink( RefSys( -hole_x, length + hole_y, leg_h + leg_z/2.0));
	servo.addLink( RefSys(  hole_x,         -hole_y, leg_h + leg_z/2.0));
	servo.addLink( RefSys( -hole_x,         -hole_y, leg_h + leg_z/2.0));
    }
    else if (num_holes == 2)
    {
	servo.addLink( RefSys(  hole_x, length + hole_y, leg_h + leg_z/2.0));
	servo.addLink( RefSys(  hole_x,         -hole_y, leg_h + leg_z/2.0));
    }
    //-- Paint it black:
    servo.color( servo_color[0], servo_color[1], servo_color[2], servo_color[3]);

    //-- Attach the horn:
    if ( display_horn)
    {
	//! \todo Change this
	make_horn();
	horn.color( horn_color[0], horn_color[1], horn_color[2], horn_color[3]);
	horn.relRotate(0,0, horn_angle);
	servo.attach( 0, horn, 2 );

    }

    return servo;
}

void TowerProSG90servo::make_horn()
{
    if ( horn_num_arms != 4)
    {
	BasicServo::make_horn();
	horn.relRotate(0, 0, 180);
    }
    else
    {
	//-- Construct 4-arm servo horn

	//-- Create axis cylinder
	horn = Cylinder(horn_r_axis + horn_tol, horn_h_axis +0.2, 100, false);
	horn.translate(0,0,-0.1);

	//-- Create a single arm of type 1:
	Component base_type1 = Cube( 2*horn_r_axis, horn_arm_shift + 0.001, horn_h_top+0.1);
	Component upper_cyl_type1 = Cylinder( horn_arm_r,horn_h_top+0.1, 100, true);
	upper_cyl_type1.translate( 0, horn_arm_dist, 0);

	Component arm_type1 = base_type1 & upper_cyl_type1;
	arm_type1.translate(0, 0, (horn_h_top+0.1) /2);

	//-- Create a single arm of type 2:
	Component base_type2 = Cube( 2*horn_arm_r_small, 0.001, horn_h_top+0.1);
	Component upper_cyl_type2 = Cylinder( horn_arm_r_small, horn_h_top + 0.1, 100, true);
	upper_cyl_type2.translate( 0, horn_arm_dist_small, 0);

	Component arm_type2 = base_type2 & upper_cyl_type2;
	arm_type2.translate(0, 0, (horn_h_top+0.1) /2);
	arm_type2.rotate( 0,0, 90);

	Component arms = arm_type1 + arm_type1.rotatedCopy(0,0, 180)
		       + arm_type2 + arm_type2.rotatedCopy(0,0, 180);
	arms.translate( 0, 0, horn_h_axis);


	//-- Add the top cylinder:
	Component top_cyl = Cylinder( horn_r_top, horn_h_top + 0.1, 100, false)
		.translate(0,0, horn_h_axis);

	//-- Sum up all the parts:
	horn = horn + arms + top_cyl;

	//-- Set link on the end of the axis cylinder, to attach to the servo:
	horn.addLink( RefSys( 0,0, horn_h_axis));
	//! -- \todo Change this when OOML is fixed:
	horn.relTranslate(0,0,-horn_h_axis);
    }
}
