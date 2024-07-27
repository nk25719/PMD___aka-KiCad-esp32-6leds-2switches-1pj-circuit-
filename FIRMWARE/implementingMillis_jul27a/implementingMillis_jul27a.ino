#include <WiFi.h>
#include <HTTPClient.h>
#include <SoftwareSerial.h>
#include <DFRobotDFPlayerMini.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <WiFiManager.h>

WiFiServer server(80);
const char *server_address = "192.168.1.3";
const int serverPort = 5500;
const int analogPin = 34;
const int BUTTON_PIN = 36;
const int lamp1Pin = 2;
const int lamp2Pin = 4;
const int lamp3Pin = 5;
const int lamp4Pin = 18;
const int lamp5Pin = 19;
SoftwareSerial mySoftwareSerial(16, 17);  // RX, TX for DFPlayer
DFRobotDFPlayerMini myDFPlayer;
bool trackPlaying = false;
String line;
char command;
unsigned long previousMillis = 0;
unsigned long previousButtonMillis = 0;
const long interval = 100;
const long buttonDebounceTime = 50;
LiquidCrystal_I2C lcd(0x3F, 20, 4);  // Address 0x3F, 20 columns, 4 rows
int lastState = LOW; // the previous state (is low) from the input pin
int currentState;     // the current reading from the input pin
unsigned long alarmPauseMillis = 0;
const unsigned long alarmPauseDuration = 600000; // 10 minutes

void setup() {
  Serial.begin(115200);
  mySoftwareSerial.begin(9600);  // DFPlayer serial communication
  Wire.begin();  // Initialize I2C communication
  lcd.init();  // Initialize LCD
  lcd.backlight();  // Turn on LCD backlight
  pinMode(BUTTON_PIN, INPUT_PULLUP);  // Initialize button pin
  pinMode(lamp1Pin, OUTPUT);
  pinMode(lamp2Pin, OUTPUT);
  pinMode(lamp3Pin, OUTPUT);
  pinMode(lamp4Pin, OUTPUT);
  pinMode(lamp5Pin, OUTPUT);

  // Initialize WiFiManager
  WiFiManager wm;
  if(!wm.autoConnect("ESP32_AP")) {
    Serial.println("Failed to connect");
    ESP.restart();
  }

  // Connected to WiFi
  Serial.println("Connected to WiFi");
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("WiFi Connected");

  // Start DF player
  startDFPlayer();
  // Start server
  server.begin();
  Serial.println();
  Serial.println(F("DFRobot DFPlayer Mini"));
  Serial.println(F("Initializing DFPlayer module ... Wait!"));
  if (!myDFPlayer.begin(mySoftwareSerial)) {
    Serial.println(F("Not initialized:"));
    Serial.println(F("1. Check the DFPlayer Mini connections"));
    Serial.println(F("2. Insert an SD card"));
    while (true);
  }
  Serial.println();
  Serial.println(F("DFPlayer Mini module initialized!"));
  myDFPlayer.setTimeOut(500);  // Serial timeout 500ms
  myDFPlayer.volume(25);        // Volume 25
  myDFPlayer.EQ(0);            // Normal equalization
  menuOptions();  // Display menu options on serial monitor
}

void loop() {
  unsigned long currentMillis = millis();
  checkWiFiConnection();
  fetchEmergencyLevelOverWiFi();
  handleWiFiClientRequests();
  handlePinData();
  muteButton(currentMillis);
  pauseOrResumeAlarm(currentMillis);
}

void pauseOrResumeAlarm(unsigned long currentMillis) {
  currentState = digitalRead(BUTTON_PIN);
  if ((currentMillis - previousButtonMillis >= buttonDebounceTime) && (lastState == LOW && currentState == HIGH)) {
    Serial.println("Button released");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Alarm Paused");
    if (trackPlaying) {
      myDFPlayer.pause();
      trackPlaying = false;
      alarmPauseMillis = currentMillis;
    } else {
      myDFPlayer.start();
      trackPlaying = true;
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Alarm Resumed");
    }
    previousButtonMillis = currentMillis;
  }
  if (trackPlaying == false && currentMillis - alarmPauseMillis >= alarmPauseDuration) {
    myDFPlayer.start();
    trackPlaying = true;
    Serial.println("Resumed.");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Alarm Resumed");
  }
  lastState = currentState;
}

