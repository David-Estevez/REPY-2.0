#include <ooml/core.h>
#include <ooml/components.h>

#ifndef BASE_H
#define BASE_H

class Base: public Component
{
public:
    Base(): Component(), _side(52), _thickness(4), _drill_x(15), _drill_y(15), _drill_r(3/2), _cross_small(40), _cross_large(20) { build();}
    Base(double side, double thickness, double drill_x, double drill_y, double drill_r):
            Component(), _side(side), _thickness(thickness),
            _drill_x(drill_x), _drill_y(drill_y), _drill_r(drill_r),
            _cross_small(0), _cross_large(0) { build(); }

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
