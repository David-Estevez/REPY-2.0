// Base for REPY module
// Author: David Estévez (DEF)

#include <ooml/core.h>
#include <ooml/components.h>
#include <iostream>
#include <fstream>

struct Base
{
    double side;
    double thickness;
    double drill_x;
    double drill_y;
    double drill_r;
    double cross_small;
    double cross_large;
};

int main()
{
    struct Base base = {52, 4, 15, 15, 3/2, 40, 20};
    IndentWriter writer;

    Component contour = Cube::create(base.side, base.side, base.thickness);

    Component cross01 = Cube::create(base.cross_small, base.cross_large, base.thickness + 0.1);
    Component cross02 = Cube::create(base.cross_large, base.cross_small, base.thickness + 0.1);

    Component drill01 = Cylinder::create( base.drill_r, base.thickness+0.1, 20, true);
    drill01.translate( base.drill_x, base.drill_y, 0);

    Component drill02 = Cylinder::create( base.drill_r, base.thickness+0.1, 20, true);
    drill02.translate( base.drill_x, -base.drill_y, 0);

    Component drill03 = Cylinder::create( base.drill_r, base.thickness+0.1, 20, true);
    drill03.translate( -base.drill_x, base.drill_y, 0);

    Component drill04 = Cylinder::create( base.drill_r, base.thickness+0.1, 20, true);
    drill04.translate( -base.drill_x, -base.drill_y, 0);

    Component holes = drill01 + drill02 + drill03 + drill04;

    Component foot = contour - cross01 - cross02 - holes;

    writer << foot;
    std::cout << writer;

    return 0;

}
