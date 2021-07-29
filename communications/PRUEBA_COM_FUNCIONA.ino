#include <SoftwareSerial.h>

SoftwareSerial HC12(10, 11); // HC-12 TX Pin, HC-12 RX Pin
void setup() {
  Serial.begin(9600);
  HC12.begin(9600);
  
}
void loop(){
  //Serial.println("Hi");
  //while(j<10){
  //while(i<10){
  HC12.println("hola sergio!!!");  
  //HC12.write(i);
  delay(2000);
  //i=i+1;
  //}
  
  
  
}
