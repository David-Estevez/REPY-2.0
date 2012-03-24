//------------------------------------------------------
//-- REPY-2.0
//------------------------------------------------------
//-- This component is the 'ear' of a REPY module.
//-- It is completely parametric, so one can build
//-- a module to fit their own needs.
//-- There are several configurations available,
//-- including reinforced 'ear'.
//------------------------------------------------------
//-- Author: David Estevez (DEF)
//------------------------------------------------------
//-- Based on REPY module, by
//-- Juan Gonzalez-Gomez (Obijuan)
//------------------------------------------------------

#include <ooml/core.h>
#include <ooml/components.h>
#include <iostream>
#include <math.h>

#include "ear.h"


/*Point type*/

struct Point
{
    double x;
    double y;
};

//-- Auxiliar funcions (mainly for finding tangent points

double _2ndDegree(double a, double b, double c, bool negative)
{
    double solution;
    if (pow(b,2) - 4*a*c < 0)
        std::cerr << "Error. No solutions for 2nd order eq. " << std::endl;
    if (negative) solution = (-b - sqrt( pow(b, 2) -4*a*c)) / (2*a);
    else solution = (-b + sqrt( pow(b, 2) -4*a*c)) / (2*a);
    return solution;
}

struct Point tang_point(double origin_x, double origin_y, double center_x, double center_y, double radius, bool leftmost)
{
        //-- Get the line where the tangent points should be
        double m = (center_x - origin_x) / (origin_y - center_y);
        double n = -center_x * m + center_y + pow(radius ,2)/(origin_y-center_y);

        //-- There must be two tangential points
        struct Point tangent[2];
        struct Point dummy[4];  //-- Dummy variable for storing solutions

        //-- Obtain potential solutions
        dummy[0].x = _2ndDegree( pow(m, 2)+1, 2*(m*n - m*center_y - center_x), pow(center_x, 2) + pow(n, 2) -2*center_y*n + pow(center_y, 2) - pow( radius, 2) , false);
        dummy[0].y = _2ndDegree( 1, -2*center_y, pow( (dummy[0].x - center_x), 2) + pow(center_y, 2) - pow(radius, 2), false);
        dummy[1].x = dummy[0].x;
        dummy[1].y = _2ndDegree( 1, -2*center_y, pow( (dummy[1].x - center_x), 2) + pow(center_y, 2) - pow(radius, 2), true);
        dummy[2].x = _2ndDegree( pow(m, 2)+1, 2*(m*n - m*center_y - center_x), pow(center_x, 2) + pow(n, 2) -2*center_y*n + pow(center_y, 2) - pow( radius, 2) , true);
        dummy[2].y = _2ndDegree( 1, -2*center_y, pow( (dummy[2].x - center_x), 2) + pow(center_y, 2) - pow(radius, 2), false);
        dummy[3].x = dummy[2].x;
        dummy[3].y = _2ndDegree( 1, -2*center_y, pow( (dummy[3].x - center_x), 2) + pow(center_y, 2) - pow(radius, 2), true);

        int solutions = 0; //-- Solutions already found
        int i = 0;

        while (solutions < 2 && i < 4)
        {
           double check = m*dummy[i].x + n - dummy[i].y; //Belongs to the line?

           if ( check < 0.00001 && check >-0.00001) //-- Check if it is aproximately 0
           {
               tangent[solutions].x = dummy[i].x;
               tangent[solutions].y = dummy[i].y;
               solutions++;
           }
           i++;
         }

        //-- Choose leftmost or rightmost solution
         if (leftmost)
        {
             if (tangent[0].x < tangent[1].x)
                 return tangent[0];
             else
                 return tangent[1];
         }
         else
         {
             if (tangent[0].x > tangent[1].x)
                 return tangent[0];
             else
                 return tangent[1];
         }
 }


//-- Class members
//----------------------------------------

Ear::Ear(): AbstractPart()
{
    _base = 50;
    _shift = 10;
    _height = 50;
    _corona_r = 25/2;
    _thickness = 4;

    //-- Optional parameters
    _drill_r = 0;
    _reinf_thickness = 0;
    build();
}

Ear::Ear( double base, double shift, double height, double corona_r, double thickness): AbstractPart()
{
    _base = base;
    _shift = shift;
    _height = height;
    _corona_r = corona_r;
    _thickness = thickness;

    //-Optional parameters
    _drill_r = 0;
    _reinf_thickness = 0;

    build();
 }

Component Ear::build()
{
    //-- Compute the servo's corona circle
    Component2D corona = Circle::create(_corona_r, 100);
    corona.translate(0, _height, 0);

    //-- Create the ear shape
    Polygon<Point2D> shape;
    shape.addPoint(Point2D(0,0));
    shape.addPoint(Point2D(_base/2, 0));
    shape.addPoint(Point2D(_base/2, _shift));

    //-- Compute tangent points
    struct Point tang[2];
    tang[0] = tang_point(_base/2, _shift, 0, _height, _corona_r, false);
    tang[1] = tang_point(-_base/2, _shift, 0, _height, _corona_r, true);

    shape.addPoint(Point2D(tang[0].x,tang[0].y));
    shape.addPoint(Point2D(tang[1].x,tang[1].y));

    //-- Remaining points
    shape.addPoint(Point2D(-_base/2, _shift));
    shape.addPoint(Point2D(-_base/2, 0));

    //-- Extrude the ear shape
    Component ear_shape = PolygonalPrism(shape, _thickness);
    Component ear_extrude = corona.linearExtrudedCopy(_thickness,0,100,10,false);

    //-- Make the drill for the axis if needed
    if (_drill_r != 0)
    {
        if ( _drill_r == _drill_r_big)
            {
             Component hole = Cylinder::create( _drill_r, _thickness + 0.1);
             hole.translate(0, _height, _thickness/2);
             ear_shape = ear_shape - hole;
            }
        else
            {
            //-- This is the hole with the shape for the screw head
            }
    }

    //-- Final shape
    Component ear_result = ear_extrude + ear_shape;

    //--Add the reinforcement if needed
    if (_reinf_thickness != 0 )
        {
        Component reinf_shape = PolygonalPrism(shape, _reinf_thickness);
        Component reinf_extrude = corona.linearExtrudedCopy(_reinf_thickness,0,100,10,false);
        Component reinforcement = reinf_shape - reinf_extrude;
        reinforcement.translate(0,0,_thickness);
        ear_result = ear_result + reinforcement;
        }

    return ear_result;

}

//-- Add the drill for the axis/servo corona
void Ear::add_drill( double radius, double radius_big)
{
    _drill_r = radius;
    if (radius_big == -1)
        _drill_r_big = radius;
    else
        _drill_r_big = radius_big;

}

//-- Add an extra layer as reinforcement
void Ear::add_reinforcement( double thickness)  { _reinf_thickness = thickness;}
