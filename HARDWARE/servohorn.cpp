#include "servohorn.h"

//-- Constructor:
//-----------------------------------------
ServoHorn::ServoHorn( int num_arms)
{
    this->num_arms = num_arms;
    tol = 0;
    cut = 0;

    //-- Set parameters depending on the number of arms of the servo horn.
    //-- For fake futaba:
    switch( num_arms )
    {
    case 0: default:
	//-- Rounded horn:
	h_top = 3;
	r_top = 20.5 / 2.0;
	h_axis = 3.5;
	r_axis = 9 / 2.0;
	//-- Not needed for rounded horn:
	arm_r = 0;
	arm_shift = 0;
	arm_dist = 0;
	break;

    case 2:
	//-- 2-arms horn:
	h_top = 3;
	r_top = 12.5 / 2.0;
	h_axis = 3;
	r_axis = 9 / 2.0;
	arm_r = 5 / 2.0;
	arm_shift = 0;
	arm_dist = 19 - 5 / 2.0;
	break;

    case 4:
	//-- 4-arms horn:
	h_top = 3;
	r_top = 13.5 / 2.0;
	h_axis = 3;
	r_axis = 9 / 2.0;
	arm_r = 4.5 / 2.0;
	arm_shift = 7;
	arm_dist = 18 - 4.5 / 2.0;
	break;

    case 6:
	//-- 6-arms horn:
	h_top = 3;
	r_top = 15 / 2.0;
	h_axis = 3;
	r_axis = 9 / 2.0;
	arm_r = 5 / 2.0;
	arm_shift = 0;
	arm_dist = (31.5 - 5) / 2.0;
	break;
    }
    rebuild();
}

void ServoHorn::set_tolerance(double tol)
{
    this->tol = tol;
    rebuild();
}

void ServoHorn::cut_horn(double cut)
{
    this->cut = cut;
    rebuild();
}

Component ServoHorn::build()
{
    //-- Create axis cylinder
    Component horn = Cylinder::create(r_axis+tol, h_axis +0.1, 100, false);

    if (num_arms == 0) //-- Rounded horn
    {
	Component top = Cylinder::create( r_top+tol, h_top, 100, false);
	top.translate(0, 0, h_axis);
	horn = horn + top;

	if ( cut < r_top )
	{
	    //-- Create a cube with the dimensions of the cut
	    Component to_be_substracted = Cube::create( (r_top+tol)- cut + 0.1, 2*(r_top+tol)+0.2, h_top+0.2, false);

	    //-- Center it on Y:
	    to_be_substracted.translate(0, -(r_top+tol)+0.1, 0);

	    //-- Place it on its place (LOL) and substract it:
	    horn = horn - to_be_substracted.translate( cut + 0.1 ,0, h_axis-0.1);
	 }
    }
    else //-- Horn with arms:
    {
	//-- Create a single arm:
	Component base = Cube::create( 2*r_axis, 0.001, h_top+0.1);
	Component upper_cyl = Cylinder::create( arm_r, h_top+0.1, 100, true);
	upper_cyl = upper_cyl.translate( 0, arm_dist, 0);

	Component arm = base.color( 1, 0, 0) & upper_cyl.color(1,0,0);
	arm.translate(0, 0, (h_top+0.1) /2);

	//-- Create the orher arms by rotation:
	Component arms = arm;
	for ( int i = 1; i < num_arms; i++)
	    arms = arms + arm.rotatedCopy(0,0, 360/num_arms*i);
	arms.translate( 0, 0, h_axis);

	//-- Add the top cylinder:
	Component top_cyl = Cylinder::create( r_top, h_top + 0.1, 100, false)
			    .translate(0,0, h_axis);

	//-- Sum up all the parts:
	horn = horn + arms + top_cyl;
    }

    //-- Set link on the end of the axis cylinder, to attach to the servo:
    horn.addLink( RefSys( 0,0, h_axis));
    //! -- \todo Change this when OOML is fix:
    horn.relTranslate(0,0,-h_axis);

    return horn;
}
