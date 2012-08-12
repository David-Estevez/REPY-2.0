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
    _type = 0;

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

    //-- Add up everything:
    Component result = base + ear01 + ear02;

    //-- Horn hole
    if ( _type == 1)
    {
        //-- Cutted rounded horn
        Servo_Horn_rounded horn( ROUNDED_HORN_R_TOP - 3, 0.1);
        horn.rotate(-90,0,0).rotate(0,90,0)
            .translate(0, -(ROUNDED_HORN_H_TOP + ROUNDED_HORN_H_AXIS),0)
            .translate(0, SIDE_BOARD/2.0 + _board_safe + 0.1 , SERVO_AXIS_Y + SERVO_LEG_Y +_thickness_base/2);

        result = result - horn;

        if (_display_horn)
           result = result + horn.color(0,0,0);
      }

    if ( _type == 2)
    {
        //-- 2 arms horn
        Servo_Horn_arms horn (2);
        horn.rotate(-90,0,0)
            .translate(0, - (HORN_2_ARMS_TOP_H+HORN_2_ARMS_AXIS_H), 0)
            .translate(0, SIDE_BOARD/2.0 + _board_safe + 0.1 , SERVO_AXIS_Y + SERVO_LEG_Y +_thickness_base/2);

        result = result - horn;

        if (_display_horn)
            result = result + horn.color(0,0,0);}

     if ( _type == 4)
     {
         //-- 4 arms horn
         Servo_Horn_arms horn (4);
         horn.rotate(-90,0,0)
             .translate(0, - (HORN_4_ARMS_TOP_H+HORN_2_ARMS_AXIS_H), 0)
             .translate(0, SIDE_BOARD/2.0 + _board_safe + 0.1 , SERVO_AXIS_Y + SERVO_LEG_Y +_thickness_base/2);

         result = result - horn;

         if (_display_horn)
             result = result + horn.color(0,0,0);
     }

     if ( _type == 6) //-- 6 arms horn
     {
        Servo_Horn_arms horn (6);
        horn.rotate(-90,0,0)
            .translate(0, - (HORN_6_ARMS_TOP_H+HORN_2_ARMS_AXIS_H), 0)
            .translate(0, SIDE_BOARD/2.0 + _board_safe + 0.1 , SERVO_AXIS_Y + SERVO_LEG_Y +_thickness_base/2);

        result = result - horn;

        if (_display_horn)
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

