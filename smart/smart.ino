#include <dht.h>

dht DHT;

#define DHT11_PIN 7
#define light A1
#define water A0
#define water2 A2
#define soil A3


#define pump1 4
#define pump2 5
#define ledstrip 8
#define buzzer 9
#define atomizer 10
#define fan1 11
#define fan2 12


void setup(){
  Serial.begin(9600);
  pinMode(buzzer, OUTPUT);
  pinMode(ledstrip,OUTPUT);
  pinMode(atomizer,OUTPUT);
  pinMode(fan1,OUTPUT);
  pinMode(fan2,OUTPUT);
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
   tone(buzzer, 500); // Send 0.5KHz sound signal...
   delay(1000);        // ...for 1 sec
   noTone(buzzer);     // Stop sound...
//   delay(1000);        // ...for 1sec
  }
  int temp = DHT.temperature;
  if(temp<15)
  {
   tone(buzzer, 1000); // Send 1KHz sound signal...
   delay(1000);        // ...for 1 sec
   noTone(buzzer);     // Stop sound...
//   delay(1000);        // ...for 1sec
  }
  if(temp>35)
  {
   tone(buzzer, 2000); // Send 2KHz sound signal...
   delay(1000);        // ...for 1 sec
   noTone(buzzer);     // Stop sound...
//   delay(1000);        // ...for 1sec
  }
}

void response(){
  int lightlevel = analogRead(light);
  int temperaturelevel = DHT.temperature;
  //led strip
  if(lightlevel>400)
    analogWrite(ledstrip,255);
  else
    analogWrite(ledstrip,0);
  //fan and exhaust fan  
  if(temperaturelevel > 35){
    digitalWrite(fan1,HIGH);
    analogWrite(fan2,255);
  }
  else{
    digitalWrite(fan1,HIGH);
    analogWrite(fan2,0);
  }
  
}
void loop()
{
  int chk = DHT.read11(DHT11_PIN);
  prepareJson();
  alert();
  response();
  delay(1000);
}
