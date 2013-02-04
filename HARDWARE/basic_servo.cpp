//------------------------------------------------------
//-- Basic servo
//------------------------------------------------------
//-- A parametric simple servo
//-- It is used for creating the module.
//------------------------------------------------------
//-- Author: David Estevez (DEF)
//------------------------------------------------------

#include <ooml/core.h>
#include <ooml/components.h>

#include "basic_servo.h"
#include "ear.h"

//-- Default
Basic_Servo::Basic_Servo()
{
    //-- Default horn configuration
    horn_arms = 0;
    display_horn = false;
}

//-- Basic servo implementations:
//=============================================================================================
double Basic_Servo::get_width()	{   return width; }
double Basic_Servo::get_length(){   return length;}
double Basic_Servo::get_height(){   return height;}


//-- Leg dimensions:
double Basic_Servo::get_leg_h()	{   return leg_h; }
double Basic_Servo::get_leg_x() {   return leg_x; }
double Basic_Servo::get_leg_y()	{   return leg_y; }
double Basic_Servo::get_leg_z() {   return leg_z; }

//-- Leg holes
int Basic_Servo::get_num_holes() {  return num_holes;}
double Basic_Servo::get_hole_r() {  return hole_r;}
double Basic_Servo::get_hole_x() {  return hole_x;}
double Basic_Servo::get_hole_y() {  return hole_y;}

//-- Axis dimensions:
double Basic_Servo::get_axis_h() {  return axis_h;}
double Basic_Servo::get_axis_r() {  return axis_r;}
double Basic_Servo::get_axis_y() {  return axis_y;}

//-- Horn
bool Basic_Servo::horn_shown()	{   return display_horn; }
Component Basic_Servo::get_horn()   {	return Servo_Horn( horn_arms); } //-- Not actually true, as it has to be placed.

//-- Servo configuration:
//----------------------------------------------------------------------------------------
void Basic_Servo::set_horn(int arms, bool visibility)
{
    horn_arms = arms;
    display_horn = visibility;
}


/*
Basic_servo::Basic_servo(bool screw, double screw_length, double tol):AbstractPart()
{
    _screw = screw;
    _screw_length = screw_length;
    _tol = tol;
    rebuild();
}

Component Basic_servo::build()
{
    //-- Create body
    Component body = Cube::create( SERVO_WIDTH, SERVO_LENGTH, SERVO_HEIGHT, false);
    body.translate(- SERVO_WIDTH / 2, 0, 0);

    //-- Create axis
    Component axis = Cylinder::create( SERVO_AXIS_R, SERVO_AXIS_H, 20, true);
    axis.translate(0, SERVO_AXIS_Y, SERVO_HEIGHT + SERVO_AXIS_H / 2);

    //-- Create legs
    Component leg01 = Cube::create(SERVO_LEG_X, SERVO_LEG_Y, SERVO_LEG_Z, false);
    leg01.translate(-SERVO_LEG_X/2, SERVO_LENGTH, SERVO_LEG_H );
    Component leg02 = leg01.translatedCopy(0, -(SERVO_LENGTH + SERVO_LEG_Y), 0);

    //-- Holes
    Component hole_base = Cylinder::create( SERVO_HOLE_R, SERVO_LEG_Z+0.1+_screw_length, 20, true);
    Component hole01 = hole_base.translatedCopy( SERVO_HOLE_X,   SERVO_LENGTH + SERVO_HOLE_Y, SERVO_LEG_H);
    Component hole02 = hole_base.translatedCopy( -SERVO_HOLE_X,  SERVO_LENGTH + SERVO_HOLE_Y, SERVO_LEG_H);
    Component hole03 = hole_base.translatedCopy( SERVO_HOLE_X,  -SERVO_HOLE_Y, SERVO_LEG_H);
    Component hole04 = hole_base.translatedCopy( -SERVO_HOLE_X, -SERVO_HOLE_Y, SERVO_LEG_H);

    Component holes = hole01 + hole02 + hole03 + hole04;

    //-- Final object
    Component servo;

    if (!_screw)
    servo = body + axis + leg01 + leg02 - holes;
    else
    servo = body + axis + leg01 + leg02 + holes;

    return servo;

}


*/

//-- Servo horns implementations:
//=============================================================================================

