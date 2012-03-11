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

int main()
{
 Base  base( 52, 4, 15, 15, 3/2);
 base.add_cross( 20, 40);
 Component base_prime = base.build();
 base_prime.translate(10,10,10);

 Ear ear(50, 10, 50, 25/2, 4);
 ear.add_drill(3/2);


 Component result = base_prime + ear.build();

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

