// File: FT_processingPMD_MQTT 
// Author: Forrest Lee Erickson
// Date: 20241006
// Date: 20241016 Background change color on send and receive MQTT. Subscribe to 20240421_USA4.
// Date: 20241017 Set title on window.

// Pseude Medical Device in Processing. 
// This example sketch connects to the public shiftr.io instance and sends a message on every keystroke.
// After starting the sketch you can find the client here: https://www.shiftr.io/try.
//
// Note: If you're running the sketch via the Android Mode you need to set the INTERNET permission
// in Android > Sketch Permissions.
//
// by Joël Gähwiler
// https://github.com/256dpi/processing-mqtt


/*
#define PROG_NAME "FT_PMD_MQTT "
#define VERSION "V0.4 "
#define DEVICE_UNDER_TEST "PMD SN: USA1"  //A PMD model  and Serial Number
#define LICENSE "GNU Affero General Public License, version 3 "
#define ORIGIN "USA"
*/

String PROG_NAME = "FT_processingPMD_MQTT";
String VERSION = "V0.0 ";
// Set the topic for the Pseude Medical Device in Processing.
String PMD_DTA_TOPIC = "PROCESSING_PMD_USA1_DTA_TOPIC_USA_MARYVILLE";
//String PMD_DTA_TOPIC = "PROCESSING_PMD_DTA_TOPIC_LB";


String thePayload = "";

import mqtt.*;

MQTTClient client;
String MessageFromProcessing_PMD = "";

class Adapter implements MQTTListener {
  void clientConnected() {
    println("client connected");

    client.subscribe("/hello");
    client.subscribe("PMD_LB1");
    client.subscribe("PMD_LB1");
    client.subscribe("PMD_LB1");
    client.subscribe("PMD_LB1");
    client.subscribe("PMD_LB1");
    client.subscribe("PMD_LB1");

    client.subscribe("PMD_Austin1");    

    client.subscribe("PMD_USA1");
    client.subscribe("PMD_USA2");
    client.subscribe("PMD_USA3");
    client.subscribe("PMD_USA4");
    client.subscribe("20240421_USA4");    
    client.subscribe("PMD_USA5");

    //    client.subscribe("KRAKE_DTA_TOPIC");
  }

  void messageReceived(String topic, byte[] payload) {
    thePayload = "Received message: " + topic + " - " + new String(payload);
//    println("new message: " + topic + " - " + new String(payload));
    println(thePayload);
    background(0); //Set background on messageReceived.
  }

  void connectionLost() {
    println("connection lost");
  }
}

Adapter adapter;

void setup() {
  //surface.setTitle("Hello World!");
  surface.setTitle(PROG_NAME + " Ver:" + VERSION);
  
  
  adapter = new Adapter();
  client = new MQTTClient(this, adapter);
  //  client.connect("mqtt://public:public@public.cloud.shiftr.io", "processing");
  client.connect("mqtt://public:public@public.cloud.shiftr.io", "Lee's processing");

  size(700, 360);
  //disables drawing outlines
  noStroke();
  //background(255, 4, 255);
  background(64);
  frameRate(24);

  client.publish(PMD_DTA_TOPIC, "FirstMessage PMD USA1");
  MessageFromProcessing_PMD = "FirstMessage PMD USA1";
}//end setup()

void draw() {
  //Need a heart beat message

  //Text on draw window
  fill(255);
  textSize(25);
  text("PMD_DTA_TOPIC: ", 10, 30);
  textSize(15);
  text(PMD_DTA_TOPIC, 225, 30);
  textSize(20);
  fill(200);
  text("Press digits 0-9", 10, 60);
  fill(252, 10, 55);
  text(MessageFromProcessing_PMD, 10, 80);
  fill(55, 10, 252);
  text(thePayload, 10, 100);
}//end draw()


void keyPressed() {
  int keyIndex = -1;
  if (key >= 'A' && key <= 'Z') {
    keyIndex = key - 'A';
  } else if (key >= 'a' && key <= 'z') {
    keyIndex = key - 'a';
  }
  if (keyIndex == -1) {
    // If it's not a letter key, clear the screen   
    MessageFromProcessing_PMD = "MessageFromProcessing_PMD:" + " " + (int(key)-48);
    client.publish(PMD_DTA_TOPIC, MessageFromProcessing_PMD);
    //     println(key);
    println(MessageFromProcessing_PMD);
    background(0, 16, 0); //Set background on sent message.  } else { 
    // It's a letter key, fill a rectangle
    //fill(millis() % 255,64,64);
    //float x = map(keyIndex, 0, 25, 0, width - rectWidth);
    //rect(x, 0, rectWidth, height);
  }
}
