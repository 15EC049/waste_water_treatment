int inByte = 0;
const int valv1 = 3;//Valve pin
const int valv2 = 4;//Valve pin
const int valv3 = 5;//Valve pin
void setup() {
  // put your setup code here, to run once:
    Serial.begin(9600);
      pinMode(13,OUTPUT);
  pinMode(valv1, OUTPUT);
  pinMode(valv2, OUTPUT);
  pinMode(valv3, OUTPUT);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }


}

void loop() {
  // put your main code here, to run repeatedly:
    if (Serial.available() > 0) 
    {
      inByte = Serial.readString().toInt();
      //Serial.println(inByte,DEC);
      if(inByte == 1)
      {
        valv1_on();
      }
      else if(inByte == 2)
      {
       valv2_on();
      }
      else if(inByte == 3)
      {
        valv3_on();
      }
      else
      {
        Serial.println("at Else");
      }
    }

}
void valv1_on()
{
  digitalWrite(valv1, HIGH);
  digitalWrite(valv2, LOW);
  digitalWrite(valv3, LOW);
  Serial.println("Fresh Water. Valve 1 Open....");
}

void valv2_on()
{
  digitalWrite(valv1, LOW);
  digitalWrite(valv2, HIGH);
  digitalWrite(valv3, LOW);
  Serial.println("Acidic Water. Valve 2 Open....");
}
void valv3_on()
{
  digitalWrite(valv1, LOW);
  digitalWrite(valv2, LOW);
  digitalWrite(valv3, HIGH);
  Serial.println("Waste Water. Valve 3 Open....");  
}
