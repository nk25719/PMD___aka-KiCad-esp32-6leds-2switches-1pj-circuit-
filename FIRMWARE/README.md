# File Summary
These files are for the iCad-esp32-6leds-2switches-1pj-circuit assembly.
https://github.com/nk25719/KiCad-esp32-6leds-2switches-1pj-circuit

They were developed during the learning of ESP32 embedded systems programing and embedded systems hardware development.

## Firmware Types by Development Tools 

### Files which compile in the Arduino IDE Rev 2:
Blink_jul16b,  Blinks a single LED using delay().  
Blink2LEDs_jul16b, Blinks two LEDs using delay().  
Blink6independentRate_jul27b, Blinks all LEDs EXCEPT D9.  Uses "clock watching" for multi tasking.  
Blink6inSequence_jul20a, Blinks but using delay(). The LED D9 does not blink. The LEDs do not blink in the sequence of the PCB.  
BlinkWOdelay_jul16c,  created 2005 by David A. Mellis modified 8 Feb 2010 by Paul Stoffregen. This code likly malfunctions when the mills() function rolls over.  
ClassySolution_jul20b, From the https://learn.adafruit.com/multi-tasking-the-arduino-part-1 article. Uses no delay().  
FactoryTest_BRD1, Uses the SoftwareSerial library to communicate with the DF player. Uses delay().  
FactoryTest_WW_WZ_BUTTONS, This firmware tests LEDs with walking one, Walking Zero and the four input buttons. Was used for test of assemblies build by JLCPCB July 2024.  
FlashWOdelay_jul16d, Flashes two LEDs with out using delay but does not use the Class solution.  
HOLDDownS1toBlinkLEDpin2Faster_jul27a, Presseing S1 causes the LED to change blink period.  
implementingMillis_jul27a, Has WiFi Manager, Uses SoftwareSerial for DF player. Uses delay() in function handlePinData().  
marchingOneTest, Test for shorts and opens on LED pins.  
marchingZeroTest, Test for shorts and opens on LED pins.  
mockingKrake, Firmware for the Krake mockup. Has WiFi Manager, Uses SoftwareSerial for DF player. Uses delay() in several functions.  
testSwitches, Test for switch press and held and reports our serial port.  
twoAtonce_jul16a, Flashes two LEDs with out using delay but does not use the Class solution.  

### Files which compile in MS Visual Studio:
PMDtoKRake_KrakeV2. Although this compiles in the Aaruino IDE it has a template subfolder with HTML and PY code and so looks to stem from a MS Visual Studio template.
