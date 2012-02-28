#include <ooml/core.h>
#include <ooml/components.h>

#include "base.h"


Component Base::build()
{
    //-- Create the main part
    Component main = Cube::create(_side, _side, _thickness);

    //-- Create the cross-shaped hole
    Component cross01 = Cube::create(_cross_small, _cross_large, _thickness + 0.1);
    Component cross02 = Cube::create(_cross_large, _cross_small, _thickness + 0.1);

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

    //-- Add up all the components
    Component piece = main - cross01 - cross02 - holes;

    return piece;

}

