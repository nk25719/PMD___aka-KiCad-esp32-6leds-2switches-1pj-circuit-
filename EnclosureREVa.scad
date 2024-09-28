x=60.88;//x +5PCB Width
y=30.685;//y +5PCB Height
z=0;//z
x1= 65.88;
y1= 35.685;
height_top = 3;
corner_radius=5;
wall_thick =5;
hole_diameter = 3.5; // for screws
post_diameter = 10;
LED_diameter = 6.6; // for LED
lid_thickness = 2;
lid_lip = 2;
lid_tolerance =0.5;

extend = 35; //Show inside Enclosure

heightPCB = 111.7680;
widthPCB = 53.370;

heightPCBHole = 103.163;
widthPCBHole = 43.4340;

halfheightPCBHole = heightPCBHole/2;
halfwidthPCBHole = widthPCBHole/2;


//PCB BOARD
color("Green")
difference(){
translate([55.88,-26.685,25])
rotate([0,0,90])
square ([widthPCB,heightPCB],0);
//PCB HOLE 1
translate([-halfheightPCBHole,halfwidthPCBHole,20])
cylinder(h=20,d1=3.25,d2 =3.25,center = true);
    
 //PCB HOLE 2
translate([halfheightPCBHole,halfwidthPCBHole,20])
cylinder(h=20,d1=3.25,d2 =3.25,center = true);
    
//PCB HOLE 3
translate([halfheightPCBHole,-halfwidthPCBHole,20])
cylinder(h=20,d1=3.25,d2 =3.25,center = true);
    
//PCB HOLE 4
translate([-halfheightPCBHole,-halfwidthPCBHole,20])
cylinder(h=20,d1=3.25,d2 =3.25,center = true);
}







//THE TOP 
difference(){
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
//Hole 1
translate([-55.88,26.685,0])
cylinder(h=15,d1=hole_diameter,d2 = hole_diameter, center=true);
//Hole 2
translate([55.88,26.685,0])
cylinder(h=15,d1=hole_diameter,d2 = hole_diameter, center=true);
//Hole 3
translate([55.88,-26.685,0])
cylinder(h=15,d1=hole_diameter,d2 = hole_diameter, center=true);
//Hole 4
translate([-55.88,-26.685,0])
cylinder(h=15,d1=hole_diameter,d2 = hole_diameter, center=true);

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

}
// 
difference(){
hull(){
    translate ([x1,y1,extend]){
    cylinder (r=corner_radius, h=15.3);
}
    translate ([-x1,y1,extend]){
    cylinder (r=corner_radius, h=15.3);
}
    translate ([-x1,-y1,extend]){
    cylinder (r=corner_radius, h=15.3);
}
    translate ([x1,-y1,extend]){
    cylinder (r=corner_radius, h=15.3);
}
}

hull(){
translate ([55.88,25.658,extend]){
    cylinder (r=corner_radius, h=15.3, center=true);
}
    translate ([-55.88,25.658,extend]){
    cylinder (r=corner_radius, h=15.3 , center=true);
}
    translate ([-55.88,-25.658,extend]){
    cylinder (r=corner_radius, h=15.3, center=true);
}
    translate ([55.88,-25.658,extend]){
    cylinder (r=corner_radius, h=15.3, center=true);
    }
  
 //HOLE FOR POWER Source

}
}

$fn=50;
//

//DIFFERENCE CODE NOT WORKING
difference(){
//Big Cylinder 1
translate([-58.88,25.88,5])
cylinder(h=10,d1=13,d2 =13, center=true);
 //Small Hole 1
translate([-58.88,25.88,5])
cylinder(h=12,d1=hole_diameter,d2 = hole_diameter, center=true);   
}   
difference (){    
//Screw Hole 2
translate([58.88,25.88,5])
cylinder(h=10,d1=13,d2 =13,center=true);
//Hole 2
translate([58.88,25.88,5])
cylinder(h=12,d1=hole_diameter,d2 = hole_diameter, center=true);
}
difference(){
//Screw Hole 3
translate([58.88,-25.88,5])
cylinder(h=10,d1=13,d2 =13, center=true);
    //Hole 3
translate([58.88,-25.88,5])
cylinder(h=12,d1=hole_diameter,d2 = hole_diameter, center=true);
}
 difference(){   
    
//Screw Hole 4
translate([-58.88,-25.88,10])
cylinder(h=20,d1=13,d2 =13,center=true);
//Hole 4
translate([-58.88,-25.88,10])
cylinder(h=22,d1=hole_diameter,d2 = hole_diameter, center=true);
 }


 
  