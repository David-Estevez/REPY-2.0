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
 * \date Aug 4th, 2013
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


    //-- Servo (others)
    //------------------------------------------
    //! \brief Returns the body of the servo
    Component get_servo_body();

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

    /*! \brief Returns the distance between the center of the horn
     *  and the center of the arm circle
     */
    double get_horn_arm_dist();

    //! \brief Returns the clearance for making holes with the horn
    double get_horn_tol();

    //! \brief Returns the distance between the cut part and the rounded extreme
    double get_horn_cut();

    //-- Horn (others):
    //------------------------------------------
    //! \brief Returns the visibility of the horn
    bool horn_shown();

    //! \brief Returns the horn as a component
    Component get_horn();

    //! \brief Returns the horn angle
    double get_horn_angle();

    //-- Servo configuration:
    //-----------------------------------------------------------------
    /*! \brief Sets the characteristics and dimensions of the horn
     *
     *  \param arms Number of arms of the horn
     *  \param visibility Horn shown or not shown
     *  \param cut Dimension of the cut of the horn
     */
    void set_horn( int arms, double angle = 0, bool visibility = true, double cut = 0);

    /*! \brief Sets the visibility of the horn
     *
     *  \param visibility Horn shown or not shown
     */
    void set_horn_visibility( bool visibility);

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

    /*! \brief Sets the different default dimensions of the horn after a change in
     *	the horn main characteristics.
     */
    virtual void update_horn() = 0;

    //! \brief Builds and returns the BasicServo
    virtual Component build();

    //! \brief Builds the servo horn and saves it in horn variable
    virtual void make_horn();

    //-- Servo characteristics:
    //------------------------------------------------------------------
    /*! \var Component servo
     *  \brief Servo body (servo without horn)
     */
    Component servo;

    //-- Main dimensions:
    /*!
     * \var double width
     * \brief  wwidth of the body of the servo
     *
     * \var double length
     * \brief  length of the body of the servo
     *
     * \var double height
     * \brief  height of the body of the servo
     */
    double width, length, height;

    //-- Leg dimensions:
    /*!
     * \var double leg_h
     * \brief  Height at which the servo leg is placed
     *
     * \var double leg_x
     * \brief  Dimension of the leg on the X axis
     *
     * \var double leg_y
     * \brief Dimension of the leg on the Y axis
     *
     * \var double leg_z
     * \brief Dimension of the leg on the Z axis
     */
    double leg_h, leg_x, leg_y, leg_z;

    //-- Leg holes
    /*!
     * \var int num_holes
     * \brief Amount of holes of the servo legs.
     *
     * \var double hole_r
     * \brief Radius of the servo leg holes
     *
     * \var double hole_x
     * \brief Offset of the servo leg holes on the X axis
     *
     * \var double hole_y
     * \brief Offset of the servo leg holes on the X axis
     */
    int num_holes;
    double  hole_r, hole_x, hole_y;

    //-- Axis dimensions:
    /*!
     * \var double axis_h
     * \brief Height at which the servo axis is placed
     *
     * \var double axis_r
     * \brief Radius of the servo axis
     *
     * \var double axis_y
     * \brief Position of the servo axis on the Y axis
     */
    double axis_h, axis_r, axis_y;

    //-- Horn positioning:
    /*! \var double horn_dist_axis
     *  \brief Distance between the servo body and the horn bigger part
     */
    double horn_dist_axis;

    //-- Tolerances:
    /*!
     * \var double width_tol
     * \brief Clearance of the width of the servo body
     *
     * \var double length_tol
     * \brief Clearance of the length of the servo body
     *
     * \var double height_tol
     * \brief Clearance of the height of the servo body
     */
    double width_tol;
    double length_tol;
    double height_tol;

    //-- Color:
    /*!
     * \var std::Vector<double> servo_color
     * \brief Color of the body of the servo.
     *
     * This color should be a vector with 4 values: RGB values +
     * the alpha channel.
     *
     */
    std::vector<double> servo_color;

    //-- Horn characteristics:
    //----------------------------------------
    /*! \var Component horn
     *  \brief Servo horn
     */
    Component horn;

    /*! \var bool display_horn
     *  \brief Stores the state of the horn: shown / not shown
     */
    bool display_horn;

    /*! \var int horn_num_arms
     *  \brief Number of arms of the horn
     */
    int horn_num_arms;

    /*! \var double horn_h_top
     * \brief Thickness of the upper part of the horn
     *
     * \var double horn_r_top
     * \brief Radius of the upper part of the horn
     */
    double horn_h_top, horn_r_top;

    /*! \var double horn_h_axis
     * \brief Thickness of the lower part of the horn
     *
     * \var double horn_r_axis
     * \brief Radius of the lower part of the horn
     */
    double horn_h_axis, horn_r_axis;

    /*! \var double horn_arm_r
     * \brief Radius of the extreme of the horn arm
     *
     * \var double horn_arm_shift
     * \brief Shift of the horn arm
     *
     * \var double horn_arm_dist
     * \brief Distance between the center of the horn
     *	      and the center of the arm circle
     */
    double horn_arm_r, horn_arm_shift, horn_arm_dist;

    /*! \var double horn_tol
     *	\brief Clearance for making holes with the horn
     */
    double horn_tol;

    /*! \var double horn_cut
     *	\brief Distance between the cut part and the rounded extreme
     *
     *	This distance is equal to the diameter of the upper part
     *	of the horn minus the amount cut
     */
    double horn_cut; //-- For cutting the round horn.

    //-- Horn color:
    /*!
     * \var std::Vector<double> horn_color
     * \brief Color of the servo horn
     *
     * This color should be a vector with 4 values: RGB values +
     * the alpha channel.
     *
     */
    std::vector<double> horn_color;

    //-- Horn position:
    /*!
     * \var double horn_angle
     * \brief Angle of the horn
     *
     */
    double horn_angle;
};


#endif // BASIC_SERVO_H
