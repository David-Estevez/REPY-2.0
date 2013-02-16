//------------------------------------------------------
//-- Basic servo
//------------------------------------------------------
//-- A parametric simple servo
//-- It is used for creating the module.
//------------------------------------------------------
//-- Author: David Estevez (DEF)
//------------------------------------------------------

#include "basicservo.h"

//-- Default constructor
BasicServo::BasicServo()
{
    //-- Default horn configuration ( rounded, not shown)
    //-- horn_arms = 0;
    display_horn = false;
}

//-- Basic servo data interface:
//=============================================================================================
double BasicServo::get_width()	{   return width; }
double BasicServo::get_length(){   return length;}
double BasicServo::get_height(){   return height;}


//-- Leg dimensions:
double BasicServo::get_leg_h()	{   return leg_h; }
double BasicServo::get_leg_x() {   return leg_x; }
double BasicServo::get_leg_y()	{   return leg_y; }
double BasicServo::get_leg_z() {   return leg_z; }

//-- Leg holes
int BasicServo::get_num_holes() {  return num_holes;}
double BasicServo::get_hole_r() {  return hole_r;}
double BasicServo::get_hole_x() {  return hole_x;}
double BasicServo::get_hole_y() {  return hole_y;}

//-- Axis dimensions:
double BasicServo::get_axis_h() {  return axis_h;}
double BasicServo::get_axis_r() {  return axis_r;}
double BasicServo::get_axis_y() {  return axis_y;}

//-- Horn
bool BasicServo::horn_shown()	{   return display_horn; }
Component BasicServo::get_horn()   {	return horn; } //-- Not actually true, as it has to be placed.

//-- Servo configuration:
//----------------------------------------------------------------------------------------
void BasicServo::set_horn(int arms, bool visibility)
{
    //! \todo change this
    //horn_arms = arms;
    display_horn = visibility;

    rebuild();
}
