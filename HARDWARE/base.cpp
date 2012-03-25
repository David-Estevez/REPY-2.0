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

#include "base.h"


Base::Base(): AbstractPart()
{
    //--Default values
    _side = 52;
    _thickness = 4;
    _drill_x = 15;
    _drill_y = 15;
    _drill_r = 3/2;

    //-- Optional parameters
    _cross_small = 0;
    _cross_large = 0;

    rebuild();
}

Base::Base(double side, double thickness, double drill_x, double drill_y, double drill_r): AbstractPart()
{
    _side = side;
    _thickness = thickness;
    _drill_x = drill_x;
    _drill_y = drill_y;
    _drill_r = drill_r;

    //-- Optional parameters
    _cross_small = 0;
    _cross_large = 0;

    rebuild();
}

Component Base::build()
{
    //-- Create the main part
    Component main = Cube::create(_side, _side, _thickness);

    //--Create the holes
    Component drill01 = Cylinder::create( _drill_r, _thickness+0.1, 20, true);
    drill01.translate( _drill_x, _drill_y, 0);

    Component drill02 = Cylinder::create( _drill_r, _thickness+0.1, 20, true);
    drill02.translate( _drill_x, -_drill_y, 0);

    Component drill03 = Cylinder::create( _drill_r, _thickness+0.1, 20, true);
    drill03.translate( -_drill_x, _drill_y, 0);

    Component drill04 = Cylinder::create( _drill_r, _thickness+0.1, 20, true);
    drill04.translate( -_drill_x, -_drill_y, 0);

    Component holes = drill01 + drill02 + drill03 + drill04;

    //-- Create the cross-shaped hole
    if (_cross_small > 0 && _cross_large > 0)
    {
        Component cross01 = Cube::create(_cross_small, _cross_large, _thickness + 0.1);
        Component cross02 = Cube::create(_cross_large, _cross_small, _thickness + 0.1);
        holes = holes - cross01 - cross02;
    }

    //-- Add up all the components
    Component piece = main - holes;

    return piece;

}

//-- Add a cross-shaped hole to the base
void Base::add_cross( double small, double large)
{
    _cross_small = small;
    _cross_large = large;
    rebuild();
}

