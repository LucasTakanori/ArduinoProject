#include <SoftwareSerial.h>
#include <ArduinoJson.h>
#include "DHT.h"
#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

//calibration constants
const int AirValue0 = 590;   //you need to replace this value with Value_1
const int WaterValue0 = 298;  //you need to replace this value with Value_2
const int AirValue1 = 591;   //you need to replace this value with Value_1
const int WaterValue1 = 300;  //you need to replace this value with Value_2
const int AirValue2 = 608;   //you need to replace this value with Value_1
const int WaterValue2 = 308;  //you need to replace this value with Value_2
int soilMoistureValue0 = 0;
int soilmoisturepercent0 =0;
int soilMoistureValue1 = 0;
int soilmoisturepercent1 =0;
int soilMoistureValue2 = 0;
int soilmoisturepercent2 =0;

String readHumidityAndTemp(){
   float h = dht.readHumidity();   //read humidity
   float t = dht.readTemperature();   //read temp Cº
   
   Serial.println(h);   //
   Serial.println(t);   //

   String H= String(h);
   String T= String(t);
   String str = String(H +','+ T);
   if (isnan(h) || isnan(t)) {
    Serial.println("Sensor error DHT11");
    return;
  }

  return str;
  
}


String readMoistFloor(){

  soilMoistureValue0 = analogRead(A0);
  soilMoistureValue1 = analogRead(A1);
  soilMoistureValue2 = analogRead(A2);
  //put Sensor insert into soil

  String M0= String(soilMoistureValue0);
  String M1= String(soilMoistureValue1);
  String M2= String(soilMoistureValue2);
  String str = String(M0 +','+M1+','+M2+',');
  return str;
  Serial.println(soilMoistureValue0);
  Serial.println(soilMoistureValue1);
  Serial.println(soilMoistureValue2);
  soilmoisturepercent0 = map(soilMoistureValue0, AirValue0, WaterValue0, 0, 100);
  soilmoisturepercent1 = map(soilMoistureValue1, AirValue1, WaterValue1, 0, 100);
  soilmoisturepercent2 = map(soilMoistureValue2, AirValue2, WaterValue2, 0, 100);
  str = String(str + soilmoisturepercent0 + ',' + soilmoisturepercent1 +',' + soilmoisturepercent2 );
  Serial.print(soilmoisturepercent0);
  Serial.println("%");
  Serial.print(soilmoisturepercent1);
  Serial.println("%");
  Serial.print(soilmoisturepercent2);
  Serial.println("%");

  return str;

}

SoftwareSerial HC12(10, 11); // HC-12 TX Pin, HC-12 RX Pin

void setup() {
  Serial.begin(9600);     //Initialize serial communication
  HC12.begin(9600);     //Initialize HC12 Transmiter
  dht.begin();  //initialize DHT Sensor
  
}

void loop(){   
   
  HC12.println("hola sergio!!!");   //
  //HC12.println(readHumidityAndTemp());
  //HC12.println(readMoistFloor());
  //readMoistFloor();
  StaticJsonDocument<200> doc;
  doc["sensor"] = "gps";
  doc["time"] = 1351824120;
  
  HC12.println(doc);
  //HC12.write(i);
  delay(2000);  
  
  
}