//------------------------------------------------------
//-- REPY-2.0
//------------------------------------------------------
//-- This is the upper part of a REPY module.
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

#include "repy_upper.h"

REPY_upper::REPY_upper(): AbstractPart()
{
    //-- Initialize parameters to be used:

    //-- Space left around the board to protect it
    _board_safe = 1.5;

    //-- Thicknesses
    _thickness_base = 4;
    _thickness_ear01 = 4;
    _thickness_ear02 = 4;

    //-- Servo horn not shown by default
    _display_horn = false;

    rebuild();
}

Component REPY_upper::build()
{
    //-- Base:
    Base  base( SIDE_BOARD + 2*_board_safe, _thickness_base, DRILL_X/2, DRILL_Y/2, DRILL_D/2.0);

    //-- Ears:
    Ear ear01( SIDE_BOARD , 12, SERVO_AXIS_Y + SERVO_LEG_Y, 38/2, _thickness_ear01);
    ear01.add_drill( M3 + 0.1 );
    ear01.rotate(90, 0, 0);
    Component ear02 = ear01.translatedCopy(0,- ((SIDE_BOARD + 2*_board_safe)/2 - _thickness_ear01), _thickness_base/2);
    ear01.translate(0,(SIDE_BOARD + 2*_board_safe)/2, _thickness_base/2);

    //-- Horn hole
    Servo_Horn_rounded horn(25/2.0 - 3, 0.1);
    horn.rotate(-90,0,0)
        .rotate(0,-90,0)
            .translate(0, -(ROUNDED_HORN_H_TOP+ROUNDED_HORN_H_AXIS),0)
        .translate(0, SIDE_BOARD/2.0 + _board_safe + 0.1 ,SERVO_AXIS_Y+SERVO_LEG_Y+_thickness_base/2);

    //-- Add up everything:
    Component result = base + ear01 + ear02 - horn;

    if (_display_horn)
    {
        result = result + horn.color(0,0,0);
    }

    return result;
}

void REPY_upper::showHorn( bool display_horn)
{
    //-- Update the variable _display_horn
    _display_horn = display_horn;

    rebuild();
}
