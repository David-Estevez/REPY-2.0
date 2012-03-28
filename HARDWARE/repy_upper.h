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

#include <base.h>
#include <ear.h>
#include <basic_servo.h>

//-- This parameters depend on the board that we want to use.

//-- For skymega:
#ifndef SKYMEGA_BOARD
#define SKYMEGA_BOARD

#define SIDE_BOARD 52
#define DRILL_X 30
#define DRILL_Y 30
#define DRILL_D 3

#endif //SKYMEGA_BOARD

//-- M3 screw parameters
#ifndef M3_SCREW
#define M3_SCREW

#define M3 3/2
#define M3_HEAD 4.5/2
#define M3_HEAD_H 2

#ifndef REPY_LOWER_H
#define REPY_LOWER_H

#endif //M3_SCREW

//-- Upper part of REPY module:

class REPY_upper: public AbstractPart
{
public:
    REPY_upper();
    //-- Need to make another constructor for giving it parameters

protected:
    virtual Component build();

private:
    //-- Parameters that define the module:

    //-- Space left around the board to protect it
    float _board_safe;

    //-- Thicknesses
    float _thickness_base;
    float _thickness_ear01;
    float _thickness_ear02;

};

#endif // REPY_UPPER_H
