#include <LiquidCrystal.h>
#include <DHTesp.h>

#include <ESP8266WiFi.h>

// pino 10 reservado para motor

// functions headers
void print_dht(float,float);

// LCD setup
              //rs, enable, d4, d5, d6, d7
LiquidCrystal lcd(0, 2, 14, 12, 13, 15);

// dht 11 setup
DHTesp dht;
int dhtPin = 16;

// wifi setup
const char* ssid = "P30_IOT";
const char* password = "pucrs@2019";
int port = 32000;
WiFiServer server(port);

void setup()
{
  Serial.begin(115200);
  dht.setup(dhtPin, DHTesp::DHT11); // Connect DHT sensor to GPIO 16

  WiFi.begin(ssid, password);
  server.begin();
  
  lcd.print("hello, world!");
}

void loop()
{
  delay(dht.getMinimumSamplingPeriod());

  float humidity = dht.getHumidity();
  float temperature = dht.getTemperature();

  print_dht(humidity, temperature);

  lcd.clear();
  char teste[30];
  sprintf(teste,"T %2.1fC H %2.1f%%",temperature,humidity);
  lcd.print(teste);

  ////////////////// Wifi //////////////////////
  // Check if module is still connected to WiFi.
  if (WiFi.status() != WL_CONNECTED) {
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
    }
  }

  WiFiClient client = server.available();

  if (client) {
    Serial.println("Client connected.");
    client.print("Hi, Client");
   
    while (client.connected()) {
      if (client.available()) {
        
       String line = client.readStringUntil('.');
       Serial.println(line);
      }
    }
    Serial.println("Client disconnected.");
    client.stop();
  }
  ////////////////// Wifi //////////////////////

  
  delay(2000);
}

void print_dht(float humidity, float temperature)
{
  Serial.print(dht.getStatusString());
  Serial.print("\n");
  Serial.print("Umidade: ");
  Serial.print(humidity, 1);
  Serial.print("%\nTemperatura: ");
  Serial.print(temperature, 1);
  Serial.print("\n");
}
