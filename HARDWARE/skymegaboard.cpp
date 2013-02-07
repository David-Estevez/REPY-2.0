#include "skymegaboard.h"

//-- Default constructor
SkyMegaBoard::SkyMegaBoard()
{
    //-- Set dimensions:
    thickness = 3;
    side = 52;
    drill_diam = 3;
    drill_x = 30;
    drill_y = 30;

    rebuild();
}

//-- Data interface:
double SkyMegaBoard::getThickness() { return thickness; }
double SkyMegaBoard::getSide()	    { return side; }
double SkyMegaBoard::getDrillDiam() { return drill_diam; }
double SkyMegaBoard::getDrillX()    { return drill_x; }
double SkyMegaBoard::getDrillY()    { return drill_y; }


Component SkyMegaBoard::build()
{
    //-- PCB:
    Component pcb = RoundedTablet( side, side, thickness, side/20 );

    //-- Holes:
    Component hole_base = Cylinder( drill_diam/2.0, thickness + 0.1);
    Component hole01 = hole_base.translatedCopy(  drill_x/2.0,  drill_y/2.0, 0);
    Component hole02 = hole_base.translatedCopy( -drill_x/2.0,  drill_y/2.0, 0);
    Component hole03 = hole_base.translatedCopy(  drill_x/2.0, -drill_y/2.0, 0);
    Component hole04 = hole_base.translatedCopy( -drill_x/2.0, -drill_y/2.0, 0);
    Component holes = hole01 + hole02 + hole03 + hole04;

    //-- Make board:
    Component skymega = pcb - holes;

    //-- Add some links:
    //-- 4 for the upper side drills:
    skymega.addLink( RefSys(  drill_x/2.0,  drill_y/2.0, thickness/2.0));
    skymega.addLink( RefSys( -drill_x/2.0,  drill_y/2.0, thickness/2.0));
    skymega.addLink( RefSys(  drill_x/2.0, -drill_y/2.0, thickness/2.0));
    skymega.addLink( RefSys( -drill_x/2.0, -drill_y/2.0, thickness/2.0));

    //-- 4 for the lower side drills (looking downwards):
    skymega.addLink( RefSys(  drill_x/2.0,  drill_y/2.0, -thickness/2.0).relRotate(180,0,0));
    skymega.addLink( RefSys( -drill_x/2.0,  drill_y/2.0, -thickness/2.0).relRotate(180,0,0));
    skymega.addLink( RefSys(  drill_x/2.0, -drill_y/2.0, -thickness/2.0).relRotate(180,0,0));
    skymega.addLink( RefSys( -drill_x/2.0, -drill_y/2.0, -thickness/2.0).relRotate(180,0,0));

    //-- Put some color:
    skymega.color( 0.2, 0.2, 0.5);

    return skymega;
}
