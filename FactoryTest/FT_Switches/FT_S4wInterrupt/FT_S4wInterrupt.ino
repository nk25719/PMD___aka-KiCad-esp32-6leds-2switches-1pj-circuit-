// ref info
// https://randomnerdtutorials.com/esp32-pir-motion-sensor-interrupts-timers/ 

// https://www.youtube.com/watch?v=PcqiKy_rb24

/*********
  Rui Santos
  Complete project details at https://randomnerdtutorials.com  
*********/

#define timeSeconds 1
#define BAUDRATE 115200

// Set GPIOs for LED and PIR Motion Sensor
const int led = 23;
const int Interrupt = 35;

// Timer: Auxiliary variables
unsigned long now = millis();
unsigned long lastTrigger = 0;
boolean startTimer = false;
boolean motion = false;

// Checks if motion was detected, sets LED HIGH and starts a timer
void IRAM_ATTR detectsMovement() {
  digitalWrite(led, HIGH);
  startTimer = true;
  lastTrigger = millis();
}

void setup() {
  // Serial port for debugging purposes
  Serial.begin(BAUDRATE);
  
  // PIR Motion Sensor mode INPUT_PULLUP
  pinMode(Interrupt, INPUT_PULLUP);
  // Set Interrupt pin as interrupt, assign interrupt function and set RISING mode
  attachInterrupt(digitalPinToInterrupt(Interrupt), detectsMovement, RISING);

  // Set LED to LOW
  pinMode(led, OUTPUT);
  digitalWrite(led, LOW);
}

void loop() {
  // Current time
  now = millis();
  if((digitalRead(led) == HIGH) && (motion == false)) {
    Serial.println("interrupt DETECTED!!!");
    motion = true;
  }
  // Turn off the LED after the number of seconds defined in the timeSeconds variable
  if(startTimer && (now - lastTrigger > (timeSeconds*1000))) {
    Serial.println("interrupt stopped...");
    digitalWrite(led, LOW);
    startTimer = false;
    motion = false;
  }
}