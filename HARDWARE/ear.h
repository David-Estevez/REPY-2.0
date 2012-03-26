
//------------------------------------------------------
//-- REPY-2.0
//------------------------------------------------------
//-- This component is the 'ear' of a REPY module.
//-- It is completely parametric, so one can build
//-- a module to fit their own needs.
//-- There are several configurations available,
//-- including reinforced 'ear'.
//------------------------------------------------------
//-- Author: David Estevez (DEF)
//------------------------------------------------------
//-- Based on REPY module, by
//-- Juan Gonzalez-Gomez (Obijuan)
//------------------------------------------------------

#include <ooml/core.h>
#include <ooml/components.h>

#ifndef EAR_H
#define EAR_H

class Ear: public AbstractPart
{
public:
    //-- Constructor
    Ear();
    Ear( double base, double shift, double height, double horn_r, double thickness);

    //-- Adds a hole for the axis
    void add_drill( double radius, double radius_big = -1, double screw_head = 0);

    //-- Adds a reinforcement to the module
    void add_reinforcement( double thickness);

protected:
    virtual Component build();

private:
    double _base;
    double _shift;
    double _height;
    double _horn_r;
    double _thickness;
    //--Optional parameters
    double _drill_r;
    double _drill_r_big;
    double _reinf_thickness;
    double _screw_head;

};

#endif // EAR_H
