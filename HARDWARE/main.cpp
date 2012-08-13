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
    bool render_assembly = true;

    if( render_lower )
    {
        REPY_lower lower_part;
        lower_part.showServo(false);

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

    if ( render_upper )
    {
        REPY_upper upper_part;
        upper_part.hornType(6);

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

    if ( render_assembly )
    {
        REPY_upper upper_part;
        REPY_lower lower_part;

        lower_part.showServo(true);
        upper_part.showHorn(true);
        upper_part.hornType(6);

        Component rotated_upper_part = upper_part.translate(0,0,-(SERVO_AXIS_Y+SERVO_LEG_Y+/*thickness_base*/4/2))
                                                 .rotate(0, 180, 0)
                                                 .translate(0,0, (SERVO_AXIS_Y+SERVO_LEG_Y+/*thickness_base*/4/2));
        //-- Assembly
        Component assembly = rotated_upper_part + lower_part;

        //-- Printing the upper part
        IndentWriter writer_assembly;
        writer_assembly << assembly;
        //cout << writer_assembly << endl << endl;

        ofstream file_assembly("REPY-2.0_assembly.scad");
        if (file_assembly)
        {
            file_assembly << "//-------------------------------------------------------------------------" << endl;
            file_assembly << "//-- REPY-2.0_assembly.scad" << endl;
            file_assembly << "//-------------------------------------------------------------------------" << endl;
            file_assembly << "//--This file has been generated automatically according to your data."<< endl;
            file_assembly << "//--For more info, visit: http://iearobotics.com/oomlwiki/"<< endl;
            file_assembly << "//--------------------------------------------------------------------------" << endl << endl;
            file_assembly << writer_assembly;
            file_assembly.close();
            cout << "Assembly saved succesfully." << endl;
        }
        else
        {
            cerr << "Error, cannot open the file" << endl;
        }
    }

    if (false) //-- Render rounded horn
    {
        //-- Render horn
        Servo_Horn_rounded horn(25/2.0-2.5);

        //-- Printing the upper part
        IndentWriter writer_horn;
        writer_horn << horn;
        //cout << writer_horn << endl << endl;

        ofstream file_horn("REPY-2.0_horn.scad");
        if (file_horn)
        {
            file_horn << "//-------------------------------------------------------------------------" << endl;
            file_horn << "//-- REPY-2.0_horn.scad" << endl;
            file_horn << "//-------------------------------------------------------------------------" << endl;
            file_horn << "//--This file has been generated automatically according to your data."<< endl;
            file_horn << "//--For more info, visit: http://iearobotics.com/oomlwiki/"<< endl;
            file_horn << "//--------------------------------------------------------------------------" << endl << endl;
            file_horn << writer_horn;
            file_horn.close();
            cout << "Horn part saved succesfully." << endl;
        }
        else
        {
            cerr << "Error, cannot open the file" << endl;
        }
    }

    if (false) //-- Render arms horn
    {
        //-- Render horn
        Servo_Horn_arms horn(4);

        //-- Printing the upper part
        IndentWriter writer_horn;
        writer_horn << horn;
        //cout << writer_horn << endl << endl;

        ofstream file_horn("REPY-2.0_horn.scad");
        if (file_horn)
        {
            file_horn << "//-------------------------------------------------------------------------" << endl;
            file_horn << "//-- REPY-2.0_horn.scad" << endl;
            file_horn << "//-------------------------------------------------------------------------" << endl;
            file_horn << "//--This file has been generated automatically according to your data."<< endl;
            file_horn << "//--For more info, visit: http://iearobotics.com/oomlwiki/"<< endl;
            file_horn << "//--------------------------------------------------------------------------" << endl << endl;
            file_horn << writer_horn;
            file_horn.close();
            cout << "Horn part saved succesfully." << endl;
        }
        else
        {
            cerr << "Error, cannot open the file" << endl;
        }
    }


    return 0;

}

