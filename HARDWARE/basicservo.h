//------------------------------------------------------
//-- Basic servo
//------------------------------------------------------
//-- A simple servo
//-- It is used for creating the module.
//-- New servo component should inherit from this one.
//------------------------------------------------------
//-- Author: David Estevez (DEF)
//------------------------------------------------------

#ifndef BASIC_SERVO_H
#define BASIC_SERVO_H

#include <ooml/core.h>
#include <ooml/components.h>

#include "servohorn.h"

class BasicServo: public AbstractPart
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

    //-- Leg holes
    int get_num_holes();
    double get_hole_r();
    double get_hole_x();
    double get_hole_y();

    //-- Axis dimensions:
    double get_axis_h();
    double get_axis_r();
    double get_axis_y();

    //-- Horn
    bool horn_shown();
    Component get_horn();

    //-- Servo configuration:
    //-----------------------------------------------------------------
    void set_horn( int arms, bool visibility = true);

protected:
    BasicServo();

    virtual Component build() = 0;

    //-- Servo characteristics:
    //---------------------------------------
    //-- Main dimensions:
    double width, length, height;

    //-- Leg dimensions:
    double leg_h, leg_x, leg_y, leg_z;

    //-- Leg holes
    int num_holes;
    double  hole_r, hole_x, hole_y;

    //-- Axis dimensions:
    double axis_h, axis_r, axis_y;

    //-- Horn
    Component horn;

    bool display_horn;
};


#endif // BASIC_SERVO_H
