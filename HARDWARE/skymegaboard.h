//------------------------------------------------------
//-- REPY-2.0
//------------------------------------------------------

//------------------------------------------------------
//-- Author: David Estevez (DEF)
//------------------------------------------------------
//-- Based on REPY module, by
//-- Juan Gonzalez-Gomez (Obijuan)
//------------------------------------------------------

#ifndef SKYMEGABOARD_H
#define SKYMEGABOARD_H

#include <ooml/core.h>
#include <ooml/components.h>

class SkyMegaBoard : public AbstractPart
{
public:
    SkyMegaBoard();

    //-- Data interface:
    //---------------------------
    double get_thickness();
    double get_side();
    double get_drill_diam();
    double get_drill_x();
    double get_drill_y();

protected:
    virtual Component build();

private:
    //-- Dimensions
    double thickness;
    double side;
    double drill_diam;
    double drill_x;
    double drill_y;

};

#endif // SKYMEGABOARD_H
