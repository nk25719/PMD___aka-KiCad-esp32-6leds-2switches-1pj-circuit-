#include <HTTPClient.h>
#include <SoftwareSerial.h>
#include <DFRobotDFPlayerMini.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

unsigned long previousMillisZero = 0;
const long intervalZero = 500; // Time each lamp stays off (in milliseconds)
int currentLampZero = 1;

const int MUTE_BUTTON_PIN = 36; // GPIO 36 for the mute button
const int ON_OFF_BUTTON_PIN = 39; // GPIO 39 for the ON/OFF button

#define LED_PIN0 23// mute buttom  // D9 on PCB
#define LED_PIN 2 // GPIO 2 for the blue LED // ON OFF LED // D4 on PCB
const int lamp1Pin = 15; // lamp emergency L1 // D5 on PCB
const int lamp2Pin = 4; //lamp emergency L2 // D3 on PCB
const int lamp3Pin = 5; //lamp emergency L3 // D8 on PCB
const int lamp4Pin = 18;//lamp emergency L4 // D7 on PCB
const int lamp5Pin = 19;//lamp emergency L5 // D6 on PCB


void setup() {
  // put your setup code here, to run once:
    Serial.begin(115200);
    pinMode(MUTE_BUTTON_PIN, INPUT_PULLUP); // Set mute button pin as input with pull-up
    pinMode(ON_OFF_BUTTON_PIN, INPUT_PULLUP); // Set ON/OFF button pin as input with pull-up
    pinMode(LED_PIN, OUTPUT);          // Set LED pin as output
    digitalWrite(LED_PIN, HIGH);        // Initialize LED to ON

    // Initialize lamp pins
    pinMode(lamp1Pin, OUTPUT);
    pinMode(lamp2Pin, OUTPUT);
    pinMode(lamp3Pin, OUTPUT);
    pinMode(lamp4Pin, OUTPUT);
    pinMode(lamp5Pin, OUTPUT);
    pinMode(LED_PIN0, OUTPUT);

}

void loop() {
  blinkLamp();// put your main code here, to run repeatedly:

}


void blinkLamp() {
    unsigned long currentMillisZero = millis();

    // Check if it's time to turn off the next lamp
    if (currentMillisZero - previousMillisZero >= intervalZero) {
        previousMillisZero = currentMillisZero;

        // Ensure all lamps are initially on
        digitalWrite(lamp1Pin, HIGH);
        digitalWrite(lamp2Pin, HIGH);
        digitalWrite(lamp3Pin, HIGH);
        digitalWrite(lamp4Pin, HIGH);
        digitalWrite(lamp5Pin, HIGH);
        digitalWrite(LED_PIN0, HIGH);
        
        // Turn off the current lamp
        switch (currentLampZero) {
            case 1: digitalWrite(lamp1Pin, LOW); Serial.println("Lamp 1 is Off"); break;
            case 2: digitalWrite(lamp2Pin, LOW); Serial.println("Lamp 2 is Off"); break;
            case 3: digitalWrite(lamp3Pin, LOW); Serial.println("Lamp 3 is Off"); break;
            case 4: digitalWrite(lamp4Pin, LOW); Serial.println("Lamp 4 is Off"); break;
            case 5: digitalWrite(lamp5Pin, LOW); Serial.println("Lamp 5 is Off"); break;
            case 6: digitalWrite(LED_PIN0, LOW); Serial.println("LED_PIN0 is Off"); break;
        }

        // Move to the next lamp to turn off
        currentLampZero++;
        if (currentLampZero > 6) {
            currentLampZero = 1; // Reset to the first lamp after the last one
        }
    }
}

