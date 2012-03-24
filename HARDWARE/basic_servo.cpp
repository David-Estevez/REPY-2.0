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

Basic_servo::Basic_servo(double tol):AbstractPart() { _tol = tol;}

Component Basic_servo::Build()
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
    Component hole_base = Cylinder::create( SERVO_HOLE_R, SERVO_LEG_Z+0.1, 20, true);
    Component hole01 = hole_base.translatedCopy( SERVO_HOLE_X,   SERVO_LENGTH + SERVO_HOLE_Y, SERVO_LEG_H + SERVO_LEG_Z);
    Component hole02 = hole_base.translatedCopy( SERVO_HOLE_X,  -SERVO_HOLE_Y, SERVO_LEG_H + SERVO_LEG_Z);
    Component hole03 = hole_base.translatedCopy( -SERVO_HOLE_X, -SERVO_HOLE_Y, SERVO_LEG_H + SERVO_LEG_Z);
    Component hole04 = hole_base.translatedCopy( -SERVO_HOLE_X,  SERVO_LENGTH + SERVO_HOLE_Y, SERVO_LEG_H + SERVO_LEG_Z);
    Component holes = hole01 + hole02 + hole03 + hole04;

    //-- Final object
    Component servo = body + axis + leg01 + leg02 - holes;

    return servo;

}


