//------------------------------------------------------------------------------
//-- REPY module
//------------------------------------------------------------------------------
//-- This file belongs to the REPY-2.0 module project:
//--
//--	· http://www.dsquaredrobotics.com/wiki/index.php?title=REPY-2.0
//--
//--
//-- REPY-2.0 was designed using the 00ML (Object-Oriented Mechanics Library).
//-- More info about the OOML at:
//--	· http://iearobotics.com/oomlwiki/doku.php
//--
//-- REPY-2.0 concept is deeply based on Juan Gonzalez-Gomez REPY module. More
//-- info about the original REPY at:
//--	· http://www.thingiverse.com/thing:13442
//--	· http://www.iearobotics.com/wiki/index.php?title=M%C3%B3dulos_REPY-1
//--
//------------------------------------------------------------------------------
//-- Author: David Estevez (DEF)
//--
//-- Released under the GPL license (more info on LICENSE.txt file)
//------------------------------------------------------------------------------

/*! \file repy_module.h
 *  \brief Mechanic module for modular robots.
 *
 *  This module accepts a BasicServo object and a BasicSquaredPCB object and
 *  generates a REPY module according to their dimensions.
 *
 * \author David Estévez Fernández ( http://github.com/David-Estevez )
 * \date Mar 2nd, 2013
 *
 */


#ifndef REPY_MODULE_H
#define REPY_MODULE_H

#include <ooml/core.h>
#include <ooml/components.h>

#include "servos/basicservo.h"
#include "boards/basicsquaredpcb.h"

/*! \class REPY_module
 *  \brief Mechanic module for modular robots.
 *
 *  This module accepts a BasicServo object and a BasicSquaredPCB object and
 *  generates a REPY module according to their dimensions.
 *
 */
class REPY_module : public AbstractPart
{
public:
    /*! \brief Constructor
     *
     *  Takes a BasicServo and a BasicSquaredPCB and generates the module parameters.
     *
     *  \param servo A BasicServo object
     *  \param pcb A BasicSquaredPCB object
     */
    REPY_module(BasicServo& servo,  BasicSquaredPCB& pcb);

protected:

    //! \brief Builds the REPY module
    virtual Component build();

private:
    Component lower_part();
    Component upper_part();
    Component make_ear( double base, double height, double thickness, double shift, double radius);

    //-- Needed components that define the module:
    BasicServo * servo;
    BasicSquaredPCB * pcb;
    Component fake_axis, fake_axis_with_tol;

    //-- Needed dimensions
    //--------------------------------------------
    //-- General:
    double board_safe;

    //-- Lower part:
    double lower_base_thickness;
    double lower_front_ear_thickness;
    double lower_back_ear_thickness;
    double lower_ear_shift;
    double lower_ear_radius;
    double lower_screw_safe;
    double lower_border_safe;

    //-- Upper part:
    double upper_base_thickness;
    double upper_front_ear_thickness;
    double upper_back_ear_thickness;
    double upper_ear_shift;
    double upper_ear_radius;
    double upper_screw_safe;
    double upper_border_safe;

    //-- Tolerances:
    double body_servo_x_tol;	//-- Clearance to insert the servo, x axis
    double body_servo_y_tol;	//-- Clearance to insert the servo, y axis
    double ear_clearance_tol;	//-- Clearance between touching ears
    double fake_axis_tol;	//-- Clearance for the fake axis

    //-- Visibility flags:
    bool show_servo;
    bool show_assembly; //-- (show assembly/print)
    bool show_lower;	//-- (show lower part)
    bool show_upper;	//-- (show upper part)

    //-- Dimensions calculated automatically by the software:
    double side;
    double central_part;
};

#endif // REPY_MODULE_H
