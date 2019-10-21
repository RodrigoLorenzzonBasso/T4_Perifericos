
#include <ESP8266WiFi.h>
const char* ssid = "embarcados";
const char* password = "embarcados";
const int ledPin = 2;
WiFiServer server(32000);


void printWiFiStatus();
  
void setup(void) {
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  // Configure GPIO2 as OUTPUT.
  pinMode(ledPin, OUTPUT);
  
  // Start TCP server.
  server.begin();
}

void loop(void) {
  // Check if module is still connected to WiFi.
  uint8_t  command[30];
  if (WiFi.status() != WL_CONNECTED) {
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
    }
    // Print the new IP to Serial.
    printWiFiStatus();
  }

  WiFiClient client = server.available();

  if (client) {
    Serial.println("Client connected.");
   
    while (client.connected()) {
      if (client.available()) {
        //char command = client.read();
        
       String line = client.readStringUntil('.');
       Serial.println(line);
       
       /* if (command == 'H') {
          digitalWrite(ledPin, HIGH);
          Serial.println("LED is now on.");
        }
        else if (command == 'L') {
          digitalWrite(ledPin, LOW);
          Serial.println("LED is now off.");
        }

         Serial.println(command);*/
      }
    }
    Serial.println("Client disconnected.");
    client.stop();
  }
 
   delay(500);
}

void printWiFiStatus() {
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}
