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

#include "./base.h"
#include "./ear.h"
#include "./basic_servo.h"
#include "./servo_dimensions.h"

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

#endif //M3_SCREW

#ifndef REPY_UPPER_H
#define REPY_UPPER_H

//-- Upper part of REPY module:

class REPY_upper: public AbstractPart
{
public:
    REPY_upper();
    //-- Need to make another constructor for giving it parameters

    void showHorn( bool display_horn);
    void hornType( int type);

protected:
    virtual Component build();

private:
    //-- Parameters that define the module:

    //-- Space left around the board to protect it
    float _board_safe;

    //-- Space left around the screws for the cross-shaped hole
    float _screw_safe;

    //-- Space left around the border for the cross-shaped hole
    float _border_safe;

    //-- Thicknesses
    float _thickness_base;
    float _thickness_ear01;
    float _thickness_ear02;
    float _thickness_ear_lower01;

    //-- Display or not the servo horn
    bool _display_horn;
    int _type; //-- Horn type (see function hornType for further info)
};

#endif // REPY_UPPER_H

