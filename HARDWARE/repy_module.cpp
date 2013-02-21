#include "repy_module.h"

REPY_module::REPY_module(BasicServo& servo,  SkyMegaBoard& skymega)
{
    this->servo = &servo;
    this->skymega = &skymega;

    //-- Default dimensions:
    //-- General:
    board_safe = 1.5;

    //-- Lower part:
    lower_base_thickness = 4;
    lower_front_ear_thickness = 4;
    lower_back_ear_thickness = 4;
    lower_ear_shift = 12;
    lower_ear_radius = 38/2.0;
    lower_screw_safe = 5;
    lower_border_safe = 7;


    //-- Upper part:
    upper_base_thickness = 4;
    upper_front_ear_thickness = 4;
    upper_back_ear_thickness = 4;
    upper_ear_shift = 12;
    upper_ear_radius = 38/2.0;
    upper_screw_safe = 5;
    upper_border_safe = 7;

    //-- Default flags:
    show_servo = true;
    show_assembly = true;
    show_lower = true;
    show_upper = true;

    rebuild();
}

Component REPY_module::build()
{

    //-- Choose horn:
    this->servo->set_horn( 4);

    //-- Calculate other useful dimensions:
    //-------------------------------------------------------------------------------------------
    //--Total side:
    side = skymega->getSide() + 2* board_safe;

    //-- Calculate the dimensions of the central part (not to be confused with central park):
    central_part = ( servo->get_height() + lower_back_ear_thickness + upper_back_ear_thickness) +
		   ( upper_front_ear_thickness) +
		   ( servo->get_horn_dist_axis() - servo->get_horn_h_axis() );

    //-- Place servo:
    servo->rotate(90, 0 , 180);
    servo->translate(0, 0, servo->get_leg_y() + lower_base_thickness);
    servo->translate( 0, -central_part/2.0 + upper_back_ear_thickness + lower_back_ear_thickness, 0);

    //-- Make fake axis screw:
    fake_axis =  Cylinder( 6/2.0, 2 + 0.2 , 100, false)
	      + Cylinder( 3/2.0, lower_back_ear_thickness + upper_back_ear_thickness - 2 + 0.1, 100, false).relTranslate( 0, 0, 2 + 0.1);
    fake_axis.color( 0.5, 0.5, 0.5);

    //! \todo Change this to something that uses links:
    //--
    fake_axis.moveToLink( *servo, 0);
    fake_axis.translate( 0 , upper_front_ear_thickness - servo->get_horn_h_axis() -central_part -0.1, 0);

    //--Compose the module:
    //-------------------------------------------------------------------------------------------
    Component lower = lower_part();
    Component upper = upper_part();
    Component result;

    if ( show_assembly )
	result = lower + upper.rotate(0,180,0).translate(0,0,2*(servo->get_axis_y()+servo->get_leg_y())+lower_base_thickness+upper_base_thickness) ;
    else
	if ( show_lower && show_upper)
	    result = lower.translate( - side/2.0 - 2, 0, 0) + upper.translate( side/2.0 + 2, 0, 0);
	else if (show_upper)
	    result = upper;
	else
	    result = lower;

    //! \todo change this
   return result;
}

