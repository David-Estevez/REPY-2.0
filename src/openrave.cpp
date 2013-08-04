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
#include <string>

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

    //-- Generate important data
    //------------------------------------------------------------
    std::cout << "[+] Obtaining important dimensions..." << std::endl;

    //-- Lower part:
    std::cout << "\t[+] Body..." << std::endl;

    double lower_length = REPY_futaba.get_side();
    double lower_width  = REPY_futaba.get_side();
    double lower_height = REPY_futaba.get_lower_base_thickness() +
			  REPY_futaba.get_servo()->get_axis_y() + REPY_futaba.get_servo()->get_leg_y() +
			  REPY_futaba.get_lower_ear_radius();

    //-- Upper part:
    std::cout << "\t[+] Head..." << std::endl;

    double upper_length = REPY_futaba.get_side();
    double upper_width  = REPY_futaba.get_side();
    double upper_height = REPY_futaba.get_upper_base_thickness() +
			  REPY_futaba.get_servo()->get_axis_y() + REPY_futaba.get_servo()->get_leg_y() +
			  REPY_futaba.get_upper_ear_radius();

    //-- Transformation of the upper part:
    std::cout << "\t[+] Other... " << std::endl;

    //-- Translation values:
    double x, y, z;
    REPY_futaba.get_upper_RefSys().getTransformMatrix().getGlobalTranslation(x, y, z);

    //-- Rotation values:
    double xa, ya, za;
    REPY_futaba.get_upper_RefSys().getTransformMatrix().getGlobalXYZAngles(xa, ya, za);

    //-- Compose output text:
    std::stringstream output_text;

    output_text << "# REPY module data for openRAVE model" << std::endl;
    output_text << "# -----------------------------------" << std::endl << std::endl;
    output_text << "# Body dimensions in mm (length, width, height): "	<< std::endl;
    output_text << lower_length << " " << lower_width << " " << lower_height << std::endl << std::endl;
    output_text << "# Head dimensions in mm (length, width, height): "	<< std::endl;
    output_text << upper_length << " " << upper_width << " " << upper_height << std::endl << std::endl;
    output_text << "# Transform data for upper part:" << std::endl;
    output_text << "# Rotation angles: " << std::endl;
    output_text << xa << " " << ya << " " << za << std::endl;
    output_text << "# Translation distances: " << std::endl;
    output_text << x << " " << y << " " << z << std::endl;

    //-- Output text on screen:
    std::cout << "\t[+] Generated data: " << std::endl << std::endl;
    std::cout << output_text.str() << std::endl;
    std::cout << "[+] Saving data to file..." << std::endl;

    //-- Open file
    std::ofstream datafile( "./REPY_openRAVE_data.txt" );

    if ( datafile.is_open() && datafile.good() )
    {
	datafile << output_text.str().c_str(); //-- There must be a simpler way of doing this...
    }

    datafile.close();

    //-- Create stls
    //---------------------------------------------------------------------------------------------
    char ans[3];
    std::cout << "[?] Would you like to generate the stl files?" << std::endl;
    std::cout << "[?] This operation may take a long, long, long time.(yes/no) > ";
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
