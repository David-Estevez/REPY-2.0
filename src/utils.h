//------------------------------------------------------------------------------
//-- Utils
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

/*! \file utils.h
 *  \brief Functions to save scad files and compile then in stl files.
 *
 * \author David Estévez Fernández ( http://github.com/David-Estevez )
 * \date Jul 28th, 2013
 *
 */


#include <ooml/core.h>
#include <ooml/components.h>

#include <iostream>
#include <fstream>

/*! \brief Function to generate a scad file from a object
 *
 * \param thing Object
 * \param path Path to the scad file
 */
void generate_scad(const Component& thing, const std::string& path);

/*! \brief Function to automate stl compilation from scad files
 *
 *  Requires to have openSCAD installed
 *
 * \param basePath Path to the scad file without extension
 */
void generate_stl(const std::string &basePath);
