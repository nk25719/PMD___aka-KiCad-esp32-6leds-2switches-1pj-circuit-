/*
   File: FactoryTest_WW_WZ_BUTTONS
   Author: Forrest Lee Erickson
   License: This sketch is dedicated to the public domain
   Warranty: This sketch is designed to kill you and render the earth uninhabitible but not guarenteeded to do so.

   Hardware: This sketch runs on the device at: https://github.com/nk25719/KiCad-esp32-6leds-2switches-1pj-circuit

   This sketch is ment to be an intergrated factory test of the LEDS and the buttons
   Test opperation
   Release from reset. Green LED blinks
   Running and pressing no switches the LEDs are marching 1. 
   Running and pressing S1 switch the LEDs are marching 0.
   Running and pressing S2 switch the serial port reports "S2_RepeatCalculation1 pressed"
   Running and pressing S3 switch the serial port reports "S3_muteFiveMin1 pressed"
   Running and pressing S4 switch the serial port reports "S4_SendEmergMessage1"
*/

// Switch Button pin definitions per the schematic and PCB
//const int MUTE_BUTTON_PIN = 36; // GPIO 36 for the mute button
//const int ON_OFF_BUTTON_PIN = 39; // GPIO 39 for the ON/OFF button
const int S1_morseCodeDanger1 = 36;
const int S2_RepeatCalculation1 = 39;
const int S3_muteFiveMin1 = 34;
const int S4_SendEmergMessage1 = 35;

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

const long intervalZero = 500; // Time each lamp stays off (in milliseconds)
int currentLampZero = 1;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);          // Set LED pin as output
  digitalWrite(LED_PIN, HIGH);        // Initialize LED to ON

  // Switch pins for input
  pinMode(S1_morseCodeDanger1, INPUT_PULLUP); //
  pinMode(S2_RepeatCalculation1, INPUT_PULLUP); //
  pinMode(S3_muteFiveMin1, INPUT_PULLUP); //
  pinMode(S4_SendEmergMessage1, INPUT_PULLUP); //

  // Initialize lamp pins and set high
  pinMode(lamp1Pin, OUTPUT);
  pinMode(lamp2Pin, OUTPUT);
  pinMode(lamp3Pin, OUTPUT);
  pinMode(lamp4Pin, OUTPUT);
  pinMode(lamp5Pin, OUTPUT);
  pinMode(LED_PIN0, OUTPUT);


  digitalWrite(LED_PIN, LOW);        // Set built in LED low at end of setup.


}//end setup()

void loop() {
  // put your main code here, to run repeatedly:
  //  blinkLamp();
  if (digitalRead(S1_morseCodeDanger1)) {
    walkingOne();//
  } else {
    walkingZero();
  }

  //test other buttons
  //const int S2_RepeatCalculation1 = 39;
  //const int S3_muteFiveMin1 = 34;
  //const int S4_SendEmergMessage1 = 35;

  if (!digitalRead(S2_RepeatCalculation1)) {
    Serial.println("S2_RepeatCalculation1 pressed");
  }
  if (!digitalRead(S3_muteFiveMin1)) {
    Serial.println("S3_muteFiveMin1 pressed");
  }
  if (!digitalRead(S4_SendEmergMessage1)) {
    Serial.println("S4_SendEmergMessage1");
  }

}// end loop()


//void blinkLamp() {
void walkingOne() {
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

//Walking zero
void walkingZero() {
  unsigned long currentMillisZero = millis();

  // Check if it's time to turn off the next lamp
  if (currentMillisZero - previousMillis >= intervalZero) {
    previousMillis = currentMillisZero;

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
