// Press and HOLD a button and one and only one LED blinks faster
// issue #31:  https://github.com/nk25719/KiCad-esp32-6leds-2switches-1pj-circuit/issues/31
// Beirut, Lebanon - Current Time 9:55 PM EEST on Saturday, July 27, 2024 
// Nagham Kheir


const int ledPin = 2;
const int buttonPin = 36;

unsigned long previousMillis = 0;
unsigned long onTime = 500;
unsigned long offTime = 500;
unsigned long normalOnTime = 500;
unsigned long normalOffTime = 500;
unsigned long fastOnTime = 100;
unsigned long fastOffTime = 100;

bool ledState = LOW;
bool buttonState = HIGH;
bool lastButtonState = HIGH;
bool fastBlink = false;

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP); // Assuming the button is connected to GND
  Serial.begin(115200);
}

void loop() {
  unsigned long currentMillis = millis();
  buttonState = digitalRead(buttonPin);

  // Check if the button is pressed (active LOW)
  if (buttonState == LOW && lastButtonState == HIGH) {
    fastBlink = !fastBlink; // Toggle the fastBlink state
    if (fastBlink) {
      onTime = fastOnTime;
      offTime = fastOffTime;
    } else {
      onTime = normalOnTime;
      offTime = normalOffTime;
    }
    delay(50); // Debounce delay
  }

  lastButtonState = buttonState;

  updateLEDState(currentMillis);
}

void updateLEDState(unsigned long currentMillis) {
  if (ledState == HIGH && (currentMillis - previousMillis >= onTime)) {
    ledState = LOW;  // Turn it off
    previousMillis = currentMillis;  // Remember the time
    digitalWrite(ledPin, ledState);  // Update the actual LED
    Serial.println("LED turned off");
  } else if (ledState == LOW && (currentMillis - previousMillis >= offTime)) {
    ledState = HIGH;  // Turn it on
    previousMillis = currentMillis;  // Remember the time
    digitalWrite(ledPin, ledState);  // Update the actual LED
    Serial.println("LED turned on");
  }
}
 