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
int port = 31600;
WiFiServer server(port);

void setup()
{
  Serial.begin(115200);
  dht.setup(dhtPin, DHTesp::DHT11); // Connect DHT sensor to GPIO 16

  WiFi.begin(ssid, password);
  server.begin();
  lcd.begin(16, 2);
}

void loop()
{
  delay(dht.getMinimumSamplingPeriod());

  float humidity = dht.getHumidity();
  float temperature = dht.getTemperature();

  print_dht(humidity, temperature);

  char str[30];
  sprintf(str,"T %02.1f H %02.1f\n;",temperature,humidity);

  char temp[30];
  sprintf(temp,"Temperatura %2.1fC",temperature);

  char humi[30];
  sprintf(humi,"Umidade %2.1f%%",humidity);

  lcd.clear();
  
  lcd.setCursor(0,0);
  lcd.print(temp);

  lcd.setCursor(0,1);
  lcd.print(humi);

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

    client.print(str);
   
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
  Serial.println(WiFi.localIP());
}
