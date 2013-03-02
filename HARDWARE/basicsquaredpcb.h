//------------------------------------------------------------------------------
//-- Basic squared PCB
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

/*! \file basicsquaredpcb.h
 *  \brief Defines the simplest structure of a squared pcb with drills, and its
 *  data interface.
 *
 *  It is the parent class of other pcb boards, like the SkyMega
 *
 * \author David Estévez Fernández ( http://github.com/David-Estevez )
 * \date Mar 2nd, 2013
 *
 */

#ifndef BASICSQUAREDPCB_H
#define BASICSQUAREDPCB_H

#include <ooml/core.h>
#include <ooml/components.h>

class BasicSquaredPCB : public AbstractPart
{
public:
    BasicSquaredPCB( double thickness, double side, double drill_diam, double drill_x, double drill_y);

    //-- Data interface:
    //---------------------------
    double get_thickness();
    double get_side();
    double get_drill_diam();
    double get_drill_x();
    double get_drill_y();

protected:
    virtual Component build();

private:
    BasicSquaredPCB();
    //-- Dimensions
    double thickness;
    double side;
    double drill_diam;
    double drill_x;
    double drill_y;

};


#endif // BASICSQUAREDPCB_H
