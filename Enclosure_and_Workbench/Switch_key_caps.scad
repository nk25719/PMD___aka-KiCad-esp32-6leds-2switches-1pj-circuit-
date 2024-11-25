//outter_cylinder_height = 15;
//outter_radius = 2.5;

inner_cylinder_height = 4.5;
inner_radius = 1.75;

//outter_z = outter_cylinder_height/2;
//top_z = outter_cylinder_height;

difference(){
    
//OUTTER BODY
translate([0,0,(10.5)])
    rotate([0,0,0])
cube([8.7,6.7,21], center=true);

//INNER BODY
    translate([0,0,2])
cylinder (inner_cylinder_height,inner_radius,inner_radius,center=true);
}

//TOP 
//%translate([0,0,(top_z)])
//cylinder (1.5, 1.5,1.5);
$fn=100;


