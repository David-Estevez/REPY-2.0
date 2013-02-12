#include "repy_module.h"

REPY_module::REPY_module(Basic_Servo& servo,  SkyMegaBoard& skymega)
{
    this->servo = &servo;
    this->skymega = &skymega;

    //-- Default dimensions:
    //-- General:
    board_safe = 1.5;
    side = skymega.getSide() + 2* board_safe;

    //-- Lower part:
    lower_base_thickness = 4;
    lower_front_ear_thickness = 4;
    lower_back_ear_thickness = 4;
    lower_ear_shift = 12;
    lower_ear_radius = 38/2;

    //-- Upper part:
    upper_base_thickness = 4;
    upper_front_ear_thickness = 4;
    upper_back_ear_thickness = 4;


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
    Component base = Cube( side, side, lower_base_thickness);

    //-- Drills of the base:
    Component base_drill = Cylinder( skymega->getDrillDiam()/2.0, lower_base_thickness + 0.2);
    Component base_drill01 = base_drill.translatedCopy(  skymega->getDrillX()/2.0,  skymega->getDrillY()/2.0, 0);
    Component base_drill02 = base_drill.translatedCopy( -skymega->getDrillX()/2.0,  skymega->getDrillY()/2.0, 0);
    Component base_drill03 = base_drill.translatedCopy(  skymega->getDrillX()/2.0, -skymega->getDrillY()/2.0, 0);
    Component base_drill04 = base_drill.translatedCopy( -skymega->getDrillX()/2.0, -skymega->getDrillY()/2.0, 0);

    //-- Here should go the code for the apertures on the lower part, for wiring, etc --//

    //-- Make base:
    base = (base - base_drill01 - base_drill02 - base_drill03 - base_drill04).translate(0, 0, lower_base_thickness/2.0);

    //-- Place servo:
    servo->rotate(90, 0 , 180);
    servo->translate(0, 0, servo->get_leg_y() + lower_base_thickness);
    servo->translate( 0, -side/2.0 + upper_back_ear_thickness + lower_back_ear_thickness, 0);

    //-- Make ears:
    Component front_ear = make_ear( side, servo->get_axis_y()+servo->get_leg_y(), lower_front_ear_thickness,
				    lower_ear_shift, lower_ear_radius);
    front_ear.rotate( 90, 0, 0).translate( 0, 0, lower_base_thickness/2);


    //-- Result:
    Component lower = front_ear + base + *servo;
    return lower;

}

Component REPY_module::make_ear(double base, double height, double thickness, double shift, double radius)
{
    //-- Make shift:
    if (shift == 0) shift = 0.001;
    Component square = Cube( base, shift, thickness).translate( 0, shift/2.0, 0);
    Component circle = Cylinder( radius, thickness).translate(0, height, 0);

    return square & circle;
}
