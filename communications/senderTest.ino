

#include <SoftwareSerial.h>
#include <ArduinoJson.h>


SoftwareSerial HC12(10, 11); // HC-12 TX Pin, HC-12 RX Pin

void setup() {
  Serial.begin(9600);     //Initialize serial communication
  HC12.begin(9600);     //Initialize HC12 Transmiter
  
  
}

void loop(){   
   
  HC12.println("hola sergio!!!");   //
  Serial.println("{\"humidity\":66,\"temperature\":26.5,\"floorhumidity0\":351,\"floorhumidity1\":352,\"floorhumidity2\":343,\"fHPercentages0\":81,\"fHPercentages1\":82,\"fHPercentages2\":88}");
  HC12.println("{\"humidity\":66,\"temperature\":26.5,\"floorhumidity0\":351,\"floorhumidity1\":352,\"floorhumidity2\":343,\"fHPercentages0\":81,\"fHPercentages1\":82,\"fHPercentages2\":88}");
 
  delay(2000);  
  
  
}