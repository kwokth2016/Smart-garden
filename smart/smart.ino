#include <dht.h>

dht DHT;

#define DHT11_PIN 7
#define light A1
#define water A0
#define water2 A2
#define soil A3
#define buzzer 9
void setup(){
  Serial.begin(9600);
  pinMode(buzzer, OUTPUT);
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
  Serial.print(",");
  Serial.print("\"Soil\": ");
  Serial.print(analogRead(soil));
  Serial.print(",");
  Serial.print("\"water2\": ");
  Serial.print(analogRead(water2));
  Serial.println("}");
}

void alert(){
  int waterlevel = analogRead(water);
  if(waterlevel<50)
  {
   tone(buzzer, 500); // Send 1KHz sound signal...
   delay(1000);        // ...for 1 sec
   noTone(buzzer);     // Stop sound...
   delay(1000);        // ...for 1sec
  }
  int waterlevel2 = analogRead(water2);
  if(waterlevel2<50)
  {
   tone(buzzer, 500); // Send 1KHz sound signal...
   delay(1000);        // ...for 1 sec
   noTone(buzzer);     // Stop sound...
   delay(1000);        // ...for 1sec
  }
  int temp = DHT.temperature;
  if(temp<15)
  {
   tone(buzzer, 1000); // Send 1KHz sound signal...
   delay(1000);        // ...for 1 sec
   noTone(buzzer);     // Stop sound...
   delay(1000);        // ...for 1sec
  }
  if(temp>35)
  {
   tone(buzzer, 2000); // Send 1KHz sound signal...
   delay(1000);        // ...for 1 sec
   noTone(buzzer);     // Stop sound...
   delay(1000);        // ...for 1sec
  }
}

void loop()
{
  int chk = DHT.read11(DHT11_PIN);
  prepareJson();
  alert();
  delay(1000);
}
