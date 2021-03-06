//------------------------------------------------------------------------------
//-- Basic servo
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

/*! \file basicservo.cpp
 *  \brief Defines the simplest structure of a servo, and its data interface.
 *
 *  To make objects compatible with as much servos as possible, new servos
 *  should inherit from this 'BasicServo'
 *
 * \author David Estévez Fernández ( http://github.com/David-Estevez )
 * \date Aug 4th, 2013
 *
 */

#include "basicservo.h"

//-- Default constructor
BasicServo::BasicServo()
{
    //-- Default horn configuration ( rounded, not shown)
    horn_num_arms = 0;
    display_horn = false;
}

//-- Basic servo data interface:
//=============================================================================================
double BasicServo::get_width() {   return width;    }
double BasicServo::get_length(){   return length;   }
double BasicServo::get_height(){   return height;   }


//-- Leg dimensions:
double BasicServo::get_leg_h() {   return leg_h; }
double BasicServo::get_leg_x() {   return leg_x; }
double BasicServo::get_leg_y() {   return leg_y; }
double BasicServo::get_leg_z() {   return leg_z; }

//-- Leg holes
int BasicServo::get_num_holes() {  return num_holes;}
double BasicServo::get_hole_r() {  return hole_r;   }
double BasicServo::get_hole_x() {  return hole_x;   }
double BasicServo::get_hole_y() {  return hole_y;   }

//-- Axis dimensions:
double BasicServo::get_axis_h() {  return axis_h;   }
double BasicServo::get_axis_r() {  return axis_r;   }
double BasicServo::get_axis_y() {  return axis_y;   }

//-- Horn positioning dimensions:
double BasicServo::get_horn_dist_axis()	{   return horn_dist_axis;  }

//-- Tolerances:
double BasicServo::get_width_tol() {	return width_tol;   }
double BasicServo::get_length_tol(){	return length_tol;  }
double BasicServo::get_height_tol(){	return height_tol;  }

//-- Servo body:
Component BasicServo::get_servo_body(){	return servo;	    }


//-- Horn data interface:
//============================================================================================
bool BasicServo::horn_shown()	{   return display_horn; }
Component BasicServo::get_horn(){   return horn;	 }

//-- Horn dimensions:
double BasicServo::get_horn_num_arms()  {   return horn_num_arms;   }
double BasicServo::get_horn_h_top()     {   return horn_h_top;	    }
double BasicServo::get_horn_r_top()	{   return horn_r_top;	    }
double BasicServo::get_horn_h_axis()	{   return horn_h_axis;	    }
double BasicServo::get_horn_r_axis()	{   return horn_r_axis;	    }
double BasicServo::get_horn_arm_r()	{   return horn_arm_r;	    }
double BasicServo::get_horn_arm_shift() {   return horn_arm_shift;  }
double BasicServo::get_horn_arm_dist()  {   return horn_arm_dist;   }
double BasicServo::get_horn_tol()	{   return horn_tol;	    }
double BasicServo::get_horn_cut()	{   return horn_cut;	    }
double BasicServo::get_horn_angle()	{   return horn_angle;	    }

//-- Configuring servo:
//============================================================================================

void BasicServo::set_horn(int arms, double angle, bool visibility, double cut)
{
    horn_num_arms = arms;
    display_horn = visibility;
    horn_cut = cut;
    horn_angle = angle;

    this->update_horn();
}

void BasicServo::set_horn_visibility( bool visibility)
{
    display_horn = visibility;

    this->update_horn();
}

void BasicServo::set_tolerances(double width_tol, double length_tol, double height_tol)
{
    this->width_tol = width_tol;
    this->length_tol = length_tol;
    this->height_tol = height_tol;

    rebuild();
}


//-- Building the basic servo:
//============================================================================================
Component BasicServo::build()
{
    //-- Create body
    Component body = Cube( width + width_tol, length + length_tol, height + height_tol, false);
    body.translate( -width/2, 0,0);

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
    servo = body + axis + leg_top + leg_bottom - holes;

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
	/*----------------------------------------------------------------------
	 *  Weird fix to substitute: (it does not work yet)
	 * servo.attach( 0, horn, 2 );
	 * ---------------------------------------------------------------------*/

	TransformMatrix hornMatrix = horn.getLink(0).getTransformMatrix().getInv();
	TransformMatrix servoMatrix = servo.getLink(0).getTransformMatrix();
	TransformMatrix finalMatrix = servoMatrix * hornMatrix;
	double xa, ya, za; finalMatrix.getGlobalXYZAngles(xa, ya, za);
	double x, y, z; finalMatrix.getGlobalTranslation(x, y, z);
	horn.rotate(xa, ya, za);
	horn.translate(x, y, z);

	return servo + horn;

	/* End of the fix */
    }
    else
    {
	return servo;
    }
}

//-- Servo horn:
//============================================================================================

void BasicServo::make_horn()
{
    //-- Create axis cylinder
    horn = Cylinder(horn_r_axis + horn_tol, horn_h_axis +0.2, 100, false);
    horn.translate(0,0,-0.1);

    if (horn_num_arms == 0) //-- Rounded horn
    {
	Component top = Cylinder( horn_r_top + horn_tol, horn_h_top, 100, false);
	top.translate(0, 0, horn_h_axis);
	horn = horn + top;

	if ( horn_cut < 2*horn_r_top && horn_cut > 0 )
	{
	    //-- Create a cube with the dimensions of the cut
	    Component to_be_substracted = Cube( (horn_r_top + horn_tol)- horn_cut + 0.1,
						 2*(horn_r_top + horn_tol)+0.2,
						 horn_h_top+0.2,
						 false);

	    //-- Center it on Y:
	    to_be_substracted.translate(0, -(horn_r_top + horn_tol)+0.1, 0);

	    //-- Place it on its place (LOL) and substract it:
	    horn = horn - to_be_substracted.translate( horn_cut + 0.1 ,0, horn_h_axis-0.1);
	    horn.relRotate( 0, 0, 90);
	 }
    }
    else //-- Horn with arms:
    {
	//-- Create a single arm:
	Component base = Cube( 2*horn_r_axis, horn_arm_shift + 0.001, horn_h_top+0.1);
	Component upper_cyl = Cylinder( horn_arm_r,horn_h_top+0.1, 100, true);
	upper_cyl = upper_cyl.translate( 0, horn_arm_dist, 0);

	Component arm = base & upper_cyl;
	arm.translate(0, 0, (horn_h_top+0.1) /2);

	//-- Create the orher arms by rotation:
	Component arms = arm;
	for ( int i = 1; i < horn_num_arms; i++)
	    arms = arms + arm.rotatedCopy(0,0, 360/horn_num_arms*i);
	arms.translate( 0, 0, horn_h_axis);

	//-- Add the top cylinder:
	Component top_cyl = Cylinder( horn_r_top, horn_h_top + 0.1, 100, false)
			    .translate(0,0, horn_h_axis);

	//-- Sum up all the parts:
	horn = horn + arms + top_cyl;
    }

    //-- Set link on the end of the axis cylinder, to attach to the servo:
    horn.addLink( RefSys( 0,0, horn_h_axis));
    //! -- \todo Change this when OOML is fixed:
    horn.relTranslate(0,0,-horn_h_axis);
}

