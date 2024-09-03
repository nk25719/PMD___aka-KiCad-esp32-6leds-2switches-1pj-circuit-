#include <HTTPClient.h>
#include <SoftwareSerial.h>
#include <DFRobotDFPlayerMini.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>



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
    const int delayTime = 500; // Time each lamp stays off (in milliseconds)

    // Turn all lamps on
    digitalWrite(lamp1Pin, HIGH);
    digitalWrite(lamp2Pin, HIGH);
    digitalWrite(lamp3Pin, HIGH);
    digitalWrite(lamp4Pin, HIGH);
    digitalWrite(lamp5Pin, HIGH);
    digitalWrite(LED_PIN0, HIGH);
    Serial.println("All lamps are On");
    delay(1000); // Wait for a second before starting the marching zero effect

    // Turn off each lamp one by one
    digitalWrite(lamp1Pin, LOW);
    Serial.println("Lamp 1 is Off");
    delay(delayTime);

    digitalWrite(lamp2Pin, LOW);
    Serial.println("Lamp 2 is Off");
    delay(delayTime);

    digitalWrite(lamp3Pin, LOW);
    Serial.println("Lamp 3 is Off");
    delay(delayTime);

    digitalWrite(lamp4Pin, LOW);
    Serial.println("Lamp 4 is Off");
    delay(delayTime);

    digitalWrite(lamp5Pin, LOW);
    Serial.println("Lamp 5 is Off");
    delay(delayTime);

    digitalWrite(LED_PIN0, LOW);
    Serial.println("LED_PIN0 is Off");

    delay(500); // Wait for a while before starting the next cycle
}

