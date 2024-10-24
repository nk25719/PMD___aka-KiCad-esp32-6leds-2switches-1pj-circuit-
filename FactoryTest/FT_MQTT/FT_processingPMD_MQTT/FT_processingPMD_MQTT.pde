// File: FT_processingPMD_MQTT 
// Author: Forrest Lee Erickson
// Date: 20241006
// Date: 20241016 Background change color on send and receive MQTT. Subscribe to 20240421_USA4.
// Date: 20241017 Set title on window.
// Date: 20241024 Publish to a Krake model and serial number. Works with "FT_PMD_MQTT ""V0.7 "

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
 #define DEVICE_UNDER_TEST "PMD SN: USA1"  //A PMD model  and Serial Number
 #define LICENSE "GNU Affero General Public License, version 3 "
 #define ORIGIN "USA"
 */

String PROG_NAME = "FT_processingPMD_MQTT";
String VERSION = "V0.5 ";
// Set the topic for the Pseude Medical Device in Processing.
String PMD_DTA_TOPIC = "PROCESSING_PMD_USA1_DTA_TOPIC_USA_MARYVILLE";
//String PMD_DTA_TOPIC = "PROCESSING_PMD_DTA_TOPIC_LB";

String KRAKE_DTA_TOPIC = "Krake_20240421_USA4_Data"; //Publish to in GPAD API form


String thePayload = "";

import mqtt.*;

MQTTClient client;
String MessageFromProcessing_PMD = "";

class Adapter implements MQTTListener {
  void clientConnected() {
    println("client connected");

    client.subscribe("/mello");
    client.subscribe("PMD_LB1");
    client.subscribe("PMD_LB2");
    client.subscribe("PMD_LB3");
    client.subscribe("PMD_LB4");
    client.subscribe("PMD_LB5");
    client.subscribe("20240421_LEB1");

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
    MessageFromProcessing_PMD = "a3MessageFromProcessing_PMD:UpperCase";
    client.publish(KRAKE_DTA_TOPIC, MessageFromProcessing_PMD);
  } else if (key >= 'a' && key <= 'z') {
    keyIndex = key - 'a';
    MessageFromProcessing_PMD = "a5MessageFromProcessing_PMD:LowerCase";
    client.publish(KRAKE_DTA_TOPIC, MessageFromProcessing_PMD);
  } else if (key >= '0' && key <= '9') {
    keyIndex = key - '0';
    MessageFromProcessing_PMD = "MessageFromProcessing_PMD:" + " " + (int(key)-48);
    client.publish(PMD_DTA_TOPIC, MessageFromProcessing_PMD);
  }
  background(0, 16, 0); //Set background on sent message.  } else { 
  
}
