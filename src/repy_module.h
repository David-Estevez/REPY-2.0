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
 * \date Apr 1st, 2013
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



    //-- Configuring the module:
    //--------------------------------------------------------------------------------
    /*! \brief Configure how the module will be shown
     *
     *	\param show_servo  Render module with servo
     *	\param show_assembly  Render module in assembly mode / print mode
     *	\param show_lower Show lower part in print mode
     *	\param show_upper Show upper part in print mode
     *
     */
    void configRender( bool show_servo = true, bool show_assembly = true, bool show_lower = true, bool show_upper = true );

    /*! \brief Choose the type of horn wanted for the servo
     *
     * \param num_arms Number of arms of the servo horn chosen
     * \param cut_part (Optional) Only used for the rounded horn (0 arms). Specifies an
     *	     opcional cut on the servo horn.
     *
     */
    void configHorn( int num_arms, int cut_part = 20.5/2.0 - 3);


    //-- Data interface (for reading the module attributes)
    //--------------------------------------------------------------------------------
    //-- Module components:
    //---------------------------------------
    //! \brief Returns the lower part of the module
    Component get_lower_part();

    //! \brief Returns the upper part of the module
    Component get_upper_part();

    //! \brief Returns a pointer to the servo used in the module
    BasicServo * get_servo();

    //! \brief Returns a pointer to the PCB used in the module
    BasicSquaredPCB * get_pcb();

    //! \brief Returns the fake axis screw used in the module
    Component get_fake_axis();

    //! \brief Returns the fake axis screw with the tolerance used in the module
    Component get_fake_axis_with_tol();


    //-- Lower part data:
    //-------------------------------------
    //! \brief Returns the thickness of the base of the lower part of the module
    double get_lower_base_thickness();

    //! \brief Returns the thickness of the front ear of the lower part of the module
    double get_lower_front_ear_thickness();

    //! \brief Returns the thickness of the back ear of the lower part of the module
    double get_lower_back_ear_thickness();

    //! \brief Returns the distance between the base and the tangent line on the ear
    double get_lower_ear_shift();

    //! \brief Returns the radius of the upper rounded part of the ear
    double get_lower_ear_radius();

    //! \brief Returns the space around the drills of the base for the screw
    double get_lower_screw_safe();

    //! \brief Returns the space around the border to keep when making the base holes
    double get_lower_border_safe();


    //-- Upper part data:
    //--------------------------------------
    //! \brief Returns the thickness of the base of the upper part of the module
    double get_upper_base_thickness();

    //! \brief Returns the thickness of the front ear of the upper part of the module
    double get_upper_front_ear_thickness();

    //! \brief Returns the thickness of the back ear of the upper part of the module
    double get_upper_back_ear_thickness();

    //! \brief Returns the distance between the base and the tangent line on the ear
    double get_upper_ear_shift();

    //! \brief Returns the radius of the upper rounded part of the ear
    double get_upper_ear_radius();

    //! \brief Returns the space around the drills of the base for the screw
    double get_upper_screw_safe();

    //! \brief Returns the space around the border to keep when making the base holes
    double get_upper_border_safe();

    //-- Tolerances:
    //--------------------------------------
    //! \brief Returns the clearance to insert the servo, x axis
    double get_body_servo_x_tol();

    //! \brief Returns the clearance to insert the servo, y axis
    double get_body_servo_y_tol();

    //! \brief Returns the clearance between touching ears
    double get_ear_clearance_tol();

    //! \brief Returns the clearance for the fake axis
    double get_fake_axis_tol();


    //-- Visibility flags:
    //---------------------------------------
    //! \brief Returns the visibility of the servo
    bool get_show_servo();

    //! \brief Returns true if assembly model was selected
    bool get_show_assembly();

    //! \brief Returns if lower part is show when print model is selected.
    bool get_show_lower();

    //! \brief Returns if upper part is show when print model is selected.
    bool get_show_upper();


    //-- Dimensions calculated by the software to build the module:
    //-------------------------------------
    //! \brief Returns the total side of the module (board + safe).
    double get_side();

    //! \brief Returns the dimension used to center the servo and ears on the module
    double get_central_part();


protected:

    //! \brief Builds the REPY module
    virtual Component build();

