
x=60.88;//x +5PCB Width
y=30.685;//y +4PCB Height
z=0;//z
x1= 63.88;
y1= 33.685;
height_top = 3;
corner_radius=5;
wall_thick =5;
hole_diameter = 3.5; // for screws
post_diameter = 10;
LED_diameter = 6.6; // for LED
lid_thickness = 2;
lid_lip = 2;
lid_tolerance =0.5;

extend = 3; //Show inside Enclosure [20 is closing enclosure number.]

power_surge_diameter =5.85;
power_surge_location =extend+5;

heightPCB = 113.0620;
widthPCB = 53.370;

heightPCBHole = 103.163;
widthPCBHole = 43.4340;

halfheightPCBHole = heightPCBHole/2;
halfwidthPCBHole = widthPCBHole/2;



//THE TOP 
difference(){
    color("Khaki")
 hull(){
    translate ([x,y,z]){
    cylinder (r=corner_radius, h=height_top);
}
    translate ([-x,y,z]){
    cylinder (r=corner_radius, h=height_top);
}
    translate ([-x,-y,z]){
    cylinder (r=corner_radius, h=height_top);
}
    translate ([x,-y,z]){
    cylinder (r=corner_radius, h=height_top);
}
}
// NOTE THERE ARE ERRORS WITH THE HOLE 1-4 MEASUREMENTS THEY OUGHT TO BE SMALLER.

//Top LED 1
translate([36.83,26.685,0])
cylinder(h=15,d1=LED_diameter,d2 = LED_diameter, center=true);
//Top LED 2
translate([36.83,19.3352,0])
cylinder(h=15,d1=LED_diameter,d2 = LED_diameter, center=true);
//Top LED 3
translate([36.83,11.9854,0])
cylinder(h=15,d1=LED_diameter,d2 = LED_diameter, center=true);
//Top LED 4
translate([36.83,4.6356,0])
cylinder(h=15,d1=LED_diameter,d2 = LED_diameter, center=true);
//Top LED 5
translate([36.83,-2.7142,0])
cylinder(h=15,d1=LED_diameter,d2 = LED_diameter, center=true);
//Top LED 6
translate([-26.6618,25.0228,0])
cylinder(h=15,d1=LED_diameter,d2 = LED_diameter, center=true);
//Top LED 7
translate([-26.6618,17.6568,0])
cylinder(h=15,d1=LED_diameter,d2 = LED_diameter, center=true);
//Top LED 8
translate([-54.0263,8.0028,0])
cylinder(h=15,d1=LED_diameter,d2 = LED_diameter, center=true);

//PUSH_BUTN 1
translate([-9.0333,26.685,0])
cube([9.1967,7.20,15], center=true);
//PUSH_BUTN 2
translate([-9.0333,18.435,0])
cube([9.1967,7.20,15], center=true);
//PUSH_BUTN 3
translate([-9.0333,10.185,0])
cube([9.1967,7.20,15], center=true);
//PUSH_BUTN 4
translate([-9.0333,1.935,0])
cube([9.1967,7.20,15],center=true);
//TRANSISTOR HOLE
translate([-10.76,-13.41,00])
cube([10.5,4.641,15],center=true);
}
// THE HOLLOW SHAPE

difference(){
    color("Khaki")
hull(){
    translate ([x1,y1,extend]){
    cylinder (r=corner_radius, h=22);
}
    translate ([-x1,y1,extend]){
    cylinder (r=corner_radius, h=22);
}
    translate ([-x1,-y1,extend]){
    cylinder (r=corner_radius, h=22);
}
    translate ([x1,-y1,extend]){
    cylinder (r=corner_radius, h=22);
}
}
//INSIDE HOLLOW
hull(){
translate ([55.88,25.658,(extend+6.5)]){
    cylinder (r=corner_radius, h=20.5, center=true);
}
    translate ([-55.88,25.658,(extend+6.5)]){
    cylinder (r=corner_radius, h=20.5, center=true);
}
    translate ([-55.88,-25.658,(extend+6.5)]){
    cylinder (r=corner_radius, h=20.5, center=true);
}
    translate ([55.88,-25.658,(extend+6.5)]){
    cylinder (r=corner_radius, h=20.5, center=true);
    }
}
//Small Hole for Enclosure
translate([-halfheightPCBHole,halfwidthPCBHole,60])
cylinder(h=102,d1=hole_diameter,d2 = hole_diameter, center=true);  

//Small Hole 2 for Enclosure
translate([halfheightPCBHole,halfwidthPCBHole,60])
cylinder(h=102,d1=hole_diameter,d2 = hole_diameter, center=true);

//Small Hole 3 for Enclosure
translate([halfheightPCBHole,-halfwidthPCBHole,60])
cylinder(h=102,d1=hole_diameter,d2 = hole_diameter, center=true);
//Hole 4 for Enclosure
translate([-halfheightPCBHole,-halfwidthPCBHole,60])
cylinder(h=102,d1=hole_diameter,d2 = hole_diameter, center=true);

//POWER SURGE
translate([-x1,-6.049,(extend+5)])
rotate([0,90,0])
cylinder (h=12,d1=power_surge_diameter,d2=power_surge_diameter, center=true);
}

$fn=50;

//THE 4 CYCLINDERS 
difference(){
//Screw Cylinder 1
    color("Khaki")
translate([-halfheightPCBHole,halfwidthPCBHole,13])
cylinder(h=19.5,d1=13,d2 =13, center=true);
 //Small Hole 1
translate([-halfheightPCBHole,halfwidthPCBHole,12])
cylinder(h=20,d1=hole_diameter,d2 = hole_diameter, center=true);   
}   
difference (){    
//Screw Cylinder 2
    color("Khaki")
translate([halfheightPCBHole,halfwidthPCBHole,13])
cylinder(h=19.5,d1=13,d2 =13,center=true);
//Small Hole 2
translate([halfheightPCBHole,halfwidthPCBHole,12])
cylinder(h=20,d1=hole_diameter,d2 = hole_diameter, center=true);
}
difference(){
//Screw Cylinder 3
    color("Khaki")
translate([halfheightPCBHole,-halfwidthPCBHole,13])
cylinder(h=19.5,d1=13,d2 =13, center=true);
    //Small Hole 3
translate([halfheightPCBHole,-halfwidthPCBHole,12])
cylinder(h=20,d1=hole_diameter,d2 = hole_diameter, center=true);
}
 difference(){   
//Screw Cylinder 4
     color("Khaki")
translate([-halfheightPCBHole,-halfwidthPCBHole,13])
cylinder(h=19.5,d1=13,d2 =13,center=true);
//Hole 4
translate([-halfheightPCBHole,-halfwidthPCBHole,12])
cylinder(h=20,d1=hole_diameter,d2 = hole_diameter, center=true);
 }


 
  