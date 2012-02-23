//-------------------------------------------------------------------------
//-- base.scad
//-------------------------------------------------------------------------
//--This file has been generated automatically according to your data.
//--For more info, visit: http://iearobotics.com/oomlwiki/
//--------------------------------------------------------------------------

difference() {
  cube(size=[52.000, 52.000, 4.000], center=true);
  cube(size=[40.000, 20.000, 4.100], center=true);
  cube(size=[20.000, 40.000, 4.100], center=true);
  translate(v=[15.000, 15.000, 0.000]) {
    cylinder(h=4.100, r1=1.000, r2=1.000, $fn=20, center=true);
  } // End translate
  translate(v=[15.000, -15.000, 0.000]) {
    cylinder(h=4.100, r1=1.000, r2=1.000, $fn=20, center=true);
  } // End translate
  translate(v=[-15.000, 15.000, 0.000]) {
    cylinder(h=4.100, r1=1.000, r2=1.000, $fn=20, center=true);
  } // End translate
  translate(v=[-15.000, -15.000, 0.000]) {
    cylinder(h=4.100, r1=1.000, r2=1.000, $fn=20, center=true);
  } // End translate
} // End difference