private:
    //! \brief Generates the lower part of the module
    Component lower_part();

    //! \brief Generates the upper part of the module
    Component upper_part();

    /*! \brief Generates a 'ear'
     *
     *	Each of the lateral parts of the module is a 'ear'. Basically, a
     *	'ear' is the convex hull of a cylinder and a cube.
     *
     *	For more info and explanatory images check module documentation.
     */
    Component make_ear( double base, double height, double thickness, double shift, double radius);

    //-- Needed components that define the module:
    //--------------------------------------------
    /*!
     *	\var Component lower
     *	\brief Lower part of the module
     *
     *  \var Component upper
     *	\brief Upper part of the module
     */
    Component lower, upper;

    /*! \var BasicServo * servo
     *  \brief Pointer that stores the position in memory of a BasicServo
     *
     *	This servo is the one that will define the module.
     */
    BasicServo * servo;

    /*! \var BasicSquaredPCB * pcb
     *	\brief Pointer that stores the position in memory of a BasicSquaredPCB
     *
     *  This PCB is the one that will define the module.
     */
    BasicSquaredPCB * pcb;

    /*!
     *  \var Component fake_axis
     *	\brief Model of the screw that serves as axis for the back part of the servo
     *
     *	\var Component fake_axis_with_tol
     *  \brief Model of the screw that servos as axis for the back part of the servo,
     *	    with some clearance to allow it to rotate
     *
     */
    Component fake_axis, fake_axis_with_tol;


    //-- Needed dimensions
    //-------------------------------------------------------------------------------
    //-- General:
    //---------------------------------------------
    /*! \var double board_safe
     *	\brief Space around the PCB to keep it safe
     */
    double board_safe;

    //-- Lower part:
    //---------------------------------------------
    /*!
     * \var double lower_base_thickness
     * \brief Thickness of the base of the lower part of the module
     *
     * \var double lower_front_ear_thickness
     * \brief Thickness of the front ear of the lower part of the module
     *
     * \var double lower_back_ear_thickness
     * \brief Thickness of the back ear of the lower part of the module
     *
     * \var double lower_ear_shift
     * \brief Distance between the base and the tangent line on the ear
     *
     * \var double lower_ear_radius
     * \brief Radius of the upper rounded part of the ear
     *
     * \var double lower_screw_safe
     * \brief Space around the drills of the base for the screw
     *
     * \var double lower_border_safe
     * \brief Space around the border to keep when making the base holes
     *
     */
    double lower_base_thickness;
    double lower_front_ear_thickness;
    double lower_back_ear_thickness;
    double lower_ear_shift;
    double lower_ear_radius;
    double lower_screw_safe;
    double lower_border_safe;

    //-- Upper part:
    //-----------------------------------------------
    /*!
     * \var double upper_base_thickness
     * \brief Thickness of the base of the upper part of the module
     *
     * \var double upper_front_ear_thickness
     * \brief Thickness of the front ear of the upper part of the module
     *
     * \var double upper_back_ear_thickness
     * \brief Thickness of the back ear of the upper part of the module
     *
     * \var double upper_ear_shift
     * \brief Distance between the base and the tangent line on the ear
     *
     * \var double upper_ear_radius
     * \brief Radius of the upper rounded part of the ear
     *
     * \var double upper_screw_safe
     * \brief Space around the drills of the base for the screw
     *
     * \var double upper_border_safe
     * \brief Space around the border to keep when making the base holes
     *
     */
    double upper_base_thickness;
    double upper_front_ear_thickness;
    double upper_back_ear_thickness;
    double upper_ear_shift;
    double upper_ear_radius;
    double upper_screw_safe;
    double upper_border_safe;

    //-- Tolerances:
    //------------------------------------------------
    /*!
     * \var double body_servo_x_tol
     * \brief Clearance to insert the servo, x axis
     *
     * \var double body_servo_y_tol
     * \brief Clearance to insert the servo, y axis
     *
     * \var double ear_clearance_tol
     * \brief Clearance between touching ears
     *
     * \var double fake_axis_tol
     * \brief Clearance for the fake axis
     *
     */
    double body_servo_x_tol;
    double body_servo_y_tol;
    double ear_clearance_tol;
    double fake_axis_tol;

    //-- Visibility flags:
    //-----------------------------------------------
    /*!
     * \var bool show_servo
     * \brief If true, generates model with servo
     *
     * \var bool show_assembly
     * \brief If true, shows assembly of module, if
     *	      false, generates print-ready model.
     *
     * \var bool show_lower
     * \brief If true, and if print model is selected,
     *	      generates the lower part of the module.
     *
     * \var bool show_upper
     * \brief If true, and if print model is selected,
     *	      genrates the upper part of the module.
     */
    bool show_servo;
    bool show_assembly;
    bool show_lower;
    bool show_upper;

    //-- Dimensions calculated automatically by the software:
    //-------------------------------------------------------
    /*!
     * \var double side
     * \brief Total side of the module (board + safe).
     *
     * \var double central_part
     * \brief Dimension used to center the servo and ears on
     *	      the module.
     */
    double side;
    double central_part;
};

#endif // REPY_MODULE_H
