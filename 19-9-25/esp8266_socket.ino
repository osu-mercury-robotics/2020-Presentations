#include "ESP8266WiFi.h"
 
const char* ssid = "MERCURY";
const char* password =  "";
 
WiFiServer wifiServer(80);
 
void setup() {
 
  Serial.begin(115200);
 
  delay(1000);
 
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting..");
  }
  pinMode(0, OUTPUT);
  Serial.print("Connected to WiFi. IP:");
  Serial.println(WiFi.localIP());
 
  wifiServer.begin();
}
 
void loop() {
 
  WiFiClient client = wifiServer.available();
  
  if (client) {
 
    while (client.connected()) {
 
      while (client.available()>0) {
        char c = client.read();
        Serial.write(c);

        if(c=='1')
        {
          Serial.write(" on");
          digitalWrite(0, LOW);
        }
        if(c=='0')
        {
          Serial.write(" off");
          digitalWrite(0, HIGH);
        }
      }
 
      delay(10);
    }
 
    client.stop();
    Serial.println("Client disconnected");
 
  }
}
