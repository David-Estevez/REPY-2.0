//-------------------------------------------------------------------------
//-- TEST01.scad
//-------------------------------------------------------------------------
//--This file has been generated automatically according to your data.
//--For more info, visit: http://iearobotics.com/oomlwiki/
//--------------------------------------------------------------------------

union() {
  translate(v=[10.000, 10.000, 10.000]) {
    difference() {
      cube(size=[52.000, 52.000, 4.000], center=true);
      union() {
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
      } // End union
      cube(size=[20.000, 40.000, 4.100], center=true);
      cube(size=[40.000, 20.000, 4.100], center=true);
    } // End difference
  } // End translate
  linear_extrude(height=4.000, twist=0, $fn=100, convexity=10, center=false) {
    translate(v=[0.000, 50.000, 0.000]) {
      circle(r=12.000, $fn=100);
    } // End translate
  } // End linear_extrude
  difference() {
    polyhedron(points=[[0.000, 0.000, 0.000], [0.000, 0.000, 4.000], [25.000, 0.000, 0.000], [25.000, 0.000, 4.000], [25.000, 10.000, 0.000], [25.000, 10.000, 4.000], [11.459, 53.562, 0.000], [11.459, 53.562, 4.000], [-11.459, 53.562, 0.000], [-11.459, 53.562, 4.000], [-25.000, 10.000, 0.000], [-25.000, 10.000, 4.000], [-25.000, 0.000, 0.000], [-25.000, 0.000, 4.000]], triangles=[[1, 3, 5], [12, 10, 0], [1, 5, 7], [10, 8, 0], [1, 7, 9], [8, 6, 0], [1, 9, 11], [6, 4, 0], [1, 11, 13], [4, 2, 0], [0, 3, 1], [0, 2, 3], [2, 5, 3], [2, 4, 5], [4, 7, 5], [4, 6, 7], [6, 9, 7], [6, 8, 9], [8, 11, 9], [8, 10, 11], [10, 13, 11], [10, 12, 13], [12, 1, 13], [12, 0, 1]]);
    translate(v=[0.000, 50.000, 2.000]) {
      cylinder(h=4.100, r1=1.000, r2=1.000, $fn=100, center=true);
    } // End translate
  } // End difference
} // End union
