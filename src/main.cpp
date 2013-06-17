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

/*! \file main.cpp
 *  \brief Generate the scad and stl files for the REPY-2.0 module.
 *
 * \author David Estévez Fernández ( http://github.com/David-Estevez )
 * \date Jun 17th, 2013
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

void generate_scad(const Component& thing, const std::string& path);
void generate_stl(const std::string &basePath);

int main()
{
    //-- Create all used objects:
    //----------------------------------------------------------
    std::cout << "[+] Generating objects..." << std::endl;


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

    //-- Generate the scad files:
    //---------------------------------------------------------------------------
    std::cout << "[+] Generating the scad files... " << std::endl;

    //-- Fake Futaba 3003s servo scad files:
    std::cout << "\t[+] With Fake Futaba 3003s servo... ";
    REPY_fake_futaba.configRender( false, false, true, false);
    generate_scad( REPY_fake_futaba, "../scad/REPY Fake Futaba 3003s/REPY_Fake_Futaba_3003s_lower.scad");

    REPY_fake_futaba.configRender( false, false, false, true);
    REPY_fake_futaba.configHorn( 0);
    generate_scad( REPY_fake_futaba, "../scad/REPY Fake Futaba 3003s/REPY_Fake_Futaba_3003s_upper_rounded_horn.scad");
    REPY_fake_futaba.configHorn( 2);
    generate_scad( REPY_fake_futaba, "../scad/REPY Fake Futaba 3003s/REPY_Fake_Futaba_3003s_upper_2_arms_horn.scad");
    REPY_fake_futaba.configHorn( 4);
    generate_scad( REPY_fake_futaba, "../scad/REPY Fake Futaba 3003s/REPY_Fake_Futaba_3003s_upper_4_arms_horn.scad");
    REPY_fake_futaba.configHorn( 6);
    generate_scad( REPY_fake_futaba, "../scad/REPY Fake Futaba 3003s/REPY_Fake_Futaba_3003s_upper_6_arms_horn.scad");

    REPY_fake_futaba.configRender(true, true);
    REPY_fake_futaba.configHorn( 0);
    generate_scad( REPY_fake_futaba, "../scad/REPY Fake Futaba 3003s/REPY_Fake_Futaba_3003s_assembly.scad");
    std::cout << "[ok]" << std::endl;

    //-- Futaba 3003s servo scad files: //-- Tested Horn: none
    std::cout << "\t[+] With Futaba 3003s servo... " ;
    REPY_futaba.configRender( false, false, true, false);
    generate_scad( REPY_futaba, "../scad/REPY Futaba 3003s/REPY_Futaba_3003s_lower.scad");
    REPY_futaba.configRender( false, false, false, true);
    REPY_futaba.configHorn( 0, 21/2.0 - 3);
    generate_scad( REPY_futaba, "../scad/REPY Futaba 3003s/REPY_Futaba_3003s_upper_rounded_horn.scad");
    REPY_futaba.configRender(true, true);
    generate_scad( REPY_futaba, "../scad/REPY Futaba 3003s/REPY_Futaba_3003s_assembly.scad");
    std::cout << "[ok]" << std::endl;

    //-- TowerPro SG90 servo scad files: //-- Horn: 1, 2, 4
    std::cout << "\t[+] With Tower Pro SG90 servo... ";
    miniREPY.configRender( false, false, true, false);
    generate_scad( miniREPY, "../scad/REPY TowerPro sg90/REPY_Tower_Pro_SG90_lower.scad");

    miniREPY.configRender( false, false, false, true);
    miniREPY.configHorn(1);
    generate_scad( miniREPY, "../scad/REPY TowerPro sg90/REPY_Tower_Pro_SG90_upper_1_arm.scad");
    miniREPY.configHorn(2);
    generate_scad( miniREPY, "../scad/REPY TowerPro sg90/REPY_Tower_Pro_SG90_upper_2_arms.scad");
    miniREPY.configHorn(4);
    generate_scad( miniREPY, "../scad/REPY TowerPro sg90/REPY_Tower_Pro_SG90_upper_4_arms.scad");

    miniREPY.configHorn(1);
    miniREPY.configRender(true, true);
    generate_scad( miniREPY, "../scad/REPY TowerPro sg90/REPY_Tower_Pro_SG90_assembly.scad");
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


	    //-- Fake Futaba 3003s
	    //-------------------------------------------------------------------------------------
	    std::cout << "\t[+] Generating stl for REPY Fake Futaba 3003s..." << std::endl;

	    std::cout << "\t\t-> Lower part... [1/5]" << std::endl;
	    generate_stl("REPY Fake Futaba 3003s/REPY_Fake_Futaba_3003s_lower");

	    std::cout << "\t\t-> Upper part (rounded horn)... [2/5]" << std::endl;
	    generate_stl("REPY Fake Futaba 3003s/REPY_Fake_Futaba_3003s_upper_rounded_horn");

	    std::cout << "\t\t-> Upper part (2-arms horn)... [3/5]" << std::endl;
	    generate_stl("REPY Fake Futaba 3003s/REPY_Fake_Futaba_3003s_upper_2_arms_horn");

	    std::cout << "\t\t-> Upper part (4-arms horn)... [4/5]" << std::endl;
	    generate_stl("REPY Fake Futaba 3003s/REPY_Fake_Futaba_3003s_upper_4_arms_horn");

	    std::cout << "\t\t-> Upper part (6-arms horn)... [5/5]" << std::endl;
	    generate_stl("REPY Fake Futaba 3003s/REPY_Fake_Futaba_3003s_upper_6_arms_horn");


	    //-- Futaba 3003s
	    //-------------------------------------------------------------------------------------
	    std::cout << "\t[+] Generating stl for REPY Futaba 3003s..." << std::endl;

	    std::cout << "\t\t-> Lower part... [1/2]" << std::endl;
	    generate_stl("REPY Futaba 3003s/REPY_Futaba_3003s_lower");

	    std::cout << "\t\t-> Upper part... [2/2]" << std::endl;
	    generate_stl("REPY Futaba 3003s/REPY_Futaba_3003s_upper_rounded_horn");


	    //-- TowerPro sg90
	    //-------------------------------------------------------------------------------------
	    std::cout << "\t[+] Generating stl for REPY Futaba 3003s..." << std::endl;

	    std::cout << "\t\t-> Lower part... [1/4]" << std::endl;
	    generate_stl("REPY TowerPro sg90/REPY_Tower_Pro_SG90_lower");

	    std::cout << "\t\t-> Upper part (1-arm horn)... [2/4]" << std::endl;
	    generate_stl("REPY TowerPro sg90/REPY_Tower_Pro_SG90_upper_1_arm");

	    std::cout << "\t\t-> Upper part (2-arm horn)... [3/4]" << std::endl;
	    generate_stl("REPY TowerPro sg90/REPY_Tower_Pro_SG90_upper_2_arms");

	    std::cout << "\t\t-> Upper part (4-arm horn)... [4/4]" << std::endl;
	    generate_stl("REPY TowerPro sg90/REPY_Tower_Pro_SG90_upper_4_arms");
	}
    }

    std::cout << "[+] Process finished. Exiting..." << std::endl;

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

void generate_stl(const std::string& basePath)
{
    //-- Compiles a scad file
    std::string command = "openscad -o \"../stl/" + basePath + ".stl\" \"../scad/" + basePath + ".scad\" >&2 2> /dev/null";
    system( command.c_str() );
}
