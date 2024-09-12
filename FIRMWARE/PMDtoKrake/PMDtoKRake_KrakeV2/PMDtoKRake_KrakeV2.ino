/*
   Need the copy write and license statements here.

*/

#define COMPANY_NAME "pubinv.org "
#define PROG_NAME "PMDtoKRake_KrakeV2 "
#define VERSION "V0.2 "
#define DEVICE_UNDER_TEST "PMD: foo"  //A PMD model number
#define LICENSE "GNU Affero General Public License, version 3 "
#define ORIGIN "USA"

#define BAUDRATE 115200
#define BAUD_DFPLAYER 9600

// Libraries
#include <WiFi.h>
#include <WebServer.h>
#include <DNSServer.h>
#include <HTTPClient.h>
#include <DFRobotDFPlayerMini.h>
#include <LiquidCrystal_I2C.h>
#include <WiFiManager.h>

// Configuration and Pin Definitions
const int analogPin = 26;
const int MUTE_BUTTON_PIN = 36;
const int ON_OFF_BUTTON_PIN = 39;
const int LED_PIN = 2; // On/Off LED
const int LED_PIN_M = 23; // Mute LED
const int lampPins[] = {15, 4, 5, 18, 19}; // Emergency lamp pins including MUTE LED
const int LCD_SCL = 22; // GPIO22 on PMD schematic
const int LCD_SDA = 21; // GPIO21 on PMD schematic
//const int DFPlayer_TX2 = 17; // GPIO17 on PMD schematic
//const int DFPlayer_TX2 = 16; // GPIO16 on PMD schematic


// Global Variables
bool ledState = false;
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;
bool lastButtonState = HIGH;
bool buttonPressed = false;
bool trackPlaying = false;
unsigned long previousMillis = 0;
const long interval = 100;

// LCD and DFPlayer Setup
HardwareSerial DFPlayerSerial(2); // DFPlaywer wired to UART2 pins. See above for pin numbers.
DFRobotDFPlayerMini myDFPlayer;

//LiquidCrystal_I2C lcd(0x27, 20, 4);
LiquidCrystal_I2C lcd(0x27, LCD_SCL, LCD_SDA);

// WiFi and Server Setup
const char* server_address = "192.168.1.3";
const int serverPort = 5500;
//const char* ssidAP = "ESP32-Access-Point";
//const char* passwordAP = "123456789";
const char* ssidAP = "ESP32";
const char* passwordAP = "";

const byte DNS_PORT = 53;
WebServer server(80);
DNSServer dnsServer;

String ssid = "";
String password = "";

// HTML for WiFi Credentials Input Page
const char* htmlPage = R"rawliteral(
<html>
<body>
<h1>Enter Wi-Fi Credentials</h1>
<form action="/connect" method="POST">
SSID:<br><input type="text" name="ssid"><br>
Password:<br><input type="password" name="password"><br><br>
<input type="submit" value="Submit">
</form>
</body>
</html>)rawliteral";

//Functions

void setupLCDandSplash(void){
  Wire.begin();
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print(DEVICE_UNDER_TEST);
  lcd.setCursor(0, 1);
  lcd.print(PROG_NAME);
  lcd.setCursor(0, 2);
  lcd.print(VERSION);
  lcd.setCursor(0, 3);
  lcd.print(F(__DATE__ " " __TIME__) ); //compile date that is used for a unique identifier
}

void lcdReportWiFiConnected(void){
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("WiFi Connected"); 
}



// Setup Function
void setup() {
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, HIGH); //Start of setup make build in LED on.
  Serial.begin(BAUDRATE);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB
  }
  Serial.println("===================================");
  Serial.println(DEVICE_UNDER_TEST);
  Serial.print(PROG_NAME);
  Serial.println(VERSION);
  Serial.print("Compiled at: ");
  Serial.println(F(__DATE__ " " __TIME__) ); //compile date that is used for a unique identifier

  setupLCDandSplash();

  //Setup DFPlayer
  DFPlayerSerial.begin(BAUD_DFPLAYER, SERIAL_8N1, 16, 17); // rx2,  tx2
  startDFPlayer();

//Setup Buttons
  pinMode(MUTE_BUTTON_PIN, INPUT_PULLUP);
  pinMode(ON_OFF_BUTTON_PIN, INPUT_PULLUP);

//Setup LEDs aka lamps
  for (int pin : lampPins) {
    pinMode(pin, OUTPUT);
  }

