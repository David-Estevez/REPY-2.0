//------------------------------------------------------
//-- REPY-2.0
//------------------------------------------------------
//-- This component is the base of a REPY module.
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

#ifndef BASE_H
#define BASE_H

class Base: public Component
{
public:
    //-- Constructor
    Base();
    Base(double side, double thickness, double drill_x, double drill_y, double drill_r);

    //--Add a cross-shaped hole to the base of the module
    void add_cross( double small, double large);

//protected:
    virtual Component build();

private:
    /*Main parameters*/
    double _side;
    double _thickness;
    double _drill_x;
    double _drill_y;
    double _drill_r;

    /*For the optional cross hole*/
    double _cross_small;
    double _cross_large;

};

#endif // BASE_H
