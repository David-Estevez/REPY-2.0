//------------------------------------------------------------------------------
//-- Futaba 3003s servo
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

/*! \file futaba3003sservo.h
 *  \brief Futaba 3003s servo.
 *
 * \author David Estévez Fernández ( http://github.com/David-Estevez )
 * \date Jun 17th, 2013
 *
 * \todo Add more horns.
 */

#include "futaba3003sservo.h"

Futaba3003sServo::Futaba3003sServo(): BasicServo()
{
    //-- Servo body dimensions:
    //---------------------------------------------------------------------------------
    //-- Main dimensions:
    width = 20.5;
    length = 40.5;
    height = 37.7;

    //-- Leg dimensions:
    leg_h = 26.6;
    leg_x = 20;
    leg_y = 7.5;
    leg_z = 4;

    //-- Leg holes
    num_holes = 4;
    hole_r = 4.5/2.0;
    hole_x = 5;
    hole_y = 3;

    //-- Axis dimensions:
    axis_h = 42. - height;
    axis_r = 3;
    axis_y = 30;

    //-- Horn placement:
    horn_dist_axis = 44-2.1-37.7;

    //-- Tolerances by default:
    width_tol = 0;
    length_tol = 0;
    height_tol = 0;

    //-- Color (black):
    servo_color.push_back( 0.5); //-- Red
    servo_color.push_back( 0.5); //-- Green
    servo_color.push_back( 0.5); //-- Blue
    servo_color.push_back( 1.0); //-- Alpha channel

    //-- Horn dimensions:
    //----------------------------------------------------------------------------------
    set_horn( 0 );

    rebuild();
}

void Futaba3003sServo::update_horn()
{
    //-- Horn tolerance
    horn_tol = 0;

    //-- Color (black)
    horn_color.push_back( 0.5); //-- Red
    horn_color.push_back( 0.5); //-- Green
    horn_color.push_back( 0.5); //-- Blue
    horn_color.push_back( 1.0); //-- Alpha channel

    //-- Set parameters depending on the number of arms of the servo horn:
    //--------------------------------------------------------------------
    switch( horn_num_arms )
    {
    default:
	horn_num_arms = 0;

    case 0:
	//-- Rounded horn:
	horn_h_top = 2.2;
	horn_r_top = 21 / 2.0;
	horn_h_axis = 6.3 - horn_h_top;
	horn_r_axis = 8.1 / 2.0;
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
