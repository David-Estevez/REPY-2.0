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
    //-- Default horn configuration ( rounded, not shown)
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

    rebuild();
}

//-- Servo horns implementations:
//=============================================================================================

//-- Constructor:
//-----------------------------------------
Servo_Horn::Servo_Horn( int num_arms)
{
    this->num_arms = num_arms;
    tol = 0;
    cut = 0;

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

void Servo_Horn::set_tolerance(double tol)
{
    this->tol = tol;
    rebuild();
}

void Servo_Horn::cut_horn(double cut)
{
    this->cut = cut;
    rebuild();
}

Component Servo_Horn::build()
{
    //-- Create axis cylinder
    Component horn = Cylinder::create(r_axis+tol, h_axis +0.1, 100, false);

    if (num_arms == 0) //-- Rounded horn
    {
	Component top = Cylinder::create( r_top+tol, h_top, 100, false);
	top.translate(0, 0, h_axis);
	horn = horn + top;

	if ( cut < r_top )
	{
	    //-- Create a cube with the dimensions of the cut
	    Component to_be_substracted = Cube::create( (r_top+tol)- cut + 0.1, 2*(r_top+tol)+0.2, h_top+0.2, false);

	    //-- Center it on Y:
	    to_be_substracted.translate(0, -(r_top+tol)+0.1, 0);

	    //-- Place it on its place (LOL) and substract it:
	    horn = horn - to_be_substracted.translate( cut + 0.1 ,0, h_axis-0.1);
	 }
    }
    else //-- Horn with arms:
    {
	//-- Create a single arm:
	Component base = Cube::create( 2*r_axis, 0.001, h_top+0.1);
	Component upper_cyl = Cylinder::create( arm_r, h_top+0.1, 100, true);
	upper_cyl = upper_cyl.translate( 0, arm_dist, 0);

	Component arm = base.color( 1, 0, 0) & upper_cyl.color(1,0,0);
	arm.translate(0, 0, (h_top+0.1) /2);

	//-- Create the orher arms by rotation:
	Component arms = arm;
	for ( int i = 1; i < num_arms; i++)
	    arms = arms + arm.rotatedCopy(0,0, 360/num_arms*i);
	arms.translate( 0, 0, h_axis);

	//-- Add the top cylinder:
	Component top_cyl = Cylinder::create( r_top, h_top + 0.1, 100, false)
			    .translate(0,0, h_axis);

	//-- Sum up all the parts:
	horn = horn + arms + top_cyl;
    }

    //-- Set link on the end of the axis cylinder, to attach to the servo:
    horn.addLink( RefSys( 0,0, h_axis));

    cout << horn.links()->size();
    return horn;
}
