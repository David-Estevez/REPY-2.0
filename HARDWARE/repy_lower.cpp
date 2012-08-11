//------------------------------------------------------
//-- REPY-2.0
//------------------------------------------------------
//-- This is the lower part of a REPY module.
//-- It is completely parametric, so one can build
//-- a module to fit their own needs.
//------------------------------------------------------
//-- Author: David Estevez (DEF)
//------------------------------------------------------
//-- Based on REPY module, by
//-- Juan Gonzalez-Gomez (Obijuan)
//------------------------------------------------------

#include <ooml/core.h>
#include <ooml/components.h>

#include "repy_lower.h"

REPY_lower::REPY_lower():AbstractPart()
{
    //-- Initialize parameters to be used:

    //-- Space left around the board to protect it
    _board_safe = 1.5;

    //-- Thicknesses
    _thickness_base = 4;
    _thickness_ear01 = 4;
    _thickness_ear02 = 4;

    rebuild();
}

Component REPY_lower::build()
{
    //--Create the module itself:
    //---------------------------------

    //-- Create the base
    Base base(SIDE_BOARD + 2*_board_safe, _thickness_base, DRILL_X/2, DRILL_Y/2, DRILL_D/2.0);

    //-- Create the servo object to substract
    Basic_servo servo(true, 2 * _thickness_ear01);
    servo.color(0.25,0.25,0.25);
    servo.rotate(90, 0, 180);
    servo.translate( 0, -((SIDE_BOARD+2*_board_safe)/2 - 2 * _thickness_ear01), SERVO_LEG_Y + _thickness_base/2);


    //-- Create first ear
    Ear ear01(SIDE_BOARD , 12, SERVO_AXIS_Y + SERVO_LEG_Y, 38/2, _thickness_ear01);
    ear01.add_drill( M3 +0.1, M3_HEAD + 0.1, M3_HEAD_H);
    ear01.rotate(90, 0, 0);
    ear01.rotate(0,0,180);
    ear01.translate(0, - ((SIDE_BOARD+2*_board_safe)/2 - _thickness_ear01), _thickness_base/2-0.2);

    //-- Create second ear
    Ear ear02(SIDE_BOARD, 12, SERVO_AXIS_Y + SERVO_LEG_Y, 38/2, _thickness_ear02);
    ear02.rotate(90,0,0);
    ear02.translate(0, SERVO_LEG_H + SERVO_LEG_Z/2 - ((SIDE_BOARD+2*_board_safe)/2 - 2 * _thickness_ear01),-0.2+ _thickness_base/2);

    //-- Add up all things
    Component result = base + ear01 + ear02 - servo;

    return result;
}
