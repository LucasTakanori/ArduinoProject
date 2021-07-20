void setup() {
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop(){
  if(Serial.available()>0){
    String input = Serial.readString();
    if(input == "Hi"){
      digitalWrite(LED_BUILTIN,HIGH);
      delay(250);
      digitalWrite(LED_BUILTIN,LOW);
    }
  }
}
//https://www.youtube.com/watch?v=0zOTvB0T5fY&ab_channel=DIYTECHBROS 
