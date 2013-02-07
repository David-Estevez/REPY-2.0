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

#ifndef REPY_MODULE_H
#define REPY_MODULE_H

class REPY_module : public AbstractPart
{
public:
    REPY_module(const Basic_Servo& servo);

protected:
    virtual Component build();

private:
    Component lower_part();
    Component upper_part();


    Basic_Servo * servo;

    //-- Visibility flags:
    bool show_servo;
    bool show_assembly; //-- (show assembly/print)
    bool show_lower;	//-- (show lower part)
    bool show_upper;	//-- (show upper part)

};

#endif // REPY_MODULE_H
