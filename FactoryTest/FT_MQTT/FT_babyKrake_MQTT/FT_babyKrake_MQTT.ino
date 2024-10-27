// File name: FT_PMD_MQTT  (was MQTT_ESP32DevelopmentBoard)
// Author: Forrest Lee Erickson
// Date: 20241006
// Update 20241008 with WINK and toggle D9 when sending MQTT on line message.
// Manage LEDS. Add serial splash.
// Update 20241015 Reports IP address on serial port. Change file name.

//Set your device Model_Serial on line 12. 
// This will be the subscription topic to which the devices listens. 
// It must match the device list for which the MQTT_PMD_DAT_TOPIC or other publisher sends.
// Example devices include: PMD_LB4, PMD_Austin1.  
// No spaces.
#define MODEL_SERIAL "20240421_LEB1" 


// This example uses an ESP32 Development Board
// to connect to shiftr.io.
//
// You can check on your device after a successful
// connection here: https://www.shiftr.io/try.
//
// by Joël Gähwiler
// https://github.com/256dpi/arduino-mqtt


#define PROG_NAME "FT_PMD_MQTT "
#define VERSION "V0.4 "
#define DEVICE_UNDER_TEST "PMD SN: USA1"  //A PMD model  and Serial Number
#define LICENSE "GNU Affero General Public License, version 3 "
#define ORIGIN "USA"

//Setup for your WiFi router here
//const char ssid[] = "ssid";
//const char pass[] = "pass";

////LB network
const char ssid[] = "ADT";
const char pass[] = "adt@12345";

//Maryville network
// const char ssid[] = "VRX";
// const char pass[] = "textinsert";

// Some PMD Hardware
// Pins for switches
#define BOOT_BUTTON 0
#define SW1_BUTTON 36
#define SW2_BUTTON 39
#define SW3_BUTTON 34
#define SW4_BUTTON 35

// Pins for switches
//const int switchPin1 = 36; // Switch 1 connected to GPIO 36
//const int switchPin2 = 39; // Switch 2 connected to GPIO 39
//const int switchPin3 = 34; // Switch 3 connected to GPIO 34
//const int switchPin4 = 35; // Switch 4 connected to GPIO 35

// PMD LAMPS aka Other LEDs
const int LED_D9 = 23;    // Mute1 LED on PMD
const int LAMP1 = 15;    // D5 cold food
const int LAMP2 = 4;    // D3 baby crying
const int LAMP3 = 5;    // D8 high BP1
const int LAMP4 = 18;    // D7 shield failure
const int LAMP5 = 19;    // D6 lost sock


//MQTT constants
#define BROKER_URL "public.cloud.shiftr.io"
#define KRAKE_DTA_TOPIC "KRAKE_DTA_TOPIC" //To address the KRAKE data channel
#define KRAKE_CTL_TOPIC "KRAKE_CTL_TOPIC"  //To address the KRAKE control channel

//A Processinge PMD Device to which to subscribe
#define PROCESSING_PMD_DTA_TOPIC_USA "PROCESSING_PMD_USA1_DTA_TOPIC_USA_MARYVILLE" //Subscribe to a unique PMD device in USA
#define PROCESSING_PMD_DTA_TOPIC_LB "PROCESSING_PMD_DTA_TOPIC_LB" //Subscribe to a unique PMD device in USA


//Choose only one PMD Device to which to subscribe
//#define PMD_DTA_TOPIC "PMD_DTA_TOPIC_USA1" //Subscribe to a unique PMD device in USA
//#define PMD_DTA_TOPIC "PMD_DTA_TOPIC_USA2" //Subscribe to a unique PMD device in USA
//#define PMD_DTA_TOPIC "PMD_DTA_TOPIC_USA3" //Subscribe to a unique PMD device in USA
#define PMD_DTA_TOPIC "PMD_DTA_TOPIC_USA4" //Subscribe to a unique PMD device in USA
//#define PMD_DTA_TOPIC "PMD_DTA_TOPIC_USA5" //Subscribe to a unique PMD device in USA