void muteButton(unsigned long currentMillis) {
  int lastState = LOW; 
  int currentState = digitalRead(BUTTON_PIN);
  if ((currentMillis - previousButtonMillis >= buttonDebounceTime) && (lastState == LOW && currentState == HIGH)) {
    Serial.println("Button released");
    if (trackPlaying) {
      myDFPlayer.pause();
      trackPlaying = false;
      alarmPauseMillis = currentMillis;
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Alarm Paused");
    } else {
      myDFPlayer.start();
      trackPlaying = true;
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Alarm Resumed");
    }
    previousButtonMillis = currentMillis;
  }
  lastState = currentState;
}

void handleWiFiClientRequests() {
  WiFiClient client = server.available();
  if (client) {
    while (client.connected()) {
      if (client.available()) {
        String line = client.readStringUntil('\r');
        Serial.print("Received from client: ");
        Serial.println(line);
      }
    }
    client.stop();
    Serial.println("WiFi client disconnected");
  }
}

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
  Serial.println("Received Emergency Level: " + String(emergencyLevel));
  delay(700);
  handleEmergencyLamps(emergencyLevel);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Emergency level:");
  lcd.setCursor(0, 1);
  lcd.print(emergencyLevel);
}

void sendSensorValueToHTTPServer(int sensorValue) {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    String url = "/update";
    String postData = "value=" + String(sensorValue);
    http.begin(server_address, serverPort, url);
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

void checkWiFiConnection() {
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("WiFi lost, reconnecting...");
    WiFiManager wm;
    if(!wm.autoConnect("ESP32_AP")) {
      Serial.println("Failed to connect");
      ESP.restart();
    }
  }
}

void startDFPlayer() {
  if (!myDFPlayer.begin(mySoftwareSerial)) {
    Serial.println("Unable to begin DFPlayer");
    while (true);
  }
  myDFPlayer.setTimeOut(500);
  myDFPlayer.volume(25);  // Set initial volume
  myDFPlayer.EQ(0);  // Normal equalization
}

int fetchEmergencyLevelOverWiFi() {
  WiFiClient client;
  String url = "/emergency";
  if (client.connect(server_address, serverPort)) {
    client.print(String("GET ") + url + " HTTP/1.1\r\n" +
                 "Host: " + server_address + "\r\n" +
                 "Connection: close\r\n\r\n");
    while (client.available()) {
      String line = client.readStringUntil('\n');
      Serial.print("read this: ");
      Serial.println(line);
      if (line.startsWith("EmergencyLevel:")) {
        int emergencyLevel = line.substring(15).toInt();
        return emergencyLevel;
      }
    }
    client.stop();
  } else {
    Serial.println("Connection to server failed");
  }
  return -1; // return -1 if there was an error
}

void handleEmergencyLamps(int emergencyLevel) {
  digitalWrite(lamp1Pin, emergencyLevel > 0 ? HIGH : LOW);
  digitalWrite(lamp2Pin, emergencyLevel > 1 ? HIGH : LOW);
  digitalWrite(lamp3Pin, emergencyLevel > 2 ? HIGH : LOW);
  digitalWrite(lamp4Pin, emergencyLevel > 3 ? HIGH : LOW);
  digitalWrite(lamp5Pin, emergencyLevel > 4 ? HIGH : LOW);
}

void menuOptions() {
  Serial.println(F("DFPlayer Mini Options:"));
  Serial.println(F("1: Play"));
  Serial.println(F("2: Stop"));
  Serial.println(F("3: Pause"));
  Serial.println(F("4: Next"));
  Serial.println(F("5: Previous"));
  Serial.println(F("6: Volume Up"));
  Serial.println(F("7: Volume Down"));
  Serial.println(F("8: Query current status"));
}
