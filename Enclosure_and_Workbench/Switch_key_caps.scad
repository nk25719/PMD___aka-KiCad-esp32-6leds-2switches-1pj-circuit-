

inner_cylinder_height = 4.5;
inner_radius = 1.895;
cube_z =5.5;
outerbody_z = (cube_z/2);

color ("Salmon")
////Keycap Stem
translate ([-2,-3,cube_z])
cube([4,6,9.25]); 

 
difference(){
//OUTTER BODY  
translate([0,0,(outerbody_z)])
color ("Red")
cube([5,7,cube_z], center=true);

//INNER BODY
    translate([0,0,2])
cylinder (inner_cylinder_height,inner_radius,inner_radius,center=true);
}

$fn=100;


