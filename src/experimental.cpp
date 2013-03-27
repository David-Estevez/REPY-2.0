//------------------------------------------------------------------------------
//-- REPY-2.0
//------------------------------------------------------------------------------
//--
//-- This file generates all the scad and stl files for the lower part, the
//-- upper part with each kind of servo horn and the assembly view.
//--
//------------------------------------------------------------------------------
//--
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

/*! \file experimental.cpp
 *  \brief Creates a new accesory for the REPY-2.0 module.
 *
 * \author David Estévez Fernández ( http://github.com/David-Estevez )
 * \date Mar 27th, 2013
 */


#include <ooml/core.h>
#include <ooml/components.h>
#include <iostream>
#include <fstream>

#include "servos/futaba3003sservo.h"
#include "servos/fakefutaba3003sservo.h"
#include "servos/towerprosg90servo.h"

#include "boards/basicsquaredpcb.h"
#include "boards/skymegaboard.h"

#include "repy_module.h"

void generate_scad(const Component &thing, const std::string &path);

int main()
{

    TowerProSG90servo servo;
    servo.set_horn( 4);
    Component horn = servo.get_horn();
    horn.translate( 0, - servo.get_axis_y(), -servo.get_height() - servo.get_horn_dist_axis());

    generate_scad( horn, "../scad/Experimental_test.scad");
    return 0;
}


void generate_scad(const Component& thing, const std::string& path)
{
    //-- Opens a file and generates the openscad code

    //-- Create a IndentWriter
    IndentWriter writer;
    writer << thing;

    //-- Open a file:
    std::ofstream file( path.c_str() );

    //-- Get the name of the file:
    std::string name = path.substr( path.rfind( "/") + 1 );

    //-- Check if it is open:
    if ( file.is_open() )
    {
	file << "//-------------------------------------------------------------------------"	<< std::endl;
	file << "//-- " << name									<< std::endl;
	file << "//-------------------------------------------------------------------------"	<< std::endl;
	file << "//--This file has been generated automatically according to your data."	<< std::endl;
	file << "//--For more info, visit: http://iearobotics.com/oomlwiki/"			<< std::endl;
	file << "//-------------------------------------------------------------------------"   << std::endl;
	file << "//--This file belongs to the REPY-2.0 project, for more info, visit:"		<< std::endl;
	file << "//-- http://www.dsquaredrobotics.com/wiki/index.php?title=REPY-2.0"		<< std::endl;
	file << "//-------------------------------------------------------------------------"	<< std::endl
												<< std::endl;
	file << writer;

	file.close();
    }
    else
    {
	std::cout << "Some error ocurred opening the file \"" << path << "\"\n";
    }
}
