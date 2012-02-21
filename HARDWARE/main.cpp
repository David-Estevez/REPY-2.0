// Base for REPY module
// Author: David Estévez (DEF)

#include <ooml/core.h>
#include <ooml/components.h>
#include <iostream>
#include <fstream>
#include <math.h>

using namespace std;

struct Point
{
    double x;
    double y;
};
struct Base
{
    double side;
    double thickness;
    double drill_x;
    double drill_y;
    double drill_r;
    double cross_small;
    double cross_large;
};
struct Ear
{
    double base;
    double no_name;
    double height;
    double corona_r;
    double drill_r;
    double thickness;

};

double _2ndDegree(double a, double b, double c, bool negative)
{
    double solution;
    if (pow(b,2) - 4*a*c < 0)
        cerr << "Error. No solutions for 2nd order eq. " << endl;
    if (negative) solution = (-b - sqrt( pow(b, 2) -4*a*c)) / (2*a);
    else solution = (-b + sqrt( pow(b, 2) -4*a*c)) / (2*a);
    return solution;
}

struct Point tang_points(double origin_x, double origin_y, double center_x, double center_y, double radius, bool leftmost)
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
           double check = pow( (dummy[i].x - center_x), 2) + pow( (dummy[i].y - center_y), 2) - pow(radius, 2);

           if ( check < 0.0001 && check >-0.0001) //-- Check if it is aproximately 0
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


void part01(struct Base base)
{
    IndentWriter writer;
    Component contour = Cube::create(base.side, base.side, base.thickness);

    Component cross01 = Cube::create(base.cross_small, base.cross_large, base.thickness + 0.1);
    Component cross02 = Cube::create(base.cross_large, base.cross_small, base.thickness + 0.1);

    Component drill01 = Cylinder::create( base.drill_r, base.thickness+0.1, 20, true);
    drill01.translate( base.drill_x, base.drill_y, 0);

    Component drill02 = Cylinder::create( base.drill_r, base.thickness+0.1, 20, true);
    drill02.translate( base.drill_x, -base.drill_y, 0);

    Component drill03 = Cylinder::create( base.drill_r, base.thickness+0.1, 20, true);
    drill03.translate( -base.drill_x, base.drill_y, 0);

    Component drill04 = Cylinder::create( base.drill_r, base.thickness+0.1, 20, true);
    drill04.translate( -base.drill_x, -base.drill_y, 0);

    Component holes = drill01 + drill02 + drill03 + drill04;

    Component foot = contour - cross01 - cross02 - holes;

    writer << foot;

    ofstream file("base.scad");
            if (file)
            {
                file << "//-------------------------------------------------------------------------" << endl;
                file << "//-- base.scad" << endl;
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

}
void part02(struct Ear ear)
{
    IndentWriter writer;

    //-- Compute the servo's corona circle
    Component2D corona = Circle::create(ear.corona_r, 100);
    corona.translate(0, ear.height, 0);

    //-- Create the ear shape
    Polygon<Point2D> shape;
    shape.addPoint(Point2D(0,0));
    shape.addPoint(Point2D(ear.base/2, 0));
    shape.addPoint(Point2D(ear.base/2, ear.no_name));

    //-- Compute tangent points
    struct Point tang[2];
    tang[0] = tang_points(ear.base/2, ear.no_name, 0, ear.height, ear.corona_r, false);
    tang[1] = tang_points(-ear.base/2, ear.no_name, 0, ear.height, ear.corona_r, true);
    shape.addPoint(Point2D(tang[0].x,tang[0].y));
    shape.addPoint(Point2D(tang[1].x,tang[1].y));

    //-- Remaining points
    shape.addPoint(Point2D(-ear.base/2, ear.no_name));
    shape.addPoint(Point2D(-ear.base/2, 0));

    //-- Extrude the ear shape
    Component ear_shape = PolygonalPrism(shape, ear.thickness);
    Component ear_extrude = corona.linearExtrudedCopy(ear.thickness,0,100,10,false);
    Component ear_result = ear_extrude + ear_shape;

    writer << ear_result;

    cout << writer;
}

int main()
{
    struct Base base = {52, 4, 15, 15, 3/2, 40, 20};
    struct Ear ear = { 50, 10, 50, 25/2, 3/2, 4};

    //part01( base);

    part02(ear);
    //cout << _2ndDegree( 2 , 4, -5, true) << endl << _2ndDegree(2,4,-5,false);
    //cout << "Done!" << endl;

    return 0;

}

