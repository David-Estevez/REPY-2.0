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
 * \date Apr 1st, 2013
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
Component top_part();
Component bottom_part();

int main()
{
    std::cout << "[+] Generating experimental parts:" << std::endl;

    //-- Generate the openSCAD file:
    std::cout << "\t[+] Generating top part...";
    Component top = top_part();
    generate_scad(top, "../scad/Experimental_test.scad");
    std::cout << "\t[ok]" << std::endl;


    //-- Generate the openSCAD file:
    std::cout << "\t[+] Generating bottom part...";
    Component bottom = bottom_part();
    generate_scad( bottom, "../scad/Experimental_test.scad");
    std::cout << "\t[ok]" << std::endl;


    return 0;
}

Component top_part()
{
    //Top part
    //-----------------------------------------------------------------------------------------
    Component top;

    //-- Servo horn creation and placing:
    TowerProSG90servo servo;
    servo.set_horn( 4);
    Component horn = servo.get_horn();
    horn.translate( 0, - servo.get_axis_y(), -servo.get_height() - servo.get_horn_dist_axis() + servo.get_horn_h_axis()) ;

    //-- Skymega board and top part parameters:
    SkyMegaBoard pcb;
    double top_thickness = servo.get_horn_h_axis() + servo.get_horn_h_top();
    double top_border_safe = 1.5;
    double top_side = pcb.get_side() + 2*top_border_safe;

    BasicSquaredPCB top_base = BasicSquaredPCB( top_thickness-0.01, top_side, pcb.get_drill_diam(), pcb.get_drill_x(), pcb.get_drill_y());
			      top_base.translate( 0, 0, (top_thickness - 0.01)/2.0);

    //-- Generate the component
    top = top_base - horn;

    return top;
}

Component bottom_part()
{
    //-- Bottom part
    //------------------------------------------------------------------------------------------
    Component bottom;

    //-- Servo creation and placing:
    TowerProSG90servo servo;
    servo.set_horn( 4, false);
    servo.rotate( 0, 180, 0);
    servo.translate( 0, - servo.get_axis_y(), servo.get_height()- 0.001 );

    //-- Skymega board
    SkyMegaBoard pcb;

    //-- REPY module creation for obtaining limits:
    FakeFutaba3003sServo auxServo;
    auxServo.set_horn(0);

    REPY_module repy( auxServo, pcb);
    repy.configRender( false, false, true, false);

    //-- Other dimensions:
    //-- For cross-shaped hole:
    double dim1 = repy.get_side()-2*repy.get_upper_border_safe();
    double dim2 = pcb.get_drill_x() - pcb.get_drill_diam() - 2* repy.get_upper_screw_safe();
    double dim3 = pcb.get_drill_y() - pcb.get_drill_diam() - 2* repy.get_upper_screw_safe();

    //-- Bottom part parameters:
    double servo_ring_h = servo.get_height()-servo.get_gearbox_h() - (servo.get_leg_h() + servo.get_leg_z() );

    double bottom_thickness = servo.get_gearbox_h();
    double bottom_border_safe = 1.5;
    double bottom_side = pcb.get_side() + 2*bottom_border_safe;
    double bottom_servo_safe = 6;

    //-- REPY lower cross-shaped hole:
    Component cross_hole = RoundedTablet( dim1, dim3, servo_ring_h, 5 )
			 + RoundedTablet( dim2, dim1, servo_ring_h, 5 );
    cross_hole.translate(0,0, servo_ring_h / 2.0);


    //-- Actual lower part:
    BasicSquaredPCB bottom_base = BasicSquaredPCB( bottom_thickness, bottom_side, pcb.get_drill_diam(), pcb.get_drill_x(), pcb.get_drill_y());
    bottom_base.translate( 0, 0, (bottom_thickness - 0.01)/2.0);

    Component servo_ring = RoundedTablet( servo.get_width() + bottom_servo_safe,
					  servo.get_length()+ bottom_servo_safe,
					  servo_ring_h,
					  bottom_servo_safe / 2.0,
					  true, true, true, true, 100, false);


    servo_ring.translate( -(servo.get_width() + bottom_servo_safe )/2.0, -(servo.get_length()+ bottom_servo_safe ) / 2.0  - (servo.get_axis_y() - servo.get_length() / 2.0 ), 0 );
    servo_ring = servo_ring * cross_hole;
    servo_ring.translate( 0, 0, bottom_thickness);

    //-- Generate the component
    bottom = bottom_base + servo_ring - servo;

    return bottom;
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
