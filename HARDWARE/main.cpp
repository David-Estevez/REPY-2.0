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
#include "repy_lower.h"

using namespace std;

int main()
{

 REPY_lower lower_part;

 Component result = lower_part;

 //--------------------------------------------

 //UPDATE THE CODE FOR UPPER PART!!

 //--------------------------------------------

 /*This is for the upper part

 result = result + result02;*/

 //-- Printing the result
 IndentWriter writer;
 writer << result;
 cout << writer << endl << endl;
 ofstream file("REPY-2.0_lower.scad");
         if (file)
         {
             file << "//-------------------------------------------------------------------------" << endl;
             file << "//-- REPY-2.0_lower.scad" << endl;
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

