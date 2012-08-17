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

    //-- Space left around the screws for the cross-shaped hole
    _screw_safe = 5;

    //-- Space left around the border for the cross-shaped hole
    _border_safe = 7;

    //-- Thicknesses
    _thickness_base = 4;
    _thickness_ear01 = 4;               //-- y- (false axis)
    _thickness_ear02 = 5.5;               //-- y+ (servo horn)
    _thickness_ear_lower01 = 4;         //-- Needed for placement of y+ ear

    //-- Servo horn not shown by default
    _display_horn = false;
    _type = 0;

    rebuild();
}

Component REPY_upper::build()
{
    //-- Base:
    Base  base( SIDE_BOARD + 2*_board_safe, _thickness_base, DRILL_X/2, DRILL_Y/2, DRILL_D/2.0);
    base.add_cross( DRILL_X - DRILL_D - 2 * _screw_safe , SIDE_BOARD + 2 * _board_safe - 2 * _border_safe  );

    //-- Ears:
    Ear ear01( SIDE_BOARD , 12, SERVO_AXIS_Y + SERVO_LEG_Y, 38/2, _thickness_ear01); // -y ear
    ear01.add_drill( M3 + 0.1 );
    ear01.rotate(90, 0, 180)
         .translate(0, -(SIDE_BOARD/2 + _board_safe), _thickness_base/2);

    Ear ear02( SIDE_BOARD , 12, SERVO_AXIS_Y + SERVO_LEG_Y, 38/2, _thickness_ear02); // +y ear
    ear02.add_drill( M3 + 0.1 );
    ear02.rotate(90, 0, 180)
         .translate(0,-(SIDE_BOARD/2 + _board_safe), _thickness_base/2)
         .translate(0, _thickness_ear01 + _thickness_ear_lower01 + SERVO_HEIGHT, 0 );

    //-- Add up everything:
    Component result = base + ear01 + ear02;

    //-- Horn hole
    if ( _type == 1)
    {
        //-- Cutted rounded horn
        Servo_Horn_rounded horn( ROUNDED_HORN_R_TOP - 3, 0.1);
        horn.rotate(-90,0,0).rotate(0,90,0)
            .translate(0, -(SIDE_BOARD/2.0 + _board_safe + 0.1) , SERVO_AXIS_Y + SERVO_LEG_Y +_thickness_base/2)
            .translate(0, _thickness_ear01 + _thickness_ear_lower01 + SERVO_HEIGHT, 0 );

        result = result - horn;

        if (_display_horn)
           result = result + horn.color(0.25,0.25,0.25);
      }

    if ( _type == 2)
    {
        //-- 2 arms horn
        Servo_Horn_arms horn (2);
        horn.rotate(-90,0,0)
                .translate(0, -(SIDE_BOARD/2.0 + _board_safe + 0.1) , SERVO_AXIS_Y + SERVO_LEG_Y +_thickness_base/2)
                .translate(0, _thickness_ear01 + _thickness_ear_lower01 + SERVO_HEIGHT, 0 );

        result = result - horn;

        if (_display_horn)
            result = result + horn.color(0.25,0.25,0.25);}

     if ( _type == 4)
     {
         //-- 4 arms horn
         Servo_Horn_arms horn (4);
         horn.rotate(-90,0,0)
                 .translate(0, -(SIDE_BOARD/2.0 + _board_safe + 0.1) , SERVO_AXIS_Y + SERVO_LEG_Y +_thickness_base/2)
                 .translate(0, _thickness_ear01 + _thickness_ear_lower01 + SERVO_HEIGHT, 0 );

         result = result - horn;

         if (_display_horn)
             result = result + horn.color(0.25,0.25,0.25);
     }

     if ( _type == 6)
     {
         //-- 6 arms horn
        Servo_Horn_arms horn (6);
        horn.rotate(-90,0,0)
                .translate(0, -(SIDE_BOARD/2.0 + _board_safe + 0.1) , SERVO_AXIS_Y + SERVO_LEG_Y +_thickness_base/2)
                .translate(0, _thickness_ear01 + _thickness_ear_lower01 + SERVO_HEIGHT, 0 );

        result = result - horn;

        if (_display_horn)
            result = result + horn.color(0.25,0.25,0.25);
      }

    return result;
}

void REPY_upper::showHorn( bool display_horn)
{
    //-- Update the variable _display_horn
    _display_horn = display_horn;

    rebuild();
}

void REPY_upper::hornType(int type)
{
    //-- Choose type of horn:
    //----------------------------
    //-- 0: don't make horn hole
    //-- 1: cutted rounded horn
    //-- 2: two arms horn
    //-- 4: four arms horn
    //-- 6: six arms horn
    //----------------------------

    if (type < 0 || type > 6 || type == 3 || type == 5)
        _type = 0;
    else
        _type = type;

    rebuild();
}