//#define PMD_DTA_TOPIC "PMD_LB1_DTA_TOPIC" //Subscribe to a unique PMD device in Lebanon
//#define PMD_DTA_TOPIC "PMD_LB2_DTA_TOPIC" //Subscribe to a unique PMD device in Lebanon
//#define PMD_DTA_TOPIC "PMD_LB3_DTA_TOPIC" //Subscribe to a unique PMD device in Lebanon
//#define PMD_DTA_TOPIC "PMD_LB4_DTA_TOPIC" //Subscribe to a unique PMD device in Lebanon
//#define PMD_DTA_TOPIC "PMD_LB5_DTA_TOPIC" //Subscribe to a unique PMD device in Lebanon


#include <WiFi.h>
#include <MQTT.h>

// Heart beat aka activity indicator LED.
//Set LED for Uno or ESP32 Dev Kit on board blue LED.
const int LED_BUILTIN = 2;    // ESP32 Kit
//const int LED_BUILTIN = 13;    //Not really needed for Arduino UNO it is defined in library
const int HIGH_TIME_LED = 900;
const int LOW_TIME_LED = 100;
unsigned long lastLEDtime = 0;
unsigned long nextLEDchange = 100; //time in ms.


#define BAUDRATE 115200

WiFiClient net;
MQTTClient client;

unsigned long lastMillis = 0;  // Sets timing for periodic MQTT publish message

//Setup WiFi and MQTT subscriptions.
void connect() {
  Serial.print("checking wifi...");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
  }

  Serial.print("Connected at IP: ");
  Serial.println(WiFi.localIP().toString());

  Serial.print("\nconnecting...");
  while (!client.connect("arduino", "public", "public")) {
    Serial.print(".");
    delay(1000);
  }

  Serial.println("\nWiFi connected!");

  // Setup up MQTT services to which this device (KRAKE) subscribes
  client.subscribe(PROCESSING_PMD_DTA_TOPIC_USA);    //Subscribes to a Processing PMD data channel from USA
  client.subscribe(PROCESSING_PMD_DTA_TOPIC_LB);    //Subscribes to a Processing PMD data channel from LB
  //client.subscribe(KRAKE_CTL_TOPIC);  //Listens to self
  client.subscribe(PMD_DTA_TOPIC);    //Subscribes to a PMD data channel

}//end connect()

// Setup to receive, subscribe to topics.
void messageReceived(String &topic, String &payload) {
  Serial.println("incoming: " + topic + " - " + payload);

  // Note: Do not use the client in the callback to publish, subscribe or
  // unsubscribe as it may cause deadlocks when other things arrive while
  // sending and receiving acknowledgments. Instead, change a global variable,
  // or push to a queue and handle it in the loop after calling `client.loop()`.

  proccessPayloadOnLamps(payload);  // Change LAMPS baised on the payload

}//end message received


// A periodic message identifying the subscriber (Krake) is on line.
void publishOnLineMsg(void) {
  // publish a message roughly every second.
  if (millis() - lastMillis > 10000) {
    lastMillis = millis();
    client.publish(MODEL_SERIAL, " is online");
    digitalWrite(LED_D9, !digitalRead(LED_D9));   // Toggle
  }
}


void setupPMD_LEDS(void) {
  // Setup PMD LEDs
  pinMode(LED_D9, OUTPUT);      // set the Mute LED pin mode
  digitalWrite(LED_D9, HIGH);   // turn the LED on (HIGH is the voltage level)
  pinMode(LAMP1, OUTPUT);      // set the Mute LED pin mode
  digitalWrite(LAMP1, HIGH);   // turn the LED on (HIGH is the voltage level)
  pinMode(LAMP2, OUTPUT);      // set the Mute LED pin mode
  digitalWrite(LAMP2, HIGH);   // turn the LED on (HIGH is the voltage level)
  pinMode(LAMP3, OUTPUT);      // set the Mute LED pin mode
  digitalWrite(LAMP3, HIGH);   // turn the LED on (HIGH is the voltage level)
  pinMode(LAMP4, OUTPUT);      // set the Mute LED pin mode
  digitalWrite(LAMP4, HIGH);   // turn the LED on (HIGH is the voltage level)
  pinMode(LAMP5, OUTPUT);      // set the Mute LED pin mode
  digitalWrite(LAMP5, HIGH);   // turn the LED on (HIGH is the voltage level)
}//end setupPMD_LEDS


