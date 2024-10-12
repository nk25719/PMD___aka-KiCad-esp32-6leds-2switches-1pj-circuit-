
x=55.88;//x 
y=53.37;//y+y
z=0;//z
height_top = 5;
corner_radius=5;
wall_thick =5;
hole_diameter = 3.5; // for screws
post_diameter = 10;
LED_diameter = 6.6; // for LED
lid_thickness = 2;
lid_lip = 2;
lid_tolerance =0.5;

heightPCB = 111.7680;
widthPCB = 53.370;

heightPCBHole = 103.163;
widthPCBHole = 43.4340;

halfheightPCBHole = heightPCBHole/2;
halfwidthPCBHole = widthPCBHole/2;


difference(){
 hull(){
    translate ([55.88,26.685,0]){
    cylinder (r=corner_radius, h=height_top);
}
///THE LOCATION OF HOLE ONE 
    translate ([-55.88,26.685,0]){
    cylinder (r=corner_radius, h=height_top);
}
    translate ([-x,-y,z]){
    cylinder (r=corner_radius, h=height_top);
}
    translate ([x,-y,z]){
    cylinder (r=corner_radius, h=height_top);
}
}
}


//Hole 1
difference(){
translate([-halfheightPCBHole,halfwidthPCBHole,20])
cylinder(h=40,d1=7.25,d2 =7.25,center = true);
    translate([-halfheightPCBHole,halfwidthPCBHole,20])
cylinder(h=45,d1=hole_diameter,d2=hole_diameter, center = true);
}
//Hole 2
difference(){
   translate([halfheightPCBHole,halfwidthPCBHole,20])
cylinder(h=40,d1=7.25,d2 =7.25,center=true);
translate([halfheightPCBHole,halfwidthPCBHole,20])
cylinder(h=45,d1=hole_diameter,d2 = hole_diameter, center=true);
}       
//Hole 3
difference(){
    translate([halfheightPCBHole,-halfwidthPCBHole,20])
cylinder(h=40,d1=7.25,d2 =7.25,center=true);
translate([halfheightPCBHole,-halfwidthPCBHole,20])
cylinder(h=45,d1=hole_diameter,d2 = hole_diameter, center=true);
}
//Hole 4
difference(){
    translate([-halfheightPCBHole,-halfwidthPCBHole,20])
cylinder(h=40,d1=7.25,d2 =7.25,center=true);
translate([-halfheightPCBHole,-halfwidthPCBHole,20])
cylinder(h=45,d1=hole_diameter,d2 = hole_diameter, center=true);
}

//Hole 5
difference(){
translate([-55.88,-y,20])
cylinder(h=40,d1=7.25,d2 =7.25,center = true);
    translate([-55.88,-y,20])
cylinder(h=45,d1=hole_diameter,d2=hole_diameter, center = true);
}    
    
//Hole 6
difference(){
translate([55.88,-y,20])
cylinder(h=40,d1=7.25,d2 =7.25,center = true);
    translate([55.88,-y,20])
cylinder(h=45,d1=hole_diameter,d2=hole_diameter, center = true);
   
}    
   ///// UPPER TABLE
 color("Khaki")
difference(){
 hull(){ 
    translate ([55.88,-26.685,20]){
    cylinder (r=corner_radius, h=height_top);
}
//LOCATION OF HOLE 4
    translate ([-55.88,-26.685,20]){
    cylinder (r=corner_radius, h=height_top);
}
//LOCATION OF HOLE 5
   translate ([-55.88,-y,20]){
    cylinder (r=corner_radius, h=height_top);
}
//LOCATION OF HOLE 6
    translate ([55.88,-y,20]){
    cylinder (r=corner_radius, h=height_top);
}
}
translate([0,-40,21])
cube([99,1.8,20], center=true);
} 
   


$fn=50;
 