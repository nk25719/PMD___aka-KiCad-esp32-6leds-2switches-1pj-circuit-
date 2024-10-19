//#include <HTTPClient.h>
//#include <SoftwareSerial.h>
//#include <DFRobotDFPlayerMini.h>
//#include <LiquidCrystal_I2C.h>
//#include <Wire.h>



const int MUTE_BUTTON_PIN = 36; // GPIO 36 for the mute button
const int ON_OFF_BUTTON_PIN = 39; // GPIO 39 for the ON/OFF button

#define LED_PIN0 23// mute buttom  // D9 on PCB
#define LED_PIN 2 // GPIO 2 for the blue LED // ON OFF LED // D4 on PCB
const int lamp1Pin = 15; // lamp emergency L1 // D5 on PCB
const int lamp2Pin = 4; //lamp emergency L2 // D3 on PCB
const int lamp3Pin = 5; //lamp emergency L3 // D8 on PCB
const int lamp4Pin = 18;//lamp emergency L4 // D7 on PCB
const int lamp5Pin = 19;//lamp emergency L5 // D6 on PCB

unsigned long previousMillis = 0;
const long interval = 500; // Time each lamp stays on (in milliseconds)
int currentLamp = 1;
bool allLampsOff = true;


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
    unsigned long currentMillis = millis();
    
    if (currentMillis - previousMillis >= interval) {
        previousMillis = currentMillis;

        // Turn off all lamps first
        digitalWrite(lamp1Pin, LOW);
        digitalWrite(lamp2Pin, LOW);
        digitalWrite(lamp3Pin, LOW);
        digitalWrite(lamp4Pin, LOW);
        digitalWrite(lamp5Pin, LOW);
        digitalWrite(LED_PIN0, LOW);
        
        // Turn on the current lamp
        switch (currentLamp) {
            case 1: digitalWrite(lamp1Pin, HIGH); Serial.println("Lamp 1 is On"); break;
            case 2: digitalWrite(lamp2Pin, HIGH); Serial.println("Lamp 2 is On"); break;
            case 3: digitalWrite(lamp3Pin, HIGH); Serial.println("Lamp 3 is On"); break;
            case 4: digitalWrite(lamp4Pin, HIGH); Serial.println("Lamp 4 is On"); break;
            case 5: digitalWrite(lamp5Pin, HIGH); Serial.println("Lamp 5 is On"); break;
            case 6: digitalWrite(LED_PIN0, HIGH); Serial.println("LED_PIN0 is On"); break;
        }

        // Move to the next lamp
        currentLamp++;
        if (currentLamp > 6) {
            currentLamp = 1; // Reset to the first lamp after the last one
        }
    }
}
