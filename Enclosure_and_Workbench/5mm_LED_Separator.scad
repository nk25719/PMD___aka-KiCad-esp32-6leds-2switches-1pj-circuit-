
difference(){
//Big Cylinder
translate([0,0,0])
cylinder(9,2.5,2.5);

//Small cylinder 1
translate ([1.5,0,12])
cylinder(26,1.1,1.1,center=true);
//Small Cube 1
translate ([2,0,0])
cube([1,0.6,49],center=true);
    
//Big cylinder 2
translate ([-1.5,0,12])
cylinder(26,1.1,1.1,center=true);

//Small Cube 2

translate ([-2,0,0])
cube([1,0.6,49],center=true);
}
$fn=100;