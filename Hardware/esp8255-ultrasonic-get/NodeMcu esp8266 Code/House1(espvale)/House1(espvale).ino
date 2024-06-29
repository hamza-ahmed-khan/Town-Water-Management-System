#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ArduinoJson.h>
#include <ESP8266HTTPClient.h>

const char* ssid = "iPhone 7plus";
const char* password = "hamzaahmed";
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


//Your Domain name with URL path or IP address with path
String serverName = "http://172.20.10.2:5000/distance";
String Station_Id = "0";

//VALVE STATUS DOMAIN
String ValveServer = "http://172.20.10.2:5000/ValveStatus";

// Function declarations
ICACHE_RAM_ATTR void increase() {
  pulse++;
}

void setup() {
  Serial.begin(115200);
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
  WiFi.setAutoReconnect(true);
  WiFi.persistent(true);
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
     //===================SENSOR==================== 
    // Clears the trigPin
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    
    // Sets the trigPin on HIGH state for 10 micro seconds
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    
    // Reads the echoPin, returns the sound wave travel time in microseconds
    duration = pulseIn(echoPin, HIGH);
    
    // Calculating the distance
    distance= duration*0.034/2;
    Serial.println(distance);

    volume = 2.663 * pulse / 1000 * 30;
      if (millis() - lastTime > 2000) {
        pulse = 0;
        lastTime = millis();
      }
      Serial.print(volume);
      Serial.println(" L/m");

    // Connect to Flask server
    if (client.connect("172.20.10.2", 5000)) {

      // Send a GET request to Flask server
      client.println("GET http://172.20.10.2:5000/espvalve");
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
      if (isFlowing == "false" || distance<= 2.5){
        Serial.println("RELAY IS GOING HIGH");
        digitalWrite(relaypin, HIGH);
      } else {
        Serial.println("RELAY IS GOING LOW");
        digitalWrite(relaypin, LOW);
      }
    }
    else {
      Serial.println("Connection failed");
    }
    //===================SENSOR====================
    
      HTTPClient http;
      
      
      
      String serverPath = serverName + "?distance="+String(distance)+"&flowrate="+String(volume)+"&station="+Station_Id;
      Serial.println(serverPath);
      // Your Domain name with URL path or IP address with path
      http.begin(client, serverPath.c_str());

      
      
      // Send HTTP GET request
      int httpResponseCode = http.GET();
      
      if (httpResponseCode>0) {
        Serial.print("HTTP Response code: ");
        Serial.println(httpResponseCode);
        String payload = http.getString();
        Serial.println(payload);
        }else{
        Serial.print("Error code: ");
        Serial.println(httpResponseCode);
        Serial.println(distance);
        Serial.println(volume);
      }
      http.end();
      Serial.println(distance);
      Serial.println(volume);
    
delay(5000);
  }
}

 
