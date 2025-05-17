

module oled()  {
    // OLED PCB dimensions (you can adjust as needed)
    oled_width = 28;
    oled_height = 28.5;
    oled_thickness = 4.2; // PCB thickness
    
    // Design parameters
    wall = 1;             // Side and bottom wall thickness
    back_thickness = 1; // Back cover thickness
    clearance = 0.5;      // Fit tolerance
    pin_diameter = 1.8;
    pin_height = 5.2;
    hole_offset_x = 1.9;
    hole_offset_y = 2.19;
    
    // Cutout parameters
    cutout_width = 12;
    cutout_height = 5;
    back_cutout_sizeX=16.5;
    back_cutout_sizeY = 27;
    // Main enclosure body with cutouts
    difference() {
        // Solid block
        cube([
            oled_width + 2 * wall,
            oled_height + wall,
            oled_thickness + back_thickness
        ]);

        // Slot for OLED body
        translate([wall, wall, back_thickness])
            cube([
                oled_width,
                oled_height,
                oled_thickness + 0.2
            ]);

        // Side cutout for header pins (bottom edge center)
        translate([
            (oled_width + 2 * wall - cutout_width) / 2,
            0,
            back_thickness
        ])
            cube([cutout_width, wall + 0.1, cutout_height]);

        // Back square hole (centered on the back face)
        translate([
            (oled_width + 2 * wall - back_cutout_sizeY) / 2,
            (oled_height+ (-1) + wall - back_cutout_sizeX) / 2,
            0
        ])
            cube([back_cutout_sizeY, back_cutout_sizeX, back_thickness + 0.1]);
    }

    // Alignment pins (4 total)
    for (x = [hole_offset_x, oled_width - hole_offset_x])
    for (y = [hole_offset_y, oled_height - hole_offset_y])
        translate([x + wall, y + wall, back_thickness])
            cylinder(d = pin_diameter, h = pin_height, $fn = 24);
}
