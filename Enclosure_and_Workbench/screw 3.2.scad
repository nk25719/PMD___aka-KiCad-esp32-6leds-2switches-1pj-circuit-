$fn=100; // Smoothness

// Parameters
total_height = 19;
core_radius = 1.6;         // Half of 0.32 for radius
thread_radius = 0.04;       // Thread thickness
pitch = 0.3;                // Distance between each thread turn

// Screw core
cylinder(h=total_height - 0.2, r=core_radius);

// Helical thread
for (z = [0 : pitch : total_height - 0.2])
    rotate([0, 0, 360 * z / pitch])
    translate([core_radius + thread_radius, 0, z])
    cylinder(h=thread_radius, r=thread_radius);

// Cap
translate([0, 0, total_height - 0.2])
cylinder(h=0.99, r=core_radius * 3.2);
