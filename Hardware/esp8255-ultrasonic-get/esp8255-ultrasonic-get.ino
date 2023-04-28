#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>

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
int relaypin = D8;
char isFlowing = false;

//===================SENSOR====================

char ssid[] = "FAISAL_NET";
char password[] = "classicmedicos";

//Your Domain name with URL path or IP address with path
String serverName = "http://172.20.10.3:5000/distance";
String Station_Id = "3";

//VALVE STATUS DOMAIN
String ValveServer = "http://172.20.10.3:5000/ValveStatus";


void setup() {
  //===================SENSOR====================
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  //===================SENSOR====================
  //=======FLOW SENSOR=======
  pinMode(sensorPin, INPUT);
  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(sensorPin), increase, RISING);
  //========SOlenoid==============
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
    //Check WiFi connection status
    if (WiFi.status() == WL_CONNECTED) {
    WiFiClient client;
    // Connect to Flask server
    if (client.connect("192.168.1.112", 5000)) {

      // Send a GET request to Flask server
      client.print("GET http://192.168.1.112:5000/espvalve");

      // Read the response from Flask server
      while (client.connected()) {
        String line = client.readStringUntil('\n');
        Serial.println(line);
        if (line == "\r") {
          Serial.println("Response:");
          String responseBody = client.readString();
          Serial.println(responseBody);
          break;
        }
      }
      while (client.available()) {
        char c = client.read();
 
        isFlowing = c;
        Serial.print(isFlowing);
      }

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
    }
    
      

      Serial.println();
      digitalWrite(LED_BUILTIN, HIGH);
      delay(1000);
      digitalWrite(LED_BUILTIN, LOW);
      delay(1000);
    }
    else {
      Serial.println("Connection failed");
    }
  


    //========Solenoid==============
    if (isFlowing == false) {
      digitalWrite(relaypin, LOW);
    } else {
      digitalWrite(relaypin, HIGH);
    }


    //===================SENSOR====================
    
      HTTPClient http;
      WiFiClient client;
      
      
      
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
    
    
      Serial.println("WiFi Disconnected");
      Serial.println(distance);
      Serial.println(volume);
    
delay(5000);
}
ICACHE_RAM_ATTR void increase() {
  pulse++;
}
