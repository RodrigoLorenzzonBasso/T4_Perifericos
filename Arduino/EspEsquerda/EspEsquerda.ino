#include <LiquidCrystal.h>
#include <DHTesp.h>
#include <Servo.h>
#include <ESP8266WiFi.h>

void print_dht(float,float);
void gira_motor();
void gira_motor2();
Servo servo;
int servoPin = 4;
int pos;
              //rs, enable, d4, d5, d6, d7
LiquidCrystal lcd(0, 2, 14, 12, 13, 15);
DHTesp dht;
int dhtPin = 16;

char estado = 0; // 0 fechado 1 aberto

// wifi setup
const char* ssid = "P30_IOT";
const char* password = "pucrs@2019";
int port = 31600;
WiFiServer server(port);

void setup()
{
  Serial.begin(115200);
  dht.setup(dhtPin, DHTesp::DHT11); // Connect DHT sensor to GPIO 16

  Serial.println(WiFi.localIP());

  WiFi.begin(ssid, password);
  server.begin();
  lcd.begin(16, 2);

  servo.attach(servoPin);
}

void loop()
{
  delay(dht.getMinimumSamplingPeriod());

  float humidity = dht.getHumidity();
  float temperature = dht.getTemperature();

  print_dht(humidity, temperature);

  char str[30];
  sprintf(str,"%02.1f %02.1f;",temperature,humidity);

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
        
       String line = client.readStringUntil(';');
       Serial.println(line);

       if(strcmp(line,"Abrir") == 0)
       {
         if(estado == 0)
         {
           gira_motor();
           estado = 1;
         }
          
       }
       else if(strcmp(line,"Fechar") == 0)
       {
         if(estado == 1)
         {
           gira_motor2();
           estado = 0; 
         }
       }
      }
    }
    Serial.println("Client disconnected.");
    client.stop();
  }
  ////////////////// Wifi //////////////////////
}

void gira_motor()
{
  for(pos = 0; pos < 180; pos++){ //PARA "pos" IGUAL A 0, ENQUANTO "pos" MENOR QUE 180, INCREMENTA "pos"
    servo.write(pos); //ESCREVE O VALOR DA POSIÇÃO QUE O SERVO DEVE GIRAR
    delay(3); //INTERVALO DE 15 MILISSEGUNDOS
  }    
}

void gira_motor2()
{
  for(pos = 180; pos < 0; pos--){ //PARA "pos" IGUAL A 0, ENQUANTO "pos" MENOR QUE 180, INCREMENTA "pos"
    servo.write(pos); //ESCREVE O VALOR DA POSIÇÃO QUE O SERVO DEVE GIRAR
    delay(3); //INTERVALO DE 15 MILISSEGUNDOS
  }    
}
