#include "repy_module.h"

REPY_module::REPY_module(Basic_Servo& servo,  SkyMegaBoard& skymega)
{
    this->servo = &servo;
    this->skymega = &skymega;

    //-- Default dimensions:
    //-- General:
    board_safe = 1.5;
    //-- Lower part:
    lower_base_thickness = 4;

    rebuild();
}

Component REPY_module::build()
{
    Component lower = lower_part();
    return lower;
}

Component REPY_module::lower_part()
{
    //-- Create the base:
    //--------------------------------------------------------------------------------------------------
    //-- Base:
    Component base = Cube( skymega->getSide() + 2*board_safe, skymega->getSide() + 2*board_safe, lower_base_thickness);

    //-- Drills of the base:
    Component base_drill = Cylinder( skymega->getDrillDiam()/2.0, lower_base_thickness + 0.2);
    Component base_drill01 = base_drill.translatedCopy(  skymega->getDrillX()/2.0,  skymega->getDrillY()/2.0, 0);
    Component base_drill02 = base_drill.translatedCopy( -skymega->getDrillX()/2.0,  skymega->getDrillY()/2.0, 0);
    Component base_drill03 = base_drill.translatedCopy(  skymega->getDrillX()/2.0, -skymega->getDrillY()/2.0, 0);
    Component base_drill04 = base_drill.translatedCopy( -skymega->getDrillX()/2.0, -skymega->getDrillY()/2.0, 0);

    //-- Here should go the code for the apertures on the lower part, for wiring, etc --//

    //-- Make base:
    base = base - base_drill01 - base_drill02 - base_drill03 - base_drill04;

    //-- Edit servo:
    servo->rotate(90, 0 , 180);

    //-- Result:
    Component lower = base + *servo;
    return lower;

}
