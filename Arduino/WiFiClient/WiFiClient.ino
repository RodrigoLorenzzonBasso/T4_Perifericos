/*
 *  This sketch sends data via HTTP GET requests to data.sparkfun.com service.
 *
 *  You need to get streamId and privateKey at data.sparkfun.com and paste them
 *  below. Or just customize this script to talk to other HTTP servers.
 *
 */

#include <ESP8266WiFi.h>

const char* ssid     = "P30_IOT";
const char* password = "pucrs@2019";

const char* host = "192.168.30.128";

void setup() {
  Serial.begin(115200);
  delay(10);

  // We start by connecting to a WiFi network
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  /* Explicitly set the ESP8266 to be a WiFi-client, otherwise, it by default,
     would try to act as both a client and an access-point and could cause
     network-issues with your other WiFi-devices on your WiFi-network. */
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }

  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  
  delay(500);

  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  const int httpPort = 32000;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }
  
 client.print("Teste\n oi koefender \n");
  
   
  String line = client.readStringUntil('.');
  Serial.print(line);
 
  
  
}
