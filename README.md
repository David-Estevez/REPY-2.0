REPY-2.0
=========================================================

Symmetric module for modular robots.


* Author: [David Estevez-Fernandez (DEF)](http://www.thingiverse.com/DEF)

This work is based on REPY module, by:
[Juan Gonzalez-Gomez (Obijuan)](http://www.thingiverse.com/Obijuan)


<img src="http://www.dsquaredrobotics.com/wiki/images/thumb/e/e2/REPY_2_first_prototype_scad.png/800px-REPY_2_first_prototype_scad.png" alt="Version 2.0" width="300" /> 

More information on: 
* [d-squared:wiki - REPY-2.0](http://www.dsquaredrobotics.com/wiki/index.php?title=REPY-2.0)

* [Thingiverse - REPY v1.1](http://www.thingiverse.com/thing:13442)

* http://www.iearobotics.com/wiki/index.php?title=M%C3%B3dulos_REPY-1 (Spanish)


0. Index
-------------------------------------------------------------------
 * 1.Introduction
 * 2.Dependencies
 * 3.Usage
 * 4.Version log


1. Introduction
--------------------------------------------------------------------
/* Some text here */

2. Dependencies
--------------------------------------------------------------------
For compiling and obtaining the .scad files the Object Oriented Mechanics Library (OOML) for C++ is needed.
You can download it here:

 * [OOML](http://iearobotics.com/oomlwiki/doku.php?id=start)

For obtaining the stl files from the .scad files, OpenSCAD is needed.
You can find it here:

 * [OpenSCAD](http://www.openscad.org/)


3. Usage:
---------------------------------------------------------
* Edit the file "./HARDWARE/CMakeLists.txt" to include the path to the OOML include directory.
* Build it using cmake:

`mkdir build`						<br>
`cd build` 						<br>
`cmake ..`						<br>
`make`							<br>

* Execute the program **REPY-2.0**, that will create the openscad files and, optionally, the stl files
for the REPY-2.0 module.

4. Version log
-----------------------------------------------------------

 * Version **1.0** (first version): module finished and tested, but needs some fixes.
 * Version **0.9** (pre-release): module finished, but not tested yet.
 


