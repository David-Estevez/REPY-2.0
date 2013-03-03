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
 * \date Mar 3rd, 2013
 *
 * \todo Add more horns ( 4-arms horn)
 */

#ifndef TOWERPROSG90SERVO_H
#define TOWERPROSG90SERVO_H


#include "basicservo.h"

class TowerProSG90servo: public BasicServo
{
public:
    TowerProSG90servo();

protected:
    virtual void set_horn( int arms, bool visibility = true, double cut = 0);
};

#endif // TOWERPROSG90SERVO_H
