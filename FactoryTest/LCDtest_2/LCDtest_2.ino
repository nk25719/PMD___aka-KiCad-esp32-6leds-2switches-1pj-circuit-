#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Set the LCD address to 0x3F for a 16x2 display (try 0x27 if this doesn't work)
LiquidCrystal_I2C lcd(0x27, 16, 2); // 16 columns and 2 rows

void setup() {
  // Initialize I2C communication on GPIO 21 (SCL) and GPIO 22 (SDA)
  Wire.begin(21, 22);

  // Initialize the LCD
  lcd.init();
  lcd.backlight(); // Turn on the backlight

  // Print messages to the LCD
  lcd.setCursor(0, 0);  // First row, first column
  lcd.print("LCD Test Code");

  lcd.setCursor(0, 1);  // Second row, first column
  lcd.print("Hello, Rein");
  Serial.print("Hello, Rein");
}

void loop() {
  // You can add any dynamic content to display in the loop, for now, it's static
   // Print messages to the LCD
  lcd.setCursor(0, 0);  // First row, first column
  lcd.print("LCD Test Code");

  lcd.setCursor(0, 1);  // Second row, first column
  lcd.print("Hello, Rein");
  Serial.print("Hello, Rein ....");
}