Component REPY_module::lower_part()
{
    //-- Create the base:
    //--=======================================================================================================
    //-- Base:
    //------------------------------------------------------------------------------------------------------
    Component base = RoundedTablet( side, side, lower_base_thickness, board_safe);

    //-- Drills of the base:
    //------------------------------------------------------------------------------------------------------
    Component base_drill = Cylinder( skymega->getDrillDiam()/2.0, lower_base_thickness + 0.2);
    Component base_drill01 = base_drill.translatedCopy(  skymega->getDrillX()/2.0,  skymega->getDrillY()/2.0, 0);
    Component base_drill02 = base_drill.translatedCopy( -skymega->getDrillX()/2.0,  skymega->getDrillY()/2.0, 0);
    Component base_drill03 = base_drill.translatedCopy(  skymega->getDrillX()/2.0, -skymega->getDrillY()/2.0, 0);
    Component base_drill04 = base_drill.translatedCopy( -skymega->getDrillX()/2.0, -skymega->getDrillY()/2.0, 0);

    //-- Aperture on the lower base for wiring, etc
    //-------------------------------------------------------------------------------------------------------
    //-- Wiring_hole_x_thickness: 'y' component of the hole under the servo body along the x axis
    double wiring_hole_x_thickness = (-central_part/2.0 + lower_back_ear_thickness + upper_back_ear_thickness + servo->get_leg_h() - lower_front_ear_thickness)
				   + (  skymega->getDrillY()/2.0 - skymega->getDrillDiam()/2.0 - lower_screw_safe);

    //-- Wiring_hole_y_thickness: 'y' component of the hole under the servo body along the y axis
    double wiring_hole_y_thickness = (-central_part/2.0 + lower_back_ear_thickness + upper_back_ear_thickness + servo->get_leg_h() - lower_front_ear_thickness)
				   + ( central_part/2.0 - lower_back_ear_thickness - upper_back_ear_thickness);

    //-- Wiring_hole_leg_thickness: 'y' component of the hole under the servo leg
    double wiring_hole_leg_thickness = ( side/2.0 - lower_border_safe )
				     - ( -central_part/2.0 + lower_back_ear_thickness + upper_back_ear_thickness + servo->get_leg_h() + servo->get_leg_z() );

			    //-- Hole under the servo body, part along X axis
    Component wiring_hole = RoundedTablet( side - 2*lower_border_safe, wiring_hole_x_thickness, lower_base_thickness+0.1, lower_border_safe / 2.5)
			    .translate(0, -wiring_hole_x_thickness/2.0 -central_part/2.0 + lower_back_ear_thickness + upper_back_ear_thickness + servo->get_leg_h() - lower_front_ear_thickness, 0)
			    //-- Hole under the servo body, part along y axis
			  + RoundedTablet( skymega->getDrillX() - skymega->getDrillDiam() - 2*lower_screw_safe, wiring_hole_y_thickness, lower_base_thickness+0.1, lower_border_safe/2.5 )
			    .translate(0,  -wiring_hole_y_thickness/2.0 -central_part/2.0 + lower_back_ear_thickness + upper_back_ear_thickness + servo->get_leg_h() - lower_front_ear_thickness, 0)
			    //-- Hole under the servo leg
			  + RoundedTablet( skymega->getDrillX() - skymega->getDrillDiam() - lower_screw_safe*2, wiring_hole_leg_thickness, lower_base_thickness + 0.1, lower_border_safe/3.0)
			    .translate(0, wiring_hole_leg_thickness/2.0 + ( -central_part/2.0 + lower_back_ear_thickness + upper_back_ear_thickness + servo->get_leg_h() + servo->get_leg_z() ), 0);
    //-- Make base:
    //-----------------------------------------------------------------------------------------------------------
    base = base - base_drill01 - base_drill02 - base_drill03 - base_drill04 - wiring_hole;
    base.translate(0, 0, lower_base_thickness/2.0);



    //-- Make ears:
    //--=========================================================================================================
    //-- Front ear:
    //-----------------------------------------------------------------------------------------------------------
    Component front_ear = make_ear( side, servo->get_axis_y()+servo->get_leg_y(), lower_front_ear_thickness,
				    lower_ear_shift, lower_ear_radius);
    front_ear.rotate( 90, 0, 0).translate( 0, 0, lower_base_thickness);
    front_ear.translate(0, -lower_front_ear_thickness/2.0 , 0);
    front_ear.translate(0, -central_part/2.0 + lower_back_ear_thickness + upper_back_ear_thickness + servo->get_leg_h() , 0);

    //-- Back ear:
    //-----------------------------------------------------------------------------------------------------------
    Component back_ear = make_ear( side, servo->get_axis_y() + servo->get_leg_y(),lower_back_ear_thickness,
				   lower_ear_shift, lower_ear_radius);
    back_ear.rotate(90, 0, 0).translate( 0, 0, lower_base_thickness);
    back_ear.translate(0, -central_part/2.0 + lower_back_ear_thickness/2.0 + upper_back_ear_thickness , 0);

    //-- Make front ear drills:
    //------------------------------------------------------------------------------------------------------------
    Component ear_drills[4];
    for (int i = 1; i <5 ; i++)
	ear_drills[i-1] =  Cylinder( servo->get_hole_r(), servo->get_leg_z() + lower_front_ear_thickness + 0.2 , 100, false)
					.moveToLink(*servo, i).relTranslate(0, 0, -servo->get_leg_z()/2.0 - lower_front_ear_thickness - 0.1);

    front_ear = front_ear - (ear_drills[0] & ear_drills[1]) - ear_drills[2] - ear_drills[3];


    //-- Result:
    //--===========================================================================================================
    Component lower = front_ear + back_ear + base - *servo - fake_axis;

    if (show_servo)
	lower = lower + *servo;

    //-- Add links to the holes of the base:
    //-------------------------------------------------------------------------------------------------------------
    lower.addLink( RefSys(  skymega->getDrillX()/2.0,  skymega->getDrillY()/2.0, 0));
    lower.addLink( RefSys( -skymega->getDrillX()/2.0,  skymega->getDrillY()/2.0, 0));
    lower.addLink( RefSys(  skymega->getDrillX()/2.0, -skymega->getDrillY()/2.0, 0));
    lower.addLink( RefSys( -skymega->getDrillX()/2.0, -skymega->getDrillY()/2.0, 0));

    return lower;

}