//Setup WiFi, dnsServer for soft AP, web server
  WiFi.softAP(ssidAP, passwordAP);
  Serial.println("Access Point Created");
  dnsServer.start(DNS_PORT, "*", WiFi.softAPIP());
  server.on("/", handleRoot);
  server.on("/connect", HTTP_POST, handleConnect);
  server.begin();
  Serial.println("Web Server started");

  WiFiManager wm;
  if (!wm.autoConnect("ESP32")) {
    Serial.println("Failed to connect");
    ESP.restart();
  }
  Serial.println("WiFi Connected");
  lcdReportWiFiConnected();
  delay(1000);

  //Display Menu on LCD
  menuOptions();

  digitalWrite(LED_PIN, LOW); //End of setup make build in LED off.
}

// Loop Function
void loop() {
  dnsServer.processNextRequest();
  server.handleClient();
  checkWiFiConnection();
  fetchEmergencyLevelOverWiFi();
  handlePinData();
  muteButton();
  handleONOFFButton();
}

// ON/OFF Button Handler
void handleONOFFButton() {
  bool reading = digitalRead(ON_OFF_BUTTON_PIN);
  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }

  if (millis() - lastDebounceTime > debounceDelay && reading != lastButtonState) {
    lastButtonState = reading;
    if (reading == LOW) { // Button pressed (active low)
      ledState = !ledState; // Toggle LED state
      digitalWrite(LED_PIN, ledState ? HIGH : LOW);
      Serial.println(ledState ? "KRAKE ON" : "KRAKE OFF");

      // Turn off all GPIO pins when the ON/OFF button is pressed
      if (!ledState) {
        for (int pin = 0; pin <= 39; ++pin) {
          if (pin != MUTE_BUTTON_PIN && pin != ON_OFF_BUTTON_PIN && pin != LED_PIN) {
            digitalWrite(pin, LOW);
          }
        }
      }
    }
  }
}

// Root Web Handler
void handleRoot() {
  server.send(200, "text/html", htmlPage);
}

// WiFi Connect Handler
void handleConnect() {
  unsigned long startTime = millis();
  int timeout = 30000;  // 30 seconds timeout

  ssid = server.arg("ssid");
  password = server.arg("password");

  server.send(200, "text/html", "<html><body><h1>Connecting...</h1></body></html>");
  WiFi.softAPdisconnect(true);
  WiFi.begin(ssid.c_str(), password.c_str());

  while (WiFi.status() != WL_CONNECTED && millis() - startTime < timeout) {
    Serial.println("Connecting to WiFi...");
    delay(100);
  }

  if (WiFi.status() == WL_CONNECTED) {
    String connectedPage = "<html><body><h1>ESP32 Connected to Wi-Fi</h1><p>IP Address: " + WiFi.localIP().toString() + "</p></body></html>";
    server.send(200, "text/html", connectedPage);
    Serial.println("Connected to WiFi");
  } else {
    server.send(200, "text/html", "<html><body><h1>Failed to connect. Please try again.</h1></body></html>");
    Serial.println("Failed to connect to WiFi");
    WiFi.softAP(ssidAP, passwordAP);
  }
}

// Mute Button Handler
void muteButton() {
  static unsigned long lastDebounceTime = 0;
  static bool lastButtonState = HIGH;
  bool currentButtonState = digitalRead(MUTE_BUTTON_PIN);

  if (currentButtonState != lastButtonState) {
    lastDebounceTime = millis();
  }

  if (millis() - lastDebounceTime > debounceDelay && currentButtonState != lastButtonState) {
    lastButtonState = currentButtonState;
    if (currentButtonState == LOW) {
      Serial.println("Mute Button pressed");
      if (trackPlaying) {
        myDFPlayer.pause();
        trackPlaying = false;
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Alarm Paused");
      } else {
        myDFPlayer.start();
        trackPlaying = true;
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Alarm Resumed");
        digitalWrite(LED_PIN_M, HIGH);
      }
    }
  }
}

// Handle Analog Pin Data
void handlePinData() {
  int sensorValue = analogRead(analogPin);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Analog Pin Value:");
  lcd.setCursor(0, 1);
  lcd.print(sensorValue);
  Serial.println("Sensor Value: " + String(sensorValue));
  sendSensorValueToHTTPServer(sensorValue);
  sendSensorValueOverWiFi(sensorValue);
  int emergencyLevel = fetchEmergencyLevelOverWiFi();
  handleEmergencyLamps(emergencyLevel);
}

// Function to Send Sensor Value to HTTP Server
void sendSensorValueToHTTPServer(int sensorValue) {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    String url = "/update";
    String postData = "value=" + String(sensorValue);

    // Construct full URL with server address and port
    String fullUrl = String("http://") + server_address + ":" + serverPort + url;

    http.begin(fullUrl); // Use full URL with server and port
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");

    int httpCode = http.POST(postData);

    if (httpCode == 200) {
      Serial.println("HTTP POST request successful");
      Serial.println(http.getString());
    } else {
      Serial.println("HTTP POST request failed");
      Serial.println("HTTP Code: " + String(httpCode));
    }
    http.end();
  } else {
    Serial.println("WiFi not connected");
  }
}

