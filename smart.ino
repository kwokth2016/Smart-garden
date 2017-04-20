#include <dht.h>

dht DHT;

#define DHT11_PIN 7
#define light A1
#define water A0


void setup(){
  Serial.begin(9600);
//  pinMode(light, INPUT);
}

void prepareJson(){
  Serial.print("{");
  Serial.print("\"water\": ");
  Serial.print(analogRead(water));
  Serial.print(",");
  Serial.print("\"light\": ");
  Serial.print(analogRead(light));
  Serial.print(",");
  Serial.print("\"temperature\": ");
  Serial.print(DHT.temperature);
  Serial.print(",");
  Serial.print("\"humidity\": ");
  Serial.print(DHT.humidity);
  Serial.println("}");
}

void loop()
{
  int chk = DHT.read11(DHT11_PIN);
  prepareJson();
  delay(1000);
}
