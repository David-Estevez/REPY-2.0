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
    //-- Constructor
    Basic_servo(bool screw = false, double screw_length = 0, double tolerance = 0);

protected:
    virtual Component build();

private:
   double _tol; //-- Value for the tolerance
   bool _screw; //-- If true, it shows the screws
   double _screw_length; //-- Screw thickness
};

#endif // BASIC_SERVO_H




#ifndef SERVO_HORNS_CLASS
#define SERVO_HORNS_CLASS

//-- Definition of rounded horn dimensions:
#define ROUNDED_HORN_R_TOP 25/2.0
#define ROUNDED_HORN_H_TOP 2

#define ROUNDED_HORN_R_AXIS 9/2.0
#define ROUNDED_HORN_H_AXIS 3

class Servo_Horn_rounded: public AbstractPart
{
public:
    //-- Constructor
    Servo_Horn_rounded(double cutted_part = ROUNDED_HORN_R_TOP, double tolerance = 0);

protected:
    virtual Component build();

private:
    double _tol; //-- Value for the tolerance
    double _cutted_part; //-- Value for the distance between the center and the cut of the horn
};

/*class Servo_Horm_arms: public AbstractPart
{
public:
    //--Constructor
    Servo_Horm_arms( int num_arms, );
};*/

#endif // SERVO_HORNS_CLASS
