//------------------------------------------------------
//-- Basic servo
//------------------------------------------------------
//-- A parametric simple servo
//-- It is used for creating the module.
//-- Edit with the dimensions of the servo you are
//-- using.
//------------------------------------------------------
//-- Author: David Estevez (DEF)
//------------------------------------------------------

#include <ooml/core.h>
#include <ooml/components.h>

#include "servo_dimensions.h"

#ifndef BASIC_SERVO_H
#define BASIC_SERVO_H

//-- Basic Servo definitions:
//=============================================================================

class Basic_Servo: public AbstractPart
{
public:
    //-- Object dimensions interface:
    //---------------------------------------
    //-- Main dimensions:
    double get_width();
    double get_length();
    double get_height();


    //-- Leg dimensions:
    double get_leg_h();
    double get_leg_x();
    double get_leg_y();
    double get_leg_z();

    //-- Axis dimensions:
    double get_axis_h();
    double get_axis_r();
    double get_axis_y();

    //-- Horn
    bool horn_shown();
    Component get_horn();

protected:
    Basic_Servo();
    virtual Component build() = 0;

private:
    //-- Servo characteristics:
    //---------------------------------------
    //-- Main dimensions:
    double width, length, height;

    //-- Leg dimensions:
    double leg_h, leg_x, leg_y, leg_z;

    //-- Leg holes
    int num_holes;
    double  hole_r, hole_x, hole_y;

    //-- Screws
    // (I think here I should put the reference to the holes of the drills)

    //-- Axis dimensions:
    double axis_h, axis_r, axis_y;

    //-- Horn
    bool display_horn;
    int horn_legs;

};

class Servo_Horn: public AbstractPart
{
public:
	/* Data interface?? */

    Servo_Horn( int num_arms);

protected:
    virtual Component build();

private:
    int num_arms;
    double h_top, r_top;
    double h_axis, r_axis;
    double arm_r, arm_shift, arm_dist;
};

/*
class Basic_servo: public AbstractPart
{
public:
    //-- Constructor
    Basic_servo(bool screw = false, double screw_length = 0, double tolerance = 0);

protected:
    virtual Component build();

private:
   double _tol; //-- Value for the tolerance
   bool _screw; //-- If true, it shows the screws
   double _screw_length; //-- Screw thickness
};



//-- Servo horn definitions
//=========================================================================


class Servo_Horn_rounded: public AbstractPart
{
public:
    //-- Constructor
    Servo_Horn_rounded(double cutted_part = ROUNDED_HORN_R_TOP, double tolerance = 0);

protected:
    virtual Component build();

private:
    double _tol; //-- Value for the tolerance
    double _cutted_part; //-- Value for the distance between the center and the cut of the horn
};


class Servo_Horn_arms: public AbstractPart
{
public:
    //--Constructor:
    Servo_Horn_arms( int number_arms, double tolerance = 0);
    Servo_Horn_arms( int number_arms, double axis_h, double axis_r, double top_h, double top_r,
                     double arm_r, double arm_shift, double arm_dist, double tolerance = 0);

protected:
    virtual Component build();

private:
    //-- Parameters:
    int n; //-- Number of arms

    double _axis_h; //-- Axis height/thickness
    double _axis_r; //-- Axis radius

    double _top_h;  //-- Top cylinder height/thickness
    double _top_r;  //-- Top cylinder radius

    double _arm_r;  //-- Radius of the rounded part at the end of arm
    double _arm_shift;
    double _arm_dist; //-- Distance between center of top cylinder and center of arm cylinder

    double _tol; //-- Tolerance

};

*/
#endif // BASIC_SERVO_H
