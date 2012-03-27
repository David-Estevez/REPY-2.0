//-------------------------------------------------------------------------
//-- REPY-2.0_lower.scad
//-------------------------------------------------------------------------
//--This file has been generated automatically according to your data.
//--For more info, visit: http://iearobotics.com/oomlwiki/
//--------------------------------------------------------------------------

difference() {
  union() {
    difference() {
      cube(size=[52.000, 52.000, 4.000], center=true);
      translate(v=[15.000, 15.000, 0.000]) {
        cylinder(h=4.100, r1=1.500, r2=1.500, $fn=20, center=true);
      } // End translate
      translate(v=[15.000, -15.000, 0.000]) {
        cylinder(h=4.100, r1=1.500, r2=1.500, $fn=20, center=true);
      } // End translate
      translate(v=[-15.000, 15.000, 0.000]) {
        cylinder(h=4.100, r1=1.500, r2=1.500, $fn=20, center=true);
      } // End translate
      translate(v=[-15.000, -15.000, 0.000]) {
        cylinder(h=4.100, r1=1.500, r2=1.500, $fn=20, center=true);
      } // End translate
    } // End difference
    translate(v=[0.000, -22.000, 2.000]) {
      rotate(a=[0.000, 0.000, 180.000]) {
        rotate(a=[90.000, 0.000, 0.000]) {
          difference() {
            union() {
              linear_extrude(height=4.000, twist=0, $fn=100, convexity=10, center=false) {
                translate(v=[0.000, 36.500, 0.000]) {
                  circle(r=19.000, $fn=100);
                } // End translate
              } // End linear_extrude
              polyhedron(points=[[0.000, 0.000, 0.000], [0.000, 0.000, 4.000], [26.000, 0.000, 0.000], [26.000, 0.000, 4.000], [26.000, 12.000, 0.000], [26.000, 12.000, 4.000], [18.389, 41.280, 0.000], [18.389, 41.280, 4.000], [-18.389, 41.280, 0.000], [-18.389, 41.280, 4.000], [-26.000, 12.000, 0.000], [-26.000, 12.000, 4.000], [-26.000, 0.000, 0.000], [-26.000, 0.000, 4.000]], triangles=[[1, 3, 5], [12, 10, 0], [1, 5, 7], [10, 8, 0], [1, 7, 9], [8, 6, 0], [1, 9, 11], [6, 4, 0], [1, 11, 13], [4, 2, 0], [0, 3, 1], [0, 2, 3], [2, 5, 3], [2, 4, 5], [4, 7, 5], [4, 6, 7], [6, 9, 7], [6, 8, 9], [8, 11, 9], [8, 10, 11], [10, 13, 11], [10, 12, 13], [12, 1, 13], [12, 0, 1]]);
            } // End union
            color([0.500, 0.200, 1.000, 1.000]) {
              translate(v=[0.000, 36.500, 0.000]) {
                union() {
                  translate(v=[0.000, 0.000, 2.000]) {
                    cylinder(h=2.100, r1=1.100, r2=2.350, $fn=100, center=false);
                  } // End translate
                  translate(v=[0.000, 0.000, -0.100]) {
                    cylinder(h=2.100, r1=1.100, r2=1.100, $fn=100, center=false);
                  } // End translate
                } // End union
              } // End translate
            } // End color
          } // End difference
        } // End rotate
      } // End rotate
    } // End translate
    translate(v=[0.000, 11.000, 2.000]) {
      rotate(a=[90.000, 0.000, 0.000]) {
        union() {
          linear_extrude(height=4.000, twist=0, $fn=100, convexity=10, center=false) {
            translate(v=[0.000, 36.500, 0.000]) {
              circle(r=19.000, $fn=100);
            } // End translate
          } // End linear_extrude
          polyhedron(points=[[0.000, 0.000, 0.000], [0.000, 0.000, 4.000], [26.000, 0.000, 0.000], [26.000, 0.000, 4.000], [26.000, 12.000, 0.000], [26.000, 12.000, 4.000], [18.389, 41.280, 0.000], [18.389, 41.280, 4.000], [-18.389, 41.280, 0.000], [-18.389, 41.280, 4.000], [-26.000, 12.000, 0.000], [-26.000, 12.000, 4.000], [-26.000, 0.000, 0.000], [-26.000, 0.000, 4.000]], triangles=[[1, 3, 5], [12, 10, 0], [1, 5, 7], [10, 8, 0], [1, 7, 9], [8, 6, 0], [1, 9, 11], [6, 4, 0], [1, 11, 13], [4, 2, 0], [0, 3, 1], [0, 2, 3], [2, 5, 3], [2, 4, 5], [4, 7, 5], [4, 6, 7], [6, 9, 7], [6, 8, 9], [8, 11, 9], [8, 10, 11], [10, 13, 11], [10, 12, 13], [12, 1, 13], [12, 0, 1]]);
        } // End union
      } // End rotate
    } // End translate
  } // End union
  translate(v=[0.000, -18.000, 8.500]) {
    rotate(a=[90.000, 0.000, 180.000]) {
      color([0.250, 0.250, 0.250, 1.000]) {
        union() {
          translate(v=[-10.000, 0.000, 0.000]) {
            cube(size=[20.000, 41.000, 38.000], center=false);
          } // End translate
          translate(v=[0.000, 30.000, 41.000]) {
            cylinder(h=6.000, r1=3.000, r2=3.000, $fn=20, center=true);
          } // End translate
          translate(v=[-10.000, 41.000, 29.000]) {
            cube(size=[20.000, 6.500, 4.000], center=false);
          } // End translate
          translate(v=[-10.000, -6.500, 29.000]) {
            cube(size=[20.000, 6.500, 4.000], center=false);
          } // End translate
          translate(v=[5.000, 45.000, 31.000]) {
            cylinder(h=12.100, r1=2.000, r2=2.000, $fn=20, center=true);
          } // End translate
          translate(v=[5.000, -4.000, 31.000]) {
            cylinder(h=12.100, r1=2.000, r2=2.000, $fn=20, center=true);
          } // End translate
          translate(v=[-5.000, -4.000, 31.000]) {
            cylinder(h=12.100, r1=2.000, r2=2.000, $fn=20, center=true);
          } // End translate
          translate(v=[-5.000, 45.000, 31.000]) {
            cylinder(h=12.100, r1=2.000, r2=2.000, $fn=20, center=true);
          } // End translate
        } // End union
      } // End color
    } // End rotate
  } // End translate
} // End difference