Component REPY_module::upper_part()
{
    //-- Base:
    Component base = RoundedTablet( side, side, upper_base_thickness, board_safe);

    //-- Drills of the base:
    Component base_drill = Cylinder( skymega->getDrillDiam()/2.0, upper_base_thickness + 0.2);
    Component base_drill01 = base_drill.translatedCopy(  skymega->getDrillX()/2.0,  skymega->getDrillY()/2.0, 0);
    Component base_drill02 = base_drill.translatedCopy( -skymega->getDrillX()/2.0,  skymega->getDrillY()/2.0, 0);
    Component base_drill03 = base_drill.translatedCopy(  skymega->getDrillX()/2.0, -skymega->getDrillY()/2.0, 0);
    Component base_drill04 = base_drill.translatedCopy( -skymega->getDrillX()/2.0, -skymega->getDrillY()/2.0, 0);

    //-- Make a cross-shaped hole for the wiring, etc:
    Component cross = RoundedTablet( skymega->getDrillY() - 2* upper_screw_safe  - skymega->getDrillDiam(),
			    side-2*upper_border_safe,
			    upper_base_thickness+0.2,
			    upper_border_safe /2.5)
		    + RoundedTablet( side-2*upper_border_safe,
			    skymega->getDrillX() - 2* upper_screw_safe - skymega->getDrillDiam(),
			    upper_base_thickness+0.2,
			    upper_border_safe /2.5 );

    //-- Make base:
    base = base - base_drill01 - base_drill02 - base_drill03 - base_drill04 - cross;
    base.translate(0, 0, lower_base_thickness/2.0);

    //-- Make ears:
    Component front_ear = make_ear( side, servo->get_axis_y()+servo->get_leg_y(), upper_front_ear_thickness,
				    upper_ear_shift, upper_ear_radius);
    front_ear.relRotate( 90, 0 , 0);
    front_ear.translate(0, (central_part - upper_front_ear_thickness )/2.0, 0);

    Component back_ear = make_ear( side, servo->get_axis_y()+servo->get_leg_y(), upper_back_ear_thickness,
				    upper_ear_shift, upper_ear_radius);
    back_ear.relRotate( 90, 0 , 0);
    back_ear.translate( 0, (-central_part + upper_back_ear_thickness)/2.0, 0);

    //-- Construct upper part:
    Component upper = base + front_ear + back_ear - *servo - fake_axis;

    //-- Add links to the holes of the base:
    upper.addLink( RefSys(  skymega->getDrillX()/2.0,  skymega->getDrillY()/2.0, 0));
    upper.addLink( RefSys( -skymega->getDrillX()/2.0,  skymega->getDrillY()/2.0, 0));
    upper.addLink( RefSys(  skymega->getDrillX()/2.0, -skymega->getDrillY()/2.0, 0));
    upper.addLink( RefSys( -skymega->getDrillX()/2.0, -skymega->getDrillY()/2.0, 0));

    return upper;
}

Component REPY_module::make_ear(double base, double height, double thickness, double shift, double radius)
{
    //-- Make shift:
    if (shift == 0) shift = 0.001;
    Component square = Cube( base, shift, thickness).translate( 0, shift/2.0, 0);
    Component circle = Cylinder( radius, thickness).translate(0, height, 0);

    return square & circle;
}
