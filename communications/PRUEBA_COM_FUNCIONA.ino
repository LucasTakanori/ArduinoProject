

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

float* getHumidityAndTemp(){
  float h = dht.readHumidity();   //read humidity
  float t = dht.readTemperature();   //read temp Cº

  if (isnan(h) || isnan(t)) {
    Serial.println("Sensor error DHT11");
    return;
  }

  //Serial.println(h);   
  //Serial.println(t);

  float* data = new float[2];
  data[0] = h;
  data[1] = t;

  return data;
  
}


int* getMoistFloorValues(){
  int* data = new int[3];
  int soilMoistureValue0 = analogRead(A0);
  int soilMoistureValue1 = analogRead(A1);
  int soilMoistureValue2 = analogRead(A2);

  if (isnan(soilMoistureValue0) || isnan(soilMoistureValue1)|| isnan(soilMoistureValue2)) {
    Serial.println("Sensor error capacitive sensor");
    return;
  }

  data[0] = soilMoistureValue0;
  data[1] = soilMoistureValue1;
  data[2] = soilMoistureValue2;

  return data;
}

int* calcMoistFloorPercentage(int* data){
  int* response = new int[3];

  response[0] = map(data[0], AirValue0, WaterValue0, 0, 100);
  response[1] = map(data[1], AirValue1, WaterValue1, 0, 100);
  response[2] = map(data[2], AirValue2, WaterValue2, 0, 100);

  //Serial.print(response[0]);
  //Serial.println("%");
  //Serial.print(response[1]);
  //Serial.println("%");
  //Serial.print(response[2]);
  //Serial.println("%");

  return response;
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
  StaticJsonDocument<200> doc;  //creating json document
  float *ht = getHumidityAndTemp();
  doc["humidity"] = ht[0];
  doc["temperature"] = ht[1];

  int* floorHumidity = getMoistFloorValues();

  // JsonArray fh_doc = doc.createNestedArray("floorhumidity");
  // fh_doc.add(floorHumidity[0]);
  // fh_doc.add(floorHumidity[1]);
  // fh_doc.add(floorHumidity[2]);

  doc["floorhumidity0"] = floorHumidity[0];
  doc["floorhumidity1"] = floorHumidity[1];
  doc["floorhumidity2"] = floorHumidity[2];
  int* fHPercentages = calcMoistFloorPercentage(floorHumidity);
  doc["fHPercentages0"] = fHPercentages[0];
  doc["fHPercentages1"] = fHPercentages[1];
  doc["fHPercentages2"] = fHPercentages[2];
  //Serial.println(doc["humidity"]);

  String test = doc.as<String>(); //Json to String
  Serial.println(test);

  // Send string and and then the receiver has to it back to a JSON Object

  // "receiver test"
  StaticJsonDocument<200> parsed;
  DeserializationError error = deserializeJson(parsed, test);

  // Test if parsing succeeds.
  if (error) {
    Serial.print(F("deserializeJson() failed: "));
    Serial.println(error.f_str());
    return;
  }
  


  //Serial.println("pito");
  //HC12.println(doc.);
  HC12.println(test);
  const float sensor = parsed["humidity"];
  //Serial.println(sensor); 
  //HC12.write(i);
  delay(2000);  
  
  
}