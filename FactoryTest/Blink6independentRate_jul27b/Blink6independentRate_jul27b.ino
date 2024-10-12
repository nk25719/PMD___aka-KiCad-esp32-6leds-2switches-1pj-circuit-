// Make all LEDs blink at independent rates and duty cycles
// issue #31:  https://github.com/nk25719/KiCad-esp32-6leds-2switches-1pj-circuit/issues/31
// Beirut, Lebanon - Current Time 9:55 PM EEST on Saturday, July 27, 2024 
// Nagham Kheir


const int led1Pin = 2;
const int led2Pin = 4;
const int led3Pin = 5;
const int led4Pin = 18;
const int led5Pin = 19;
const int led6Pin = 15;

unsigned long previousMillis1 = 0;
unsigned long previousMillis2 = 0;
unsigned long previousMillis3 = 0;
unsigned long previousMillis4 = 0;
unsigned long previousMillis5 = 0;
unsigned long previousMillis6 = 0;

unsigned long onTime1 = 500;  // LED1 on duration in milliseconds
unsigned long offTime1 = 1000; // LED1 off duration in milliseconds

unsigned long onTime2 = 300;  // LED2 on duration in milliseconds
unsigned long offTime2 = 700; // LED2 off duration in milliseconds

unsigned long onTime3 = 400;  // LED3 on duration in milliseconds
unsigned long offTime3 = 800; // LED3 off duration in milliseconds

unsigned long onTime4 = 600;  // LED4 on duration in milliseconds
unsigned long offTime4 = 1200; // LED4 off duration in milliseconds

unsigned long onTime5 = 200;  // LED5 on duration in milliseconds
unsigned long offTime5 = 500; // LED5 off duration in milliseconds

unsigned long onTime6 = 200;  // LED5 on duration in milliseconds
unsigned long offTime6 = 500; // LED5 off duration in milliseconds

bool led1State = LOW;
bool led2State = LOW;
bool led3State = LOW;
bool led4State = LOW;
bool led5State = LOW;
bool led6State = LOW;

void setup() {
  pinMode(led1Pin, OUTPUT);
  pinMode(led2Pin, OUTPUT);
  pinMode(led3Pin, OUTPUT);
  pinMode(led4Pin, OUTPUT);
  pinMode(led5Pin, OUTPUT);
  pinMode(led6Pin, OUTPUT);

}

void loop() {
  unsigned long currentMillis = millis();

  updateLEDState(currentMillis, led1Pin, led1State, previousMillis1, onTime1, offTime1);
  updateLEDState(currentMillis, led2Pin, led2State, previousMillis2, onTime2, offTime2);
  updateLEDState(currentMillis, led3Pin, led3State, previousMillis3, onTime3, offTime3);
  updateLEDState(currentMillis, led4Pin, led4State, previousMillis4, onTime4, offTime4);
  updateLEDState(currentMillis, led5Pin, led5State, previousMillis5, onTime5, offTime5);
  updateLEDState(currentMillis, led6Pin, led6State, previousMillis6, onTime6, offTime6);
}

void updateLEDState(unsigned long currentMillis, int ledPin, bool &ledState, unsigned long &previousMillis, unsigned long onTime, unsigned long offTime) {
  if (ledState == HIGH && (currentMillis - previousMillis >= onTime)) {
    ledState = LOW;  // Turn it off
    previousMillis = currentMillis;  // Remember the time
    digitalWrite(ledPin, ledState);  // Update the actual LED
  } else if (ledState == LOW && (currentMillis - previousMillis >= offTime)) {
    ledState = HIGH;  // Turn it on
    previousMillis = currentMillis;  // Remember the time
    digitalWrite(ledPin, ledState);  // Update the actual LED
  }
}
