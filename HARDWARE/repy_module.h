//------------------------------------------------------
//-- REPY-2.0
//------------------------------------------------------
//
//------------------------------------------------------
//-- Author: David Estevez (DEF)
//------------------------------------------------------
//-- Based on REPY module, by
//-- Juan Gonzalez-Gomez (Obijuan)
//------------------------------------------------------

#include <ooml/core.h>
#include <ooml/components.h>

#include "basic_servo.h"
#include "skymegaboard.h"

#ifndef REPY_MODULE_H
#define REPY_MODULE_H

class REPY_module : public AbstractPart
{
public:
    REPY_module(Basic_Servo& servo,  SkyMegaBoard& skymega);

protected:
    virtual Component build();

private:
    Component lower_part();
    Component upper_part();
    Component make_ear( double base, double height, double thickness, double shift, double radius);

    //-- Needed components that define the module:
    Basic_Servo * servo;
    SkyMegaBoard * skymega;

    //-- Needed dimensions
    //--------------------------------------------
    //-- General:
    double board_safe;
    double side;

    //-- Lower part:
    double lower_base_thickness;
    double lower_front_ear_thickness;
    double lower_back_ear_thickness;
    double lower_ear_shift;
    double lower_ear_radius;

    //-- Upper part:
    double upper_base_thickness;
    double upper_front_ear_thickness;
    double upper_back_ear_thickness;
    double upper_ear_shift;
    double upper_ear_radius;

    //-- Visibility flags:
    bool show_servo;
    bool show_assembly; //-- (show assembly/print)
    bool show_lower;	//-- (show lower part)
    bool show_upper;	//-- (show upper part)

};

#endif // REPY_MODULE_H
