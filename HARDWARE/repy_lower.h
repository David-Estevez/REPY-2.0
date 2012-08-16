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

#define M3 3/2.0
#define M3_HEAD 4.5/2.0
#define M3_HEAD_H 2

#ifndef REPY_LOWER_H
#define REPY_LOWER_H

#endif //M3_SCREW

//-- Lower part of REPY module:

class REPY_lower: public AbstractPart
{
public:
    REPY_lower();

    void showServo(bool enable);

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
    float _thickness_upper01; //-- Needed for ear placement

    //-- Base holes:
    float _dist_border;
    float _dist_drill;

    //-- Ear parameters
    float _ear_radius;
    float _ear_shift;

    //-- Other parameters
    //-- Show/don't show the servo on the model
    bool _servo_enabled;
};

#endif // REPY_LOWER_H
