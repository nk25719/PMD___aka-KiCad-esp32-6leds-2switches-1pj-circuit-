#include <Arduino.h>

const int ledPin = 19;          // LED pin
//const int buttonPin = 36;      // Button pin
const int buttonPin = 35;      // Button pin

unsigned long previousMillis = 0;  // To store last time LED was updated

// Timing for the LED blink rates
const unsigned long normalOnTime = 500;
const unsigned long normalOffTime = 500;
const unsigned long fastOnTime = 200;
const unsigned long fastOffTime = 100;

unsigned long onTime = normalOnTime;  // Current on time
unsigned long offTime = normalOffTime;  // Current off time

bool ledState = HIGH;  // Initial LED state
bool buttonState;     // Current button state
bool lastButtonState = HIGH;  // Last button state (assuming pull-up)

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP); // Assuming the button is connected to GND
  Serial.begin(115200);
}

void loop() {
  unsigned long currentMillis = millis();
  buttonState = digitalRead(buttonPin);

  // Check if the button state has changed from HIGH to LOW (button press)
  if (buttonState == LOW && lastButtonState == HIGH) {
    // Toggle fastBlink mode
    if (onTime == normalOnTime) {  // If currently in normal mode, switch to fast
      onTime = fastOnTime;
      offTime = fastOffTime;
    } else {  // If currently in fast mode, switch to normal
      onTime = normalOnTime;
      offTime = normalOffTime;
    }
//    delay(50); // Debounce delay
  }
  lastButtonState = buttonState;  // Update the last button state

  // Check to update LED state based on the current time and on/off durations
  if ((ledState == HIGH && (currentMillis - previousMillis >= onTime)) || 
      (ledState == LOW && (currentMillis - previousMillis >= offTime))) {
    ledState = !ledState;  // Toggle the state
    digitalWrite(ledPin, ledState);  // Update the actual LED
    previousMillis = currentMillis;  // Reset the timer
    Serial.print(millis());
    Serial.print(" ");
    Serial.println(ledState ? "LED turned on" : "LED turned off");
  }
}