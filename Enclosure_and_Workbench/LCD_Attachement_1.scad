x = 50;
y = 30;
z=0;
x1 = 52;
y1 = 32;
z=0;
h1 = 25;
x2 = 50;
y2 = 30;
h2 = 25;
x3 = 50;
y3 = 30;
h3 = 24;
LCD_x = 26;
LCD_y = 93; 
height_top = 3;
corner_radius = 2;
corner_radiusb = 2;
extend = 1; //Show inside Enclosure [20 is closing enclosure number.]

module top(){
difference(){
difference(){
    color("DarkGrey")
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
}

 //LCD Hole 1
 translate ([46,-15,-1.5])
 rotate ([0,0,90])
 cube([LCD_x,LCD_y,10]);
}
}


module box(){
//OUTSIDE HOLLOW
difference(){
color("DarkGrey")
hull(){
translate([x1,y1,extend]){
    cylinder (r=corner_radius, h=h1);
}
    translate ([-x1,y1,extend]){
    cylinder (r=corner_radius, h=h1);
}
    translate ([-x1,-y1,extend]){
    cylinder (r=corner_radius, h=h1);
}
    translate ([x1,-y1,extend]){
    cylinder (r=corner_radius, h=h1);
}
}
//INSIDE HOLLOW
hull(){
translate([x2,y2,(extend+11.5)]){
    cylinder (r=corner_radiusb, h=h2, center=true);
}
    translate ([-x2,y2,(extend+11.5)]){
    cylinder (r=corner_radiusb, h=h2, center=true);
}
    translate ([-x2,-y2,(extend+11.5)]){
    cylinder (r=corner_radiusb, h=h2, center=true);
}
    translate ([x2,-y2,(extend+11.5)]){
    cylinder (r=corner_radiusb, h=h2, center=true);
    }
}

//LCD Hole 2
translate ([25,-35,15.5])
rotate ([0,90,90])
cube([9,50,3]);
}
}


translate ([30,-40,7])
cube([8,8,8]);

translate ([-38,-40,7])
cube([8,8,8]);

//Trying to make a lip (Not working)
//INSIDER HOLLOW
//hull(){
//translate([x2,y2,(extend+11.5)]){
//    cylinder (r=corner_radiusb, h=h3, center=true);
//}
//    translate ([-x2,y2,(extend+11.5)]){
//    cylinder (r=corner_radiusb, h=h3, center=true);
//}
//    translate ([-x2,-y2,(extend+11.5)]){
//    cylinder (r=corner_radiusb, h=h3, center=true);
//}
//    translate ([x2,-y2,(extend+11.5)]){
//    cylinder (r=corner_radiusb, h=h3, center=true);
//    }
//}
//}
 

top();
box();





