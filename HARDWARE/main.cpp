//------------------------------------------------------
//-- REPY-2.0
//------------------------------------------------------
//-- This is an example that creates the two main parts
//-- that form a module: base and ear.
//------------------------------------------------------
//-- Author: David Estevez (DEF)
//------------------------------------------------------
//-- Based on REPY module, by
//-- Juan Gonzalez-Gomez (Obijuan)
//------------------------------------------------------

#include <ooml/core.h>
#include <ooml/components.h>
#include <iostream>
#include <fstream>

#include "ear.h"
#include "base.h"
#include "basic_servo.h"

using namespace std;

#define DRILL_X 30
#define DRILL_Y 30
#define DRILL_D 3

int main()
{

 //-- Parameters to be used:
 float side = 52;
 float thickness_base = 4;

 float thickness_ear01 = 4;
 float thickness_ear02 = 4;

 //-- Create the base
 Base  base( side, thickness_base, DRILL_X/2, DRILL_Y/2, DRILL_D/2.0);

 //-- Create the servo object to substract
 Basic_servo servo(true, 2 * thickness_ear01);
 servo.color(0.25,0.25,0.25);
 servo.rotate(90, 0, 180);
 servo.translate( 0, -(side/2 - 2 * thickness_ear01), SERVO_LEG_Y + thickness_base/2);

 //-- Create first ear
 Ear ear01(side , 12, SERVO_AXIS_Y + SERVO_LEG_Y, 38/2, thickness_ear01);
 ear01.add_drill(3/2 + 0.1);
 ear01.rotate(90,0,0);
 ear01.translate(0, - (side/2 - 2 * thickness_ear01), thickness_base/2);

 //-- Create second ear
 Ear ear02(side, 12, SERVO_AXIS_Y + SERVO_LEG_Y, 38/2, thickness_ear02);
 ear02.rotate(90,0,0);
 ear02.translate(0, SERVO_LEG_H + SERVO_LEG_Z/2 - (side/2 - 2 * thickness_ear01), thickness_base/2);

 //-- Add up all things
 Component result = base + ear01 + ear02 - servo;

 //-- Printing the result
 IndentWriter writer;
 writer << result;
 cout << writer << endl << endl;
 ofstream file("TEST01.scad");
         if (file)
         {
             file << "//-------------------------------------------------------------------------" << endl;
             file << "//-- TEST01.scad" << endl;
             file << "//-------------------------------------------------------------------------" << endl;
             file << "//--This file has been generated automatically according to your data."<< endl;
             file << "//--For more info, visit: http://iearobotics.com/oomlwiki/"<< endl;
             file << "//--------------------------------------------------------------------------" << endl << endl;
             file << writer;
             file.close();
         }
         else
         {
             cerr << "Error, cannot open the file" << endl;
         }
 return 0;

}

