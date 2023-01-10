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
//===================SENSOR====================

char ssid[] = "FAISAL_NET";
char password[] = "classicmedicos";

//Your Domain name with URL path or IP address with path
String serverName = "http://192.168.1.103:5000/distance";
String Station_Id = "3";

void setup() {
  //===================SENSOR====================
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  //===================SENSOR====================
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
    if(WiFi.status()== WL_CONNECTED){

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
    //===================SENSOR====================
    
      HTTPClient http;
      WiFiClient client;
      
      
      
      String serverPath = serverName + "?distance="+String(distance)+"&station="+Station_Id;
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
      }
      http.end();
    }else {
      Serial.println("WiFi Disconnected");
      Serial.println(distance);
    }
delay(5000);
}
