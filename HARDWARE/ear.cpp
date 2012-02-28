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

/*Auxiliar funcions*/

double _2ndDegree(double a, double b, double c, bool negative)
{
    double solution;
    if (pow(b,2) - 4*a*c < 0)
        std::cerr << "Error. No solutions for 2nd order eq. " << std::endl;
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
    tang[0] = tang_points(_base/2, _shift, 0, _height, _corona_r, false);
    tang[1] = tang_points(-_base/2, _shift, 0, _height, _corona_r, true);

    shape.addPoint(Point2D(tang[0].x,tang[0].y));
    shape.addPoint(Point2D(tang[1].x,tang[1].y));

    //-- Remaining points
    shape.addPoint(Point2D(-_base/2, _shift));
    shape.addPoint(Point2D(-_base/2, 0));

    //-- Extrude the ear shape
    Component ear_shape = PolygonalPrism(shape, _thickness);
    Component ear_extrude = corona.linearExtrudedCopy(_thickness,0,100,10,false);
    Component ear_result = ear_extrude + ear_shape;

    return ear_result;

}
