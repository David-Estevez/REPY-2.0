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
    _thickness_upper01 = 4;

    //-- Base holes:
    _dist_border = 7;
    _dist_drill = 4;

    //-- Ear parameters
    _ear_radius = 38/2;
    _ear_shift = 12;

    //-- Don't render the servo by default:
    _servo_enabled = false;


    rebuild();
}

Component REPY_lower::build()
{
    //--Create the module itself:
    //---------------------------------

    //-- Create the base
    Base base(SIDE_BOARD + 2*_board_safe, _thickness_base, DRILL_X/2, DRILL_Y/2, DRILL_D/2.0);

    //-- Make holes in the base for wiring, etc
    //-- Hole01: under the servo, between the ears, for wiring, etc
    Component hole01 = Cube::create(SIDE_BOARD + 2*_board_safe - 2* _dist_border,
                                    ( _thickness_ear01 + _thickness_upper01 + SERVO_LEG_H - _thickness_ear02)-(SIDE_BOARD/2 + _board_safe - DRILL_Y/2 + DRILL_D/2 + _dist_drill),
                                    _thickness_base + 0.2, false );

    hole01.translate( -(SIDE_BOARD/2 + _board_safe - _dist_border),
                      -DRILL_Y/2 + DRILL_D/2 + _dist_drill,
                      -(_thickness_base+0.2) /2);

    //-- Hole02: under the servo leg, to save material
    Component hole02 = Cube::create( SERVO_LEG_X,
                                     (SIDE_BOARD + 2*_board_safe)-( _thickness_ear01 + _thickness_upper01 + SERVO_LEG_H + SERVO_LEG_Z + _dist_border),
                                     _thickness_base + 0.2, false);

    hole02.translate( - SERVO_LEG_X / 2,
                      -(SIDE_BOARD/2 + _board_safe) + _thickness_ear01 + _thickness_upper01 + SERVO_LEG_H + SERVO_LEG_Z,
                      -(_thickness_base+0.2)/2);

    Component base_w_holes = base - hole01-hole02.color(255, 0, 0, 0.25);

    //-- Create the servo object to substract
    Basic_servo servo(true, 2 * _thickness_ear01);
    servo.color(0.25,0.25,0.25);
    servo.rotate(90, 0, 180);
    servo.translate( 0, -((SIDE_BOARD+2*_board_safe)/2 - 2 * _thickness_ear01), SERVO_LEG_Y + _thickness_base/2);


    //-- Create first ear
    Ear ear01(SIDE_BOARD , _ear_shift, SERVO_AXIS_Y + SERVO_LEG_Y, _ear_radius, _thickness_ear01); // -y ear (false axis)
    ear01.add_drill( M3 +0.1, M3_HEAD + 0.1, M3_HEAD_H);
    ear01.rotate(90, 0, 0);
    ear01.rotate(0,0,180);
    ear01.translate(0, - ((SIDE_BOARD+2*_board_safe)/2 - _thickness_ear01), _thickness_base/2 -0.2);

    //-- Create second ear
    Ear ear02(SIDE_BOARD, _ear_shift, SERVO_AXIS_Y + SERVO_LEG_Y, _ear_radius, _thickness_ear02); // +y ear (supports the servo)
    ear02.rotate(90,0,0);
    ear02.translate(0, SERVO_LEG_H + /*SERVO_LEG_Z/2*/ - ((SIDE_BOARD+2*_board_safe)/2 -  _thickness_ear01 - _thickness_upper01 ), _thickness_base/2 -0.2);

    //-- Add up all things
    Component result = base_w_holes + ear01 + ear02 - servo;

    //-- If desired, show the servo
    if (_servo_enabled)
        result = result + servo;

    return result;
}

void REPY_lower::showServo(bool enable)
{
    //-- Update the variable _servo_enabled:
    _servo_enabled = enable;

    rebuild();
}
