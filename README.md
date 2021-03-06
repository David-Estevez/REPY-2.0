REPY-2
=========================================================

Symmetric module for modular robots.

* Author: [David Estevez-Fernandez (DEF)](http://www.thingiverse.com/DEF)

* This work is based on REPY module, by Juan Gonzalez-Gomez (Obijuan): <br/>
[Juan Gonzalez-Gomez (Obijuan) on Thingiverse](http://www.thingiverse.com/Obijuan) <br/>
[Juan Gonzalez-Gomez (Obijuan) on Github](https://github.com/Obijuan)

<img src="http://www.dsquaredrobotics.com/wiki/lib/exe/fetch.php?cache=&media=wiki:othersdef:bach_thesis:hardware_repy_2_1_real.jpg" alt="Version 2.1" width="300" /> 

More information about REPY-2 module on:

* [d-squared:wiki - REPY-2.1](http://www.dsquaredrobotics.com/wiki/doku.php?id=en:repy-2.1)
* [d-squared:wiki - REPY-2.0](http://www.dsquaredrobotics.com/wiki/doku.php?id=en:repy-2.0)

This module was part of my Bachelor's Thesis work:

* [Bachelor's Thesis](http://www.dsquaredrobotics.com/wiki/doku.php?id=en:bachelor_thesis_def)

More information about Juan Gonzalez-Gomez's work on

* [Thingiverse - REPY v1.1](http://www.thingiverse.com/thing:13442)
* [iearobotics - REPY v1.1 (Spanish)]( http://www.iearobotics.com/wiki/index.php?title=M%C3%B3dulos_REPY-1)

Index
-------------------------------------------------------------------
 * 1.Printing instructions
 * 2.Developing / customizing REPY-2.0
     * 2.1. Dependencies
     * 2.2. Compiling
     * 2.3. Doxygen documentation
     * 2.4. More info
 * 3.Version log


1. Printing instructions
--------------------------------------------------------------------
Ready-to-print stl files can be found in the stl folder. Choose them accordingly to the servo and horn to be used. 

Not all of them have been printed and tested. At this moment only the following ones are validated:

* **REPY-2.0 for Fake Futaba 3003s servo**: lower part and rounded, 4-arms and 6-arms horns.
* **REPY-2.0 for Tower Pro sg90 servo**: lower part and 2-arms horn.

If you print one that is not in the list of validated ones, please let me know if it works or not, to fix the file or add it to the list.

2. Developing / customizing REPY-2.0
--------------------------------------------------------------------
### 2.1. Dependencies ###
For compiling and obtaining the .scad files the Object Oriented Mechanics Library (OOML) for C++ is needed.
You can download and install it from here:

 * [OOML](http://iearobotics.com/oomlwiki/doku.php?id=start)

For obtaining the stl files from the .scad files, OpenSCAD is needed.
You can find it here:

 * [OpenSCAD](http://www.openscad.org/)

### 2.2. Compiling ###
* Edit the file "CMakeLists.txt" to include the path to the OOML include directory.For example, in my system this path was "/usr/include/ooml".
* Open a terminal, go to the REPY-2.0 directory and build it using cmake:
        
        $ mkdir build
        $ cd build
        $ cmake ..
        $ make 
        $ make install

Notice that for the installation you won't need to be superuser, as it is installed in a directory called 'bin' in the REPY-2.0 folder.

* Execute the program **REPY-2.0**, that will create the openscad files and, optionally, the stl files
for the REPY-2.0 module.

### 2.3. Doxygen documentation ###
Doxygen documentation can be found on [Doxygen documentation](http://www.dsquaredrobotics.com/wiki/index.php?title=REPY-2.0#Doxygen_documentation).

### 2.4. More info ###
Info about the current version of the module (REPY-2.1) can be found [here](http://www.dsquaredrobotics.com/wiki/index.php?title=REPY-2.1)

More info for developers can be found on the [d-Squared:robotics wiki](http://www.dsquaredrobotics.com/wiki/index.php?title=REPY-2.0#Developer.27s_manual).

4. Version log
-----------------------------------------------------------
 * Version **2.1** (thesis): added side connectors to the modules, dimensions fixed.
 * Version **1.1** (release): module fixed and tested.
 * Version **1.0** (prototype): module finished and tested, but needs some fixes.
 * Version **0.9** (pre-release): module finished, but not tested yet.
