#include <ooml/core.h>
#include <ooml/components.h>

#ifndef EAR_H
#define EAR_H

class Ear: public Component
{
public:
    Ear(); // : Component(), _base(50), _shift(10), _height(50), _corona_r(25/2),_drill_r(0), _thickness(4), _reinf_thickness(0) { build();}
    Ear( double base, double shift, double height, double corona_r, double thickness);
    //-- Adds an hole for the axis
    void add_drill( double radius, double radius_big = -1);
    void add_reinforcement( double thickness);

//protected:
    virtual Component build();

private:
    double _base;
    double _shift;
    double _height;
    double _corona_r;
    double _thickness;
    //--Optional parameters
    double _drill_r;
    double _drill_r_big;
    double _reinf_thickness;

};

#endif // EAR_H
