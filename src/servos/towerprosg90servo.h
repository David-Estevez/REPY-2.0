//------------------------------------------------------------------------------
//-- Tower Pro SG90 servo
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

/*! \file towerprosg90servo.h
 *  \brief Tower Pro SG90 servo
 *
 * \author David Estévez Fernández ( http://github.com/David-Estevez )
 * \date Mar 28rd, 2013
 *
 * \todo Add more horns ( 4-arms horn)
 */

#ifndef TOWERPROSG90SERVO_H
#define TOWERPROSG90SERVO_H


#include "basicservo.h"

/*! \class TowerProSG90servo
 *  \brief A Tower Pro SG90 servo 3D model
 *
 */
class TowerProSG90servo: public BasicServo
{
public:
    //! \brief Default constructor
    TowerProSG90servo();

    //-- Added data interface:
    double get_gearbox_h();
    double get_gearbox_big_r();
    double get_gearbox_small_r();
    double get_gearbox_small_y();

    double get_horn_arm_r_small();
    double get_horn_arm_dist_small();

protected:    
    /*! \brief Sets the different default dimensions of the horn after a change in
     *	the horn main characteristics.
     */
    virtual void update_horn();

    //-- Reimplement the servo creation function
    virtual Component build();

    //-- Reimplement the servo horn creation function
    virtual void make_horn();

    //-- Other needed parameter to improve the aspect of the servo:
    double gearbox_h;
    double gearbox_big_r;
    double gearbox_small_r;
    double gearbox_small_y;

    //-- New parameters for 4-arms horn
    double horn_arm_r_small;
    double horn_arm_dist_small;
};

#endif // TOWERPROSG90SERVO_H
