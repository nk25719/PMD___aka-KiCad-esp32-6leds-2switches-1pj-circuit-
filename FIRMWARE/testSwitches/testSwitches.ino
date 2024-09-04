// Pins for switches
const int switchPin1 = 36; // Switch 1 connected to GPIO 36
const int switchPin2 = 39; // Switch 2 connected to GPIO 39
const int switchPin3 = 34; // Switch 3 connected to GPIO 34
const int switchPin4 = 35; // Switch 4 connected to GPIO 35

// Variable to store the current state of each switch
int currentSwitchState1 = HIGH;
int currentSwitchState2 = HIGH;
int currentSwitchState3 = HIGH;
int currentSwitchState4 = HIGH;

// Variable to store the previous state of each switch
int lastSwitchState1 = HIGH;
int lastSwitchState2 = HIGH;
int lastSwitchState3 = HIGH;
int lastSwitchState4 = HIGH;

void setup() {
  Serial.begin(115200);

  // Set up each switch pin as an input with pull-up
  pinMode(switchPin1, INPUT_PULLUP);
  pinMode(switchPin2, INPUT_PULLUP);
  pinMode(switchPin3, INPUT_PULLUP);
  pinMode(switchPin4, INPUT_PULLUP);

  Serial.println("Switch Testing Initialized...");
}

void loop() {
  // Read the current state of each switch
  currentSwitchState1 = digitalRead(switchPin1);
  currentSwitchState2 = digitalRead(switchPin2);
  currentSwitchState3 = digitalRead(switchPin3);
  currentSwitchState4 = digitalRead(switchPin4);

  // Check if the switch was just pressed (transition from HIGH to LOW)
  if (currentSwitchState1 == LOW && lastSwitchState1 == HIGH) {
    Serial.println("Switch 1 (GPIO 36) Pressed");
  }

  if (currentSwitchState2 == LOW && lastSwitchState2 == HIGH) {
    Serial.println("Switch 2 (GPIO 39) Pressed");
  }

  if (currentSwitchState3 == LOW && lastSwitchState3 == HIGH) {
    Serial.println("Switch 3 (GPIO 34) Pressed");
  }

  if (currentSwitchState4 == LOW && lastSwitchState4 == HIGH) {
    Serial.println("Switch 4 (GPIO 35) Pressed");
  }

  // Save the current state as the last state for the next loop iteration
  lastSwitchState1 = currentSwitchState1;
  lastSwitchState2 = currentSwitchState2;
  lastSwitchState3 = currentSwitchState3;
  lastSwitchState4 = currentSwitchState4;

  // Short delay for debounce (if needed)
  delay(50);
}
