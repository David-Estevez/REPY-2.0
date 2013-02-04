//------------------------------------------------------
//-- Basic servo
//------------------------------------------------------
//-- A simple servo
//-- It is used for creating the module.
//-- New servo component should inherit from this one.
//------------------------------------------------------
//-- Author: David Estevez (DEF)
//------------------------------------------------------

#include <ooml/core.h>
#include <ooml/components.h>

#include "servo_dimensions.h"

#ifndef BASIC_SERVO_H
#define BASIC_SERVO_H


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

    //-- Servo configuration:
    //-----------------------------------------------------------------
    void set_horn( int arms, bool visibility);

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
    int horn_arms;

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

#endif // BASIC_SERVO_H
