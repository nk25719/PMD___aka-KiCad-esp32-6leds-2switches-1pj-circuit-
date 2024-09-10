//How to Use the I2C Scanner:
//Upload the I2C scanner code to your ESP32.
//Open the Serial Monitor (set baud rate to 115200).
//The Serial Monitor will display the detected I2C address of the connected devices.
//Use this address in your LCD test code instead of 0x3F.
//Once you find the correct address, update the LCD test code with that address, and it should work as expected.





#include <Wire.h>

void setup() {
  Wire.begin(21, 22); // Initialize I2C communication on GPIO 21 (SCL) and GPIO 22 (SDA)
  Serial.begin(115200);
  Serial.println("\nI2C Scanner");
}

void loop() {
  byte error, address;
  int nDevices = 0;

  Serial.println("Scanning...");

  for (address = 1; address < 127; address++) {
    Wire.beginTransmission(address);
    error = Wire.endTransmission();

    if (error == 0) {
      Serial.print("I2C device found at address 0x");
      if (address < 16)
        Serial.print("0");
      Serial.print(address, HEX);
      Serial.println(" !");
      nDevices++;
    } else if (error == 4) {
      Serial.print("Unknown error at address 0x");
      if (address < 16)
        Serial.print("0");
      Serial.println(address, HEX);
    }
  }
  if (nDevices == 0)
    Serial.println("No I2C devices found\n");
  else
    Serial.println("done\n");

  delay(5000); // Wait 5 seconds for next scan
}
