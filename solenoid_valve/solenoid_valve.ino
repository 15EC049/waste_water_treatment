const int RelayPin = 3;                   

void setup() {
   Serial.begin(9600);   
  pinMode(RelayPin, OUTPUT);
} 
void loop() {
  if(Serial.read()=='o'){

     digitalWrite(RelayPin, HIGH);   //Turn on  
     Serial.println("open");
     delay(100);
  }
   if(Serial.read()=='f'){

     digitalWrite(RelayPin, LOW);   //Turn off   
     Serial.println("close");
     delay(100);
  }
}
