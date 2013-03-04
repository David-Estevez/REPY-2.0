//------------------------------------------------------------------------------
//-- SkyMega Board
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

/*! \file skymegaboard.h
 *  \brief 3D model of the SkyMega Board
 *
 *  More info about the SkyMega Board: http://www.thingiverse.com/thing:14197
 *
 * \author David Estévez Fernández ( http://github.com/David-Estevez )
 * \date Mar 3rd, 2013
 *
 */

#ifndef SKYMEGABOARD_H
#define SKYMEGABOARD_H

#include <ooml/core.h>
#include <ooml/components.h>

#include "basicsquaredpcb.h"

/*! \class SkyMegaBoard
 *  \brief Simple 3D model of the SkyMega Board
 */
class SkyMegaBoard : public BasicSquaredPCB
{
public:
    //! \brief Default constructor
    SkyMegaBoard();

};

#endif // SKYMEGABOARD_H
