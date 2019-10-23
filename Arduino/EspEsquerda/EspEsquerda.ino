#include <LiquidCrystal.h>
#include <DHTesp.h>

// pino 15 ta no DHT 11

//LiquidCrystal(rs, enable, d4, d5, d6, d7)
LiquidCrystal lcd(12, 14, 2, 4, 5, 16);

DHTesp dht;

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

void setup()
{
  Serial.begin(9600);
  dht.setup(15, DHTesp::DHT11); // Connect DHT sensor to GPIO 15

  lcd.print("hello, world!");
}

void loop()
{
  delay(dht.getMinimumSamplingPeriod());

  float humidity = dht.getHumidity();
  float temperature = dht.getTemperature();

 //print_dht();
  
  delay(2000);
}
