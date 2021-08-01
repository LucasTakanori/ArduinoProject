#include <SoftwareSerial.h>
#include <ArduinoJson.h>
#include <SoftwareSerial.h>

const char c = 125;
char *str;
const byte HC12RxdPin = 11;                  // Recieve Pin on HC12
const byte HC12TxdPin = 10;                  // Transmit Pin on HC12
String current_packet = String("");

SoftwareSerial HC12(HC12TxdPin, HC12RxdPin); // Create Software Serial Port

void setup() {
  Serial.begin(9600);                       // Open serial port to computer
  HC12.begin(9600);                         // Open serial port to HC12
  if (HC12.isListening()) {
    Serial.println("OK");
  } else {
    Serial.println("NOK");
  }
}

void loop() {
  if(HC12.available()){   
    
    StaticJsonDocument<250> doc;
    DeserializationError error = deserializeJson(doc, HC12);
    if (error) {
      //Serial.println(F("NO DATA"));
      //Serial.println(error.c_str());
      return;
    }else{
      Serial.println("Recieving data:");
      serializeJsonPretty(doc, Serial);
      Serial.println("");
      String test = doc.as<String>(); //Json to String
      Serial.println(test);
    } 
  }
  
}
