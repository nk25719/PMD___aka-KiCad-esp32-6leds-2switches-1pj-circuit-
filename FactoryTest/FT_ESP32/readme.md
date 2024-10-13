This code controls various components, including an LCD screen, emergency lamps, a mute button, an ON/OFF button, and a DFPlayer for audio playback, all using an ESP32 microcontroller. Here's a breakdown of what it's doing:

## Libraries and Pin Definitions:

### Libraries:

HTTPClient.h: Used for HTTP requests (though not utilized in the code provided).
SoftwareSerial.h: For software serial communication with the DFPlayer Mini.
DFRobotDFPlayerMini.h: Controls the DFPlayer Mini audio module.
LiquidCrystal_I2C.h & Wire.h: Control the I2C LCD screen.

## Pin Assignments:

Two buttons (MUTE_BUTTON_PIN on GPIO 36 and ON_OFF_BUTTON_PIN on GPIO 39).
Several LED pins (emergency lamps and LEDs on different GPIO pins).
The DFPlayer Mini uses software serial (RX on GPIO 16, TX on GPIO 17).
Setup (setup function):
Serial Communication: Initializes the serial monitor at a baud rate of 115200 for debugging.
Button and LED Pins:
Buttons are set as inputs with internal pull-up resistors.
LED pins are configured as outputs, and they are turned ON initially.
Initialize Peripherals:
Software serial communication for the DFPlayer Mini.
Initializes the I2C LCD and turns on its backlight, printing "Running setup...".
LED Control: After a brief delay, all LEDs are turned off.
Main Loop (loop function):
LED Blinking:
The blinkLamp() function is called, which turns all LEDs on for 1 second, then off for 200ms. This repeats continuously, and status messages are printed to the serial monitor.