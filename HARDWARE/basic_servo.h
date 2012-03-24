//------------------------------------------------------
//-- Basic servo
//------------------------------------------------------
//-- A parametric simple servo
//-- It is used for creating the module.
//-- Edit with the dimensions of the servo you are
//-- using.
//------------------------------------------------------
//-- Author: David Estevez (DEF)
//------------------------------------------------------

#include <ooml/core.h>
#include <ooml/components.h>

#ifndef BASIC_SERVO_H
#define BASIC_SERVO_H

//-- Definition of servo dimensions
#define SERVO_WIDTH 20
#define SERVO_LENGTH 41
#define SERVO_HEIGHT 38

#define SERVO_LEG_H 27
#define SERVO_LEG_Z 4
#define SERVO_LEG_Y 6.5
#define SERVO_LEG_X 20

#define SERVO_AXIS_H 6
#define SERVO_AXIS_Y 30
#define SERVO_AXIS_R 3

#define SERVO_HOLE_R 2
#define SERVO_HOLE_X 5
#define SERVO_HOLE_Y 4

class Basic_servo: public AbstractPart
{
public:
    Basic_servo(double tolerance = 1);

protected:
    virtual Component Build();

private:
   double _tol; //-- Value for the tolerance
};

#endif // BASIC_SERVO_H
