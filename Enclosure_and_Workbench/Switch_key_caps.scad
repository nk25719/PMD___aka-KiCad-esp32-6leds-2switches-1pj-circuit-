

inner_cylinder_height = 4.5;
inner_radius = 1.7;
cube_z =13 ;
outerbody_z = (cube_z/2);

color ("Salmon")
////Keycap Stem
translate ([-2,-3,cube_z])
cube([5.42,7.25,3.24 ]); 

 
difference(){
//OUTTER BODY  
translate([ 0.7,0.55,(outerbody_z)])
color ("Red")
cube([6.3,8.2,cube_z], center=true);

//INNER BODY
    translate([0.5,0.5,2])
cylinder (inner_cylinder_height,inner_radius,inner_radius,center=true);
}

$fn=100;