// Function to Send Sensor Value Over WiFi
void sendSensorValueOverWiFi(int value) {
  if (WiFi.status() == WL_CONNECTED) {
    WiFiClient client;
    String url = "/update?value=" + String(value);
    if (client.connect(server_address, serverPort)) {
      client.print(String("GET ") + url + " HTTP/1.1\r\n" +
                   "Host: " + server_address + "\r\n" +
                   "Connection: close\r\n\r\n");

      while (client.connected()) {
        String line = client.readStringUntil('\n');
        Serial.println(line);
      }
      client.stop();
      Serial.println("Server disconnected");
    } else {
      Serial.println("Connection to server failed");
    }
  } else {
    Serial.println("WiFi not connected");
  }
}

// Check WiFi Connection
void checkWiFiConnection() {
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("WiFi lost, reconnecting...");
    WiFiManager wm;
    if (!wm.autoConnect("ESP32_AP")) {
      Serial.println("Failed to reconnect");
      ESP.restart();
    }
  }
}

// Start DFPlayer
void startDFPlayer() {
  Serial.println("Initializing DFPlayer...");

  if (!myDFPlayer.begin(DFPlayerSerial)) {
    Serial.println("DFPlayer Mini not detected:");
    Serial.println("1. Please check the wiring!");
    Serial.println("2. Please insert the SD card!");
    while (true);
  }

  delay(1000);  // Add a delay to ensure the player has time to initialize
  myDFPlayer.setTimeOut(500);
  myDFPlayer.volume(25);
  myDFPlayer.EQ(DFPLAYER_EQ_NORMAL);
  myDFPlayer.outputDevice(DFPLAYER_DEVICE_SD);

  Serial.println("DFPlayer Mini initialized successfully.");
}

// Fetch Emergency Level Over WiFi
int fetchEmergencyLevelOverWiFi() {
  WiFiClient client;
  String url = "/emergency";
  if (client.connect(server_address, serverPort)) {
    client.print(String("GET ") + url + " HTTP/1.1\r\n" +
                 "Host: " + server_address + "\r\n" +
                 "Connection: close\r\n\r\n");

    while (client.available()) {
      String line = client.readStringUntil('\n');
      if (line.startsWith("{\"level\":")) {
        int emergencyLevel = line.substring(9).toInt();
        return emergencyLevel;
      }
    }
    client.stop();
    Serial.println("Server disconnected");
  } else {
    Serial.println("Connection to server failed");
  }
  return 0;
}

// Blink Lamp Function
void blinkLamp(int lampPin, unsigned long blinkInterval) {
  static unsigned long lastBlinkTime = 0;
  if (millis() - lastBlinkTime >= blinkInterval) {
    int state = digitalRead(lampPin);
    digitalWrite(lampPin, !state);
    lastBlinkTime = millis();
  }
}

// Handle Emergency Lamps
void handleEmergencyLamps(int emergencyLevel) {
  unsigned long currentMillis = millis();
  switch (emergencyLevel) {
    case 1:
      blinkLamp(lampPins[0], 750);
      myDFPlayer.play(emergencyLevel);
      myDFPlayer.enableLoop();
      break;
    case 2:
      blinkLamp(lampPins[1], 600);
      myDFPlayer.play(emergencyLevel);
      myDFPlayer.enableLoop();
      break;
    case 3:
      blinkLamp(lampPins[2], 450);
      myDFPlayer.play(emergencyLevel);
      myDFPlayer.enableLoop();
      break;
    case 4:
      blinkLamp(lampPins[3], 300);
      myDFPlayer.play(emergencyLevel);
      myDFPlayer.enableLoop();
      break;
    case 5:
      blinkLamp(lampPins[4], 150);
      myDFPlayer.play(emergencyLevel);
      myDFPlayer.enableLoop();
      break;
    default:
      for (int pin : lampPins) {
        digitalWrite(pin, LOW);
      }
      break;
  }
}

// Menu Options
void menuOptions() {
  Serial.println();
  Serial.println("================================================================");
  Serial.println("Commands:");
  Serial.println(" [1-5] Select MP3 file");
  Serial.println(" [p] Pause/resume");
  Serial.println(" [vX] Set volume (0-30)");
  Serial.println(" [+ or -] Increase or decrease volume");
  Serial.println(" [r] Enable repeat mode");
  Serial.println("================================================================");
}
