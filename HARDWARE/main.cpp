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
#include "repy_upper.h"

using namespace std;

int main()
{
    //-- Variables for choosing what to output
    bool render_lower = true;
    bool render_upper = true;

    if( render_lower )
    {
        REPY_lower lower_part;

        //-- Printing the lower part
        IndentWriter writer_lower;
        writer_lower << lower_part;
        //cout << writer_lower << endl << endl;

        ofstream file_lower("REPY-2.0_lower.scad");
        if (file_lower)
        {
            file_lower << "//-------------------------------------------------------------------------" << endl;
            file_lower << "//-- REPY-2.0_lower.scad" << endl;
            file_lower << "//-------------------------------------------------------------------------" << endl;
            file_lower << "//--This file has been generated automatically according to your data."<< endl;
            file_lower << "//--For more info, visit: http://iearobotics.com/oomlwiki/"<< endl;
            file_lower << "//--------------------------------------------------------------------------" << endl << endl;
            file_lower << writer_lower;
            file_lower.close();
            cout << "Lower part saved succesfully." << endl;
        }
        else
        {
            cerr << "Error, cannot open the file" << endl;
        }
    }

    if ( render_upper)
    {
        REPY_lower upper_part;

        //-- Printing the upper part
        IndentWriter writer_upper;
        writer_upper << upper_part;
        //cout << writer_upper << endl << endl;

        ofstream file_upper("REPY-2.0_upper.scad");
        if (file_upper)
        {
            file_upper << "//-------------------------------------------------------------------------" << endl;
            file_upper << "//-- REPY-2.0_upper.scad" << endl;
            file_upper << "//-------------------------------------------------------------------------" << endl;
            file_upper << "//--This file has been generated automatically according to your data."<< endl;
            file_upper << "//--For more info, visit: http://iearobotics.com/oomlwiki/"<< endl;
            file_upper << "//--------------------------------------------------------------------------" << endl << endl;
            file_upper << writer_upper;
            file_upper.close();
            cout << "Upper part saved succesfully." << endl;
        }
        else
        {
            cerr << "Error, cannot open the file" << endl;
        }
    }

    return 0;

}

