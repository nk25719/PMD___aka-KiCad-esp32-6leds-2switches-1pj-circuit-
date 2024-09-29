
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

SoftwareSerial mySoftwareSerial(16, 17);  // RX, TX for DFPlayer
DFRobotDFPlayerMini myDFPlayer;
LiquidCrystal_I2C lcd(0x3F, 20, 4);  // Address 0x3F, 20 columns, 4 rows

void setup() {

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

     // Turning on LEDs 
    digitalWrite(lamp1Pin,  HIGH);
    digitalWrite(lamp2Pin,  HIGH);
    digitalWrite(lamp3Pin,  HIGH);
    digitalWrite(lamp4Pin,  HIGH);
    digitalWrite(lamp5Pin,  HIGH);
    digitalWrite(LED_PIN0,  HIGH);

    // Initialize peripherals
    mySoftwareSerial.begin(9600);
    Wire.begin();
    lcd.init();
    lcd.backlight();
    
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Running setup...");

    // // Start DF player
    // startDFPlayer();
    // menuOptions();

    delay(200);

    // Turning off LEDs 
    digitalWrite(lamp1Pin,  LOW);
    digitalWrite(lamp2Pin,  LOW);
    digitalWrite(lamp3Pin,  LOW);
    digitalWrite(lamp4Pin,  LOW);
    digitalWrite(lamp5Pin,  LOW);
    digitalWrite(LED_PIN0,  LOW);
    Serial.println("end of setup");

  
}

void loop() {
    
   
    // muteButton();
    // handleONOFFButton();
   blinkLamp();

    }

// void handleONOFFButton() {

//     bool reading = digitalRead(ON_OFF_BUTTON_PIN);
    
  
//     if ((millis() - lastDebounceTime) > debounceDelay) {
//         if (reading != buttonPressed) {
//             buttonPressed = reading;
//             if (buttonPressed == LOW) { // Button pressed (active low)
           
//                 digitalWrite(LED_PIN, ledState ? HIGH : LOW);
//                 Serial.println(ledState ? "KRAKE ON" : "KRAKE OFF");
                
//                 // Turn off all GPIO pins when the ON/OFF button is pressed
//                 if (ledState == LOW) {
//                     for (int pin = 0; pin <= 39; ++pin) {
//                         if (pin != MUTE_BUTTON_PIN && pin != ON_OFF_BUTTON_PIN && pin != LED_PIN) {
//                             digitalWrite(pin, LOW);
//                         }
//                     }
//                 }
//             }
//         }
//     }
    
// }



// void muteButton() {
//     int currentState = digitalRead(MUTE_BUTTON_PIN);
    
//         Serial.println("Mute Button released");
//         if (trackPlaying) {
//             myDFPlayer.pause();
//             trackPlaying = false;
//             delay(600000);  // Alarm paused for 10 minutes
//             lcd.clear();
//             lcd.setCursor(0, 0);
//             lcd.print("Alarm Paused");
//         } else {
//             myDFPlayer.start();
//             trackPlaying = true;
//             lcd.clear();
//             lcd.setCursor(0, 0);
//             lcd.print("Alarm Resumed");
//         }
//      }



void startDFPlayer() {
  if (!myDFPlayer.begin(mySoftwareSerial)) {
    Serial.println("Unable to begin DFPlayer");
    while (true);
  }
  myDFPlayer.setTimeOut(500);
  myDFPlayer.volume(25);  // Set initial volume
  myDFPlayer.EQ(0);  // Normal equalization
  Serial.println("DFPlayer initialized");
}

void blinkLamp() {
 // Turning on LEDs 
    digitalWrite(lamp1Pin,  HIGH);
    digitalWrite(lamp2Pin,  HIGH);
    digitalWrite(lamp3Pin,  HIGH);
    digitalWrite(lamp4Pin,  HIGH);
    digitalWrite(lamp5Pin,  HIGH);
    digitalWrite(LED_PIN0,  HIGH);
    Serial.println("LEDs are On");

delay (1000);

 // Turning off LEDs 
    digitalWrite(lamp1Pin,  LOW);
    digitalWrite(lamp2Pin,  LOW);
    digitalWrite(lamp3Pin,  LOW);
    digitalWrite(lamp4Pin,  LOW);
    digitalWrite(lamp5Pin,  LOW);
    digitalWrite(LED_PIN0,  LOW);

    Serial.println("LEDs are Off");


    delay (200);

  }




// void menuOptions() {
//   Serial.println();
//   Serial.println("================================================================");
//   Serial.println("Commands:");
//   Serial.println(" [1-5] Select MP3 file");
//   Serial.println(" [p] Pause/resume");
//   Serial.println(" [vX] Set volume (0-30)");
//   Serial.println(" [+ or -] Increase or decrease volume");
//   Serial.println(" [r] Enable repeat mode");
//   Serial.println("================================================================");


// }