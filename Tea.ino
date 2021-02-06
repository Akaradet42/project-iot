#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h> // 

#include "DHT.h"

#define DHTPIN 12  
#define DHTTYPE DHT11  
DHT dht(DHTPIN, DHTTYPE);
//char auth[] = "iGl1Y0562eEIQms2FLyA-OTyb4kjG2xI"; //รหัสBLYNK ที่ส่งเข้าเมล  OX_6pFNJrkKYW55rb4JZVxdUQfDveMuq
char auth[] = "OX_6pFNJrkKYW55rb4JZVxdUQfDveMuq";
// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "AKD";
char pass[] = "47760028";

const int pingPin = 27;
int inPin = 26 ;

void setup()
{
  // Debug console
  Serial.begin(9600);
  pinMode(5,OUTPUT);
  pinMode(18,OUTPUT);
  Blynk.begin(auth, ssid, pass);
  // You can also specify server:
  //Blynk.begin(auth, ssid, pass, "blynk-cloud.com", 80);
  //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8080);
  Serial.println();
  Serial.println("Status\tHumidity (%)\tTemperature (C)\t(F)");
  dht.begin();
}

void loop()
{
  float humidity = dht.readHumidity(); // ดึงค่าความชื้น
  float temperature = dht.readTemperature(); // ดึงค่าอุณหภูมิ
  long duration, cm;
  pinMode(pingPin, OUTPUT);
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPin, LOW);
  pinMode(inPin, INPUT);
  duration = pulseIn(inPin, HIGH);
  cm = microsecondsToCentimeters(duration);
  Blynk.run();
  delay(100);
  Blynk.virtualWrite(5,HIGH);
  Blynk.virtualWrite(18,HIGH);
  Blynk.virtualWrite(V0, temperature);
  Blynk.virtualWrite(V1, humidity);
  Blynk.virtualWrite(V2, cm);

}

long microsecondsToCentimeters(long microseconds)
{
// ความเร็วเสียงในอากาศประมาณ 340 เมตร/วินาที หรือ 29 ไมโครวินาที/เซนติเมตร
// ระยะทางที่ส่งเสียงออกไปจนเสียงสะท้อนกลับมาสามารถใช้หาระยะทางของวัตถุได้
// เวลาที่ใช้คือ ระยะทางไปกลับ ดังนั้นระยะทางคือ ครึ่งหนึ่งของที่วัดได้
return microseconds / 29 / 2;
}
