//------------------------------------------------------------------------------
//-- Basic servo
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

/*! \file basicservo.h
 *  \brief Defines the simplest structure of a servo, and its data interface.
 *
 *  To make objects compatible with as much servos as possible, new servos
 *  should inherit from this 'BasicServo'
 *
 * \author David Estévez Fernández ( http://github.com/David-Estevez )
 * \date Mar 2nd, 2013
 *
 */

#ifndef BASIC_SERVO_H
#define BASIC_SERVO_H

#include <ooml/core.h>
#include <ooml/components.h>

/*! \class BasicServo
 *  \brief Defines the simplest structure of a servo, and its data interface.
 *
 *  To make objects compatible with as much servos as possible, new servos
 *  should inherit from this 'BasicServo'
 */
class BasicServo: public AbstractPart
{
public:
    //-- Object dimensions interface:
    //-------------------------------------------------------------------

    //-- Main dimensions:
    //----------------------------------------
    //! \brief Returns the width of the body of the servo
    double get_width();

    //! \brief Returns the length of the body of the servo
    double get_length();

    //! \brief Returns the height of the body of the servo
    double get_height();

    //-- Leg dimensions:
    //-----------------------------------------
    //! \brief Returns the height at which the servo leg is placed
    double get_leg_h();

    //! \brief Returns the dimension of the leg on the X axis
    double get_leg_x();

    //! \brief Returns the dimension of the leg on the Y axis
    double get_leg_y();

    //! \brief Returns the dimension of the leg on the z axis
    double get_leg_z();

    //-- Leg holes
    //-----------------------------------------
    //! \brief Returns the amount of holes of the servo legs
    int get_num_holes();

    //! \brief Returns the radius of the servo legs holes
    double get_hole_r();

    //! \brief Returns the offset of the servo leg holes on the X axis
    double get_hole_x();

    //! \brief Returns the offset of the servo leg holes on the Y axis
    double get_hole_y();

    //-- Axis dimensions:
    //-----------------------------------------
    //! \brief Returns the height at which the servo axis is placed
    double get_axis_h();

    //! \brief Returns the radius of the servo axis
    double get_axis_r();

    //! \brief Returns the position of the servo axis on the Y axis
    double get_axis_y();

    //-- Horn positioning:
    //-----------------------------------------
    //! \brief Returns the distance between the servo body and the horn bigger part
    double get_horn_dist_axis();

    //-- Tolerances:
    //-----------------------------------------
    //! \brief Returns the clearance of the width of the servo body
    double get_width_tol();

    //! \brief Returns the clearance of the length of the servo body
    double get_length_tol();

    //! \brief Returns the clearance of the height of the servo body
    double get_height_tol();


    //-- Horn dimensions:
    //------------------------------------------
    //! \brief Returns the number of arms of the horn
    double get_horn_num_arms();

    //! \brief Returns the thickness of the upper part of the horn
    double get_horn_h_top();

    //! \brief Returns the radius of the upper part of the horn
    double get_horn_r_top();

    //! \brief Returns the thickness of the lower part of the horn
    double get_horn_h_axis();

    //! \brief Returns the radius of the lower part of the horn
    double get_horn_r_axis();

    //! \brief Returns the radius of the extreme of the horn arm
    double get_horn_arm_r();

    //! \brief Returns the shift of the horn arm
    double get_horn_arm_shift();

    //! \brief Returns the tolerance of the horn
    double get_horn_tol();

    //! \brief Returns the dimension of the cut of the horn
    double get_horn_cut();

    //-- Horn (others):
    //------------------------------------------
    //! \brief Returns the visibility of the horn
    bool horn_shown();

    //! \brief Returns the horn as a component
    Component get_horn();

    //-- Servo configuration:
    //-----------------------------------------------------------------
    /*! \brief Sets the characteristics and dimensions of the horn
     *
     *  \param arms Number of arms of the horn
     *  \param visibility Horn shown or not shown
     *  \param cut Dimension of the cut of the horn
     */
    virtual void set_horn( int arms, bool visibility = true, double cut = 0) = 0;

    /*! \brief Sets main servo body tolerances
     *
     *	\param width_tol Clearance of the body of the servo width
     *  \param length_tol Clearance of the body of the servo length
     *	\param height_tol Clearance of the body of the servo height
     */
    void set_tolerances( double width_tol, double length_tol, double height_tol );

protected:
    //! \brief Default constructor
    BasicServo();

    //! \brief Builds and returns the BasicServo
    virtual Component build();

    //! \brief Builds the servo horn and saves it in horn variable
    virtual void make_horn();

    //-- Servo characteristics:
    //------------------------------------------------------------------
    //-- Main dimensions:
    double width, length, height;

    //-- Leg dimensions:
    double leg_h, leg_x, leg_y, leg_z;

    //-- Leg holes
    int num_holes;
    double  hole_r, hole_x, hole_y;

    //-- Axis dimensions:
    double axis_h, axis_r, axis_y;

    //-- Horn positioning:
    double horn_dist_axis;

    //-- Tolerances:
    double width_tol;
    double length_tol;
    double height_tol;

    //-- Color:
    std::vector<double> servo_color;

    //-- Horn characteristics:
    //----------------------------------------
    Component horn;
    bool display_horn;

    int horn_num_arms;
    double horn_h_top, horn_r_top;
    double horn_h_axis, horn_r_axis;
    double horn_arm_r, horn_arm_shift, horn_arm_dist;
    double horn_tol;
    double horn_cut; //-- For cutting the round horn.

    //-- Horn color:
    std::vector<double> horn_color;
};


#endif // BASIC_SERVO_H
