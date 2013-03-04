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

/*! \class BasicSquaredPCB
 *  \brief Simple squared PCB with holes
 */
class BasicSquaredPCB : public AbstractPart
{
public:
    //! \brief Constructor
    BasicSquaredPCB( double thickness, double side, double drill_diam, double drill_x, double drill_y);

    //-- Data interface:
    //-----------------------------------------------------------
    //! \brief Returns the thickness of the PCB
    double get_thickness();
    //! \brief Returns the side of the PCB
    double get_side();
    //! \brief Returns the diameter of the PCB drills
    double get_drill_diam();
    //! \brief Returns the distance between drill centers on X axis
    double get_drill_x();
    //! \brief Returns the distance between drill centers on Y axis
    double get_drill_y();

protected:
    virtual Component build();

private:
    //! \brief Default constructor
    BasicSquaredPCB();

    //-- Dimensions
    //---------------------------------------------------------
    /*! \var double thickness
     *  \brief Thickness of the PCB
     */
    double thickness;

    /*! \var double side
     *  \brief Side of the PCB
     */
    double side;

    /*! \var double drill_diam
     *  \brief Diameter of the PCB drills
     */
    double drill_diam;

    /*! \var double drill_x
     *  \brief Distance between drill centers on X axis
     */
    double drill_x;

    /*! \var double drill_y
     *  \brief Distance between drill centers on Y axis
     */
    double drill_y;

};


#endif // BASICSQUAREDPCB_H
