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

struct Point _2ndDegree(double a, double b, double c)
{
    struct Point solution;
    solution.x = (-b + sqrt( pow(b, 2) -4*a*c)) / (2*a);
    solution.y = (-b - sqrt( pow(b, 2) -4*a*c)) / (2*a);
    return solution;
}
struct Point tang_points(double origin_x, double origin_y, double center_x, double center_y, double radius, bool leftmost)
{

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

    //-- Create the ear shape
    Polygon<Point2D> shape;
    shape.addPoint(Point2D(0,0));
    shape.addPoint(Point2D(ear.base/2, 0));
    shape.addPoint(Point2D(ear.base/2, ear.no_name));

    //-- Compute tangent points
    struct Point tang[2];
    tang[0] = tang_points(ear.base/2, ear.no_name, 0, ear.height, ear.corona_r, true);
    tang[1] = tang_points(-ear.base/2, ear.no_name, 0, ear.height, ear.corona_r, false);
    shape.addPoint(Point2D(tang[0].x,tang[0].y));
    shape.addPoint(Point2D(tang[1].x,tang[1].y));

    //-- Remaining points
    shape.addPoint(Point2D(-ear.base/2, ear.no_name));
    shape.addPoint(Point2D(-ear.base/2, 0));

    //-- Extrude the ear shape
    Component ear_shape = PolygonalPrism(shape, ear.thickness);

    Component ear_result = corona + ear_shape;

    writer << ear_result;

    cout << writer;
}

int main()
{
    struct Base base = {52, 4, 15, 15, 3/2, 40, 20};

    //part01( base);

    //part02(ear);

    //cout << "Done!" << endl;

    return 0;

}

