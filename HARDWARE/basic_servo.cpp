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

//-- Basic servo implementations:
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
    leg01.translate(-SERVO_LEG_X/2, SERVO_LENGTH, SERVO_LEG_H + SERVO_LEG_Z/2);
    Component leg02 = leg01.translatedCopy(0, -(SERVO_LENGTH + SERVO_LEG_Y), 0);

    //-- Holes
    Component hole_base = Cylinder::create( SERVO_HOLE_R, SERVO_LEG_Z+0.1+_screw_length, 20, true);
    Component hole01 = hole_base.translatedCopy( SERVO_HOLE_X,   SERVO_LENGTH + SERVO_HOLE_Y, SERVO_LEG_H + SERVO_LEG_Z);
    Component hole02 = hole_base.translatedCopy( SERVO_HOLE_X,  -SERVO_HOLE_Y, SERVO_LEG_H + SERVO_LEG_Z);
    Component hole03 = hole_base.translatedCopy( -SERVO_HOLE_X, -SERVO_HOLE_Y, SERVO_LEG_H + SERVO_LEG_Z);
    Component hole04 = hole_base.translatedCopy( -SERVO_HOLE_X,  SERVO_LENGTH + SERVO_HOLE_Y, SERVO_LEG_H + SERVO_LEG_Z);
    Component holes = hole01 + hole02 + hole03 + hole04;

    //-- Final object
    Component servo;

    if (!_screw)
    servo = body + axis + leg01 + leg02 - holes;
    else
    servo = body + axis + leg01 + leg02 + holes;

    return servo;

}

//-- Servo rounded horn implementations:
Servo_Horn_rounded::Servo_Horn_rounded(double cutted_part, double tolerance)
{
    //-- Assign values
    _cutted_part = cutted_part;
    _tol = tolerance;

    rebuild();
}

Component Servo_Horn_rounded::build()
{
    //-- Create axis cylinder
    Component axis = Cylinder::create(ROUNDED_HORN_R_AXIS+_tol, ROUNDED_HORN_H_AXIS, 100, false);

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
