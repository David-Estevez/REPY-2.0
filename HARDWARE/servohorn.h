//------------------------------------------------------
//-- ServoHorn
//------------------------------------------------------
//-- A simple servo horn
//-- It is used for creating the module.
//-- New servo horns should inherit from this one.
//------------------------------------------------------
//-- Author: David Estevez (DEF)
//------------------------------------------------------

#ifndef SERVOHORN_H
#define SERVOHORN_H

#include <ooml/core.h>
#include <ooml/components.h>

class ServoHorn: public AbstractPart
{
public:
    //- - Configuration functions:
    void set_tolerance( double tol);
    void cut_horn( double cut); //-- Cut is the diameter minus the cutted part


protected:
    ServoHorn( int num_arms);

    virtual Component build();

private:
    int num_arms;
    double h_top, r_top;
    double h_axis, r_axis;
    double arm_r, arm_shift, arm_dist;
    double tol;
    double cut; //-- For cutting the round horn.
};

#endif // SERVOHORN_H
