//------------------------------------------------------------------------------
//-- REPY-2.0
//------------------------------------------------------------------------------
//--
//-- This file generates all the data need for including a REPY-2.0 model in
//-- openRAVE with openMR installed.
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

/*! \file  openrave.cpp
 *  \brief Generate the data need for simulating REPY-2.0 on openRAVE
 *
 * \author David Estévez Fernández ( http://github.com/David-Estevez )
 * \date Aug 4th, 2013
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
#include "utils.h"

int main()
{
    //-- Create all used objects:
    //----------------------------------------------------------
    std::cout << "[+] Generating models..." << std::endl;

    //-- Create PCB boards:
    std::cout  << "\t[+] Making PCB boards... ";

    SkyMegaBoard skymega;
    BasicSquaredPCB miniPCB( 15, 35, 3, 30, 30);

    std::cout << "[ok]" << std::endl;


    //-- Create servos:
    std::cout << "\t[+] Making servos... ";
    FakeFutaba3003sServo fakefutaba3003s;
    Futaba3003sServo futaba3003s;
    TowerProSG90servo towerprosg90;
    cout << "[ok]" << std::endl;

    //-- Build modules:
    std::cout << "\t[+] Making modules... ";
    REPY_module REPY_fake_futaba( fakefutaba3003s, skymega);
    REPY_module REPY_futaba( futaba3003s, skymega);
    REPY_module miniREPY( towerprosg90, miniPCB);
    std::cout << "[ok]" << std::endl;


    //-- Generate SCAD files
    //-----------------------------------------------------------
    std::cout << "[+] Generating SCAD files..." << std::endl;

    REPY_futaba.configHorn( 0 );

    //-- Lower part
    std::cout << "\t[+] Body... ";
    REPY_futaba.configRender( true, false, true, false);
    generate_scad( REPY_futaba, "../scad/OpenRAVE/Body.scad");
    std::cout << "[ok]" << std::endl;

    //-- Upper part
    std::cout << "\t[+] Head... ";
    REPY_futaba.configRender( true, false, false, true);
    generate_scad( REPY_futaba, "../scad/OpenRAVE/Head.scad");
    std::cout << "[ok]" << std::endl;

    //-- Servo
    std::cout << "\t[+] Servo... ";
    generate_scad( fakefutaba3003s/*.get_horn()*/, "../scad/OpenRAVE/servo.scad");
    std::cout << "[ok]" << std::endl;

    //-- Create stls
    //----------------------------------------------------------------------------------------------------------------------
    char ans[3];
    std::cout << "[?] Would you like to generate the stl files?" << std::endl;
    std::cout << "[?] This operation will take a long, long, long time.(yes/no) > ";
    std::cin >> ans;

    if (ans[0]  == 'y' || ans[0] == 'Y')
    {
	std::cout << "[?] Are you sure? (Will take really long time) (yes/no) > ";
	std::cin >> ans;

	if (ans[0]  == 'y' || ans[0] == 'Y')
	{
	    //-- Generating stl's:
	    //--------------------------------------------------------------------------------------
	    std::cout << "[+] Generating stl files..." << std::endl;

	    //-- Lower part
	    std::cout << "\t[+] Body..." << std::endl;
	    generate_stl("OpenRAVE/Body");

	    //-- Upper part
	    std::cout << "\t[+] Head..." << std::endl;
	    generate_stl("OpenRAVE/Head");
	}
    }

    std::cout << "[+] Process finished. Exiting..." << std::endl;


    return 0;
}