//-- Constructor:
//-----------------------------------------
Servo_Horn::Servo_Horn( int num_arms)
{
    this->num_arms = num_arms;

    //-- Set parameters depending on the number of arms of the servo horn.
    //-- For fake futaba:
    switch( num_arms )
    {
    case 0: default:
	//-- Rounded horn:
	h_top = 3;
	r_top = 20.5 / 2.0;
	h_axis = 3.5;
	r_axis = 9 / 2.0;
	//-- Not needed for rounded horn:
	arm_r = 0;
	arm_shift = 0;
	arm_dist = 0;
	break;

    case 2:
	//-- 2-arms horn:
	h_top = 3;
	r_top = 12.5 / 2.0;
	h_axis = 3;
	r_axis = 9 / 2.0;
	arm_r = 5 / 2.0;
	arm_shift = 0;
	arm_dist = 19 - 5 / 2.0;
	break;

    case 4:
	//-- 4-arms horn:
	h_top = 3;
	r_top = 13.5 / 2.0;
	h_axis = 3;
	r_axis = 9 / 2.0;
	arm_r = 4.5 / 2.0;
	arm_shift = 7;
	arm_dist = 18 - 4.5 / 2.0;
	break;

    case 6:
	//-- 6-arms horn:
	h_top = 3;
	r_top = 15 / 2.0;
	h_axis = 3;
	r_axis = 9 / 2.0;
	arm_r = 5 / 2.0;
	arm_shift = 0;
	arm_dist = (31.5 - 5) / 2.0;
	break;
    }
    rebuild();
}

Component Servo_Horn::build()
{
    //-- Create axis cylinder
      cout << "I'm running here.";
    Component horn = Cylinder::create(r_axis, h_axis +0.1, 100, false);

    if (num_arms == 0) //-- Rounded horn
    {
	Component top = Cylinder::create( r_top, h_top, 100, false);
	top = top.translate(0, 0, h_axis);
	horn = horn + top;

	//! \todo Here I should substract the cutted part if needed
    }
    else //-- Horn with arms:
    {
	//-- Create a single arm:
	Component base = Cube::create( 2*r_axis, 0.001, h_top+0.1);
	Component top_cyl = Cylinder::create( arm_r, h_top+0.1, 100, true);
	top_cyl = top_cyl.translate( 0, arm_dist, 0);

	Component arm = base.color( 1, 0, 0) & top_cyl.color(1,0,0);
	arm = arm.translate(0, 0, (h_top+0.1) /2);
	horn = horn + arm;
    }


    return horn;
}

//-- Servo rounded horn implementation:
//------------------------------------------
/*
Component Servo_Horn_rounded::build()
{
    //-- Create axis cylinder
    Component axis = Cylinder::create(ROUNDED_HORN_R_AXIS+_tol, ROUNDED_HORN_H_AXIS+0.1, 100, false);

    //-- Create top of the horn
    Component top = Cylinder::create(ROUNDED_HORN_R_TOP+_tol, ROUNDED_HORN_H_TOP, 100, false);
    top = top.translate(0, 0, ROUNDED_HORN_H_AXIS);

    //-- Add them:
    Component result = axis + top;

    //-- Substract the cut if necessary:
    if (_cutted_part != ROUNDED_HORN_R_TOP )
    {
        //-- Create a cube with the dimensions of the cut
        Component cut = Cube::create( (ROUNDED_HORN_R_TOP+_tol)- _cutted_part + 0.1, 2*(ROUNDED_HORN_R_TOP+_tol)+0.2, ROUNDED_HORN_H_TOP+0.2, false);

        //-- Center it on X:
        cut = cut.translate(0, -(ROUNDED_HORN_R_TOP+_tol)+0.1, 0);

        //-- Place it on its place (LOL) and substract it:
        result = result - cut.translate(_cutted_part + 0.1 ,0, ROUNDED_HORN_H_AXIS-0.1);
    }

    return result;
}


Component Servo_Horn_arms::build()
{

    //-- Construct axis:
    Component axis = Cylinder::create(_axis_r, _axis_h + 0.1, 100, false );

    //-- Create the arms:
    Ear arm(2*_axis_r, 0, _arm_dist, _arm_r, _top_h + 0.1);

    Component arms = arm;

    for (int i = 1; i < n; i++)
        arms = arms + arm.rotatedCopy(0,0, 360/n*i);

    arms.translate(0,0, _axis_h);

    //-- Add the upper cylinder:
    Component top_cyl = Cylinder::create(_top_r, _top_h + 0.1, 100, false)
                                 .translate(0, 0, _axis_h);

    //-- Add up all parts:
    Component result = axis + arms + top_cyl;

    return result;
}

*/
