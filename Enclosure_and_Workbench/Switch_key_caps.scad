

inner_cylinder_height = 4.5;
inner_radius = 1.895;
cube_z =6 ;
outerbody_z = (cube_z/2);

color ("Salmon")
////Keycap Stem
translate ([-2,-3,cube_z])
cube([5,7,10.25 ]); 

 
difference(){
//OUTTER BODY  
translate([ 0.5,0.5,(outerbody_z)])
color ("Red")
cube([6,8,cube_z], center=true);

//INNER BODY
    translate([0.5,0.5,2])
cylinder (inner_cylinder_height,inner_radius,inner_radius,center=true);
}

$fn=100;


