//------------------------------------------------------------------------------
//-- Futaba 3003s servo
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

/*! \file futaba3003sservo.h
 *  \brief Futaba 3003s servo.
 *
 * \author David Estévez Fernández ( http://github.com/David-Estevez )
 * \date Mar 2nd, 2013
 *
 */

#ifndef FUTABA3003SSERVO_H
#define FUTABA3003SSERVO_H

#include "basicservo.h"

class Futaba3003sServo : public BasicServo
{
public:
    Futaba3003sServo();

protected:
    virtual void set_horn( int arms, bool visibility = true, double cut = 0);

};

#endif // FUTABA3003SSERVO_H
