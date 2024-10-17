// File: MQTT_PMD_DAT_TOPIC 
// Author: Forrest Lee Erickson
// Date: 20241006

// Pseude Medical Device in Processing. 
// This example sketch connects to the public shiftr.io instance and sends a message on every keystroke.
// After starting the sketch you can find the client here: https://www.shiftr.io/try.
//
// Note: If you're running the sketch via the Android Mode you need to set the INTERNET permission
// in Android > Sketch Permissions.
//
// by Joël Gähwiler
// https://github.com/256dpi/processing-mqtt

// Set the topic for the Pseude Medical Device in Processing.
String PMD_DTA_TOPIC = "PROCESSING_PMD_USA1_DTA_TOPIC_USA_MARYVILLE";
//String PMD_DTA_TOPIC = "PROCESSING_PMD_DTA_TOPIC_LB";


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
    client.subscribe("PMD_USA5");

    //    client.subscribe("KRAKE_DTA_TOPIC");
  }

  void messageReceived(String topic, byte[] payload) {
    println("new message: " + topic + " - " + new String(payload));
  }

  void connectionLost() {
    println("connection lost");
  }
}

Adapter adapter;

void setup() {
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
    background(0);
  } else { 
    // It's a letter key, fill a rectangle
    //fill(millis() % 255,64,64);
    //float x = map(keyIndex, 0, 25, 0, width - rectWidth);
    //rect(x, 0, rectWidth, height);
  }
}