void proccessPayloadOnLamps(String &payload) {
  // Proccess payload on LAMPs
  digitalWrite(LAMP1, LOW);
  digitalWrite(LAMP2, LOW);
  digitalWrite(LAMP3, LOW);
  digitalWrite(LAMP4, LOW);
  digitalWrite(LAMP5, LOW);

  if (payload < "1") {
    //Turn off all LAMPS
    digitalWrite(LAMP1, LOW);
    digitalWrite(LAMP2, LOW);
    digitalWrite(LAMP3, LOW);
    digitalWrite(LAMP4, LOW);
    digitalWrite(LAMP5, LOW);
  } else if (payload == "MessageFromProcessing_PMD: 1") {
    //Turn on only LAMP 1
    digitalWrite(LAMP1, HIGH);
    digitalWrite(LAMP2, LOW);
    digitalWrite(LAMP3, LOW);
    digitalWrite(LAMP4, LOW);
    digitalWrite(LAMP5, LOW);
  } else if (payload == "MessageFromProcessing_PMD: 2") {
    //Turn on only LAMP 2
    digitalWrite(LAMP1, LOW);
    digitalWrite(LAMP2, HIGH);
    digitalWrite(LAMP3, LOW);
    digitalWrite(LAMP4, LOW);
    digitalWrite(LAMP5, LOW);
  } else if (payload == "MessageFromProcessing_PMD: 3") {
    //Turn on only LAMP 3
    digitalWrite(LAMP1, LOW);
    digitalWrite(LAMP2, LOW);
    digitalWrite(LAMP3, HIGH);
    digitalWrite(LAMP4, LOW);
    digitalWrite(LAMP5, LOW);
  } else if (payload == "MessageFromProcessing_PMD: 4") {
    //Turn on only LAMP 4
    digitalWrite(LAMP1, LOW);
    digitalWrite(LAMP2, LOW);
    digitalWrite(LAMP3, LOW);
    digitalWrite(LAMP4, HIGH);
    digitalWrite(LAMP5, LOW);
  } else if (payload == "MessageFromProcessing_PMD: 5") {
    //Turn on only LAMP 5
    digitalWrite(LAMP1, LOW);
    digitalWrite(LAMP2, LOW);
    digitalWrite(LAMP3, LOW);
    digitalWrite(LAMP4, LOW);
    digitalWrite(LAMP5, HIGH);
  } else if (payload == "MessageFromProcessing_PMD: 6") {
    //Turn on only LAMP 5
    digitalWrite(LAMP1, HIGH);
    digitalWrite(LAMP2, HIGH);
    digitalWrite(LAMP3, HIGH);
    digitalWrite(LAMP4, HIGH);
    digitalWrite(LAMP5, HIGH);
  }// end parsing message
}// end proccessPayloadOnLamps

//Some more functions

//Wink the LED
void wink(void) {
  if (((millis() - lastLEDtime) > nextLEDchange) || (millis() < lastLEDtime)) {
    if (digitalRead(LED_BUILTIN) == LOW) {
      digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
      nextLEDchange = HIGH_TIME_LED;
    } else {
      digitalWrite(LED_BUILTIN, LOW);   // turn the LED on (HIGH is the voltage level)
      nextLEDchange = LOW_TIME_LED;
    }
    lastLEDtime = millis();
  }
}//end LED wink


// The Setup
void setup() {
  pinMode(LED_BUILTIN, OUTPUT);      // set the LED pin mode
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)

  setupPMD_LEDS();

  Serial.begin(BAUDRATE);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB
  }
  delay(500);
  //Serial splash
  Serial.println("===================================");
  Serial.println(DEVICE_UNDER_TEST);
  Serial.print(PROG_NAME);
  Serial.println(VERSION);
  Serial.print("Compiled at: ");
  Serial.println(F(__DATE__ " " __TIME__) ); //compile date that is used for a unique identifier
  Serial.println("===================================");
  Serial.println();


  WiFi.begin(ssid, pass);

  // Note: Local domain names (e.g. "Computer.local" on OSX) are not supported
  // by Arduino. You need to set the IP address directly.
  client.begin(BROKER_URL, net);
  client.onMessage(messageReceived);

  connect();

  digitalWrite(LED_D9, LOW);   // turn the LEDs at end of setup
  digitalWrite(LED_BUILTIN, LOW);

}//end setup()

void loop() {
  client.loop();
  delay(10);  // <- fixes some issues with WiFi stability
  if (!client.connected()) {
    Serial.println("Connecting again");
    connect();
  }
  publishOnLineMsg();
  wink();
}//end loop()
