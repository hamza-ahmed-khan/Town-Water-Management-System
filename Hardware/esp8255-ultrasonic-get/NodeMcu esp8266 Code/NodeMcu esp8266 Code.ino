#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ArduinoJson.h>
#include <ESP8266HTTPClient.h>

const char* ssid = "FAISAL_NET";
const char* password = "classicmedicos";
String isFlowing ;
const char* waterFlowing;
int relaypin = D8;

//===================SENSOR====================
// defines pins numbers
const int trigPin = 12;  //D5
const int echoPin = 14;  //D6
// defines variables
long duration;
int distance;

//FLOW SENSOR
int sensorPin = D2;
volatile long pulse;
unsigned long lastTime;

float volume;

//SOLENOIDE
char isFlowing = false;

//Your Domain name with URL path or IP address with path
String serverName = "http://hamza19b.pythonanywhere.com/distance";
String Station_Id = "3";

//VALVE STATUS DOMAIN
String ValveServer = "http://hamza19b.pythonanywhere.com/ValveStatus";


void setup() {
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(relaypin,OUTPUT);

  // Connect to Wi-Fi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  
  //===================SENSOR====================
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  //===================SENSOR====================
  //=======FLOW SENSOR=======
  pinMode(sensorPin, INPUT);
  attachInterrupt(digitalPinToInterrupt(sensorPin), increase, RISING);
  //========SOLENOID==============
  pinMode(relaypin,OUTPUT);
  //============//
  
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  if (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println(".NOT connected");
  }
  else{
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
  }
}

void loop() {

  if (WiFi.status() == WL_CONNECTED) {
    WiFiClient client;

    // Connect to Flask server
    if (client.connect("http://hamza19b.pythonanywhere.com", 5000)) {

      // Send a GET request to Flask server
      client.println("GET http://hamza19b.pythonanywhere.com/espvalve");
      client.println(" HTTP/1.1");
      client.println("Host: your_flask_server_IP_address");
      client.println("Connection: close");
      client.println();

      // Read the response from Flask server
      while (client.connected()) {
        String responseBody = client.readString();
        // Parse the response body as JSON and extract the value of "water flowing"
        DynamicJsonDocument doc(1024);
        deserializeJson(doc, responseBody);
        isFlowing = doc["water flowing"].as<const char*>();
        Serial.println("RESPONSE: "+ isFlowing);
      }
      if (isFlowing == "true") {
        Serial.println("RELAY IS GOING LOW");
        digitalWrite(relaypin, LOW);
      } else {
        Serial.println("RELAY IS GOING HIGH");
        digitalWrite(relaypin, HIGH);
      }
    }
    else {
      Serial.println("Connection failed");
    }
  }

 
