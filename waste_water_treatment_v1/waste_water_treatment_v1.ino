#define phPin A0  //Read From PH Sesnor
#define turbidityPin A1
#define Offset 0.00  //PH deviation compensate
#define LED 13
#define samplingInterval 20
#define printInterval 800
#define ArrayLenth  40    //times of collection
int pHArray[ArrayLenth]; //Store the average value of the sensor feedback
int pHArrayIndex=0;
int turbval=0;
static float pHValue,phvoltage,turbvoltage;//PH Value and Voltage Level
const int valv1 = 3;//Valve pin
const int valv2 = 4;//Valve pin
const int valv3 = 5;//Valve pin
float turb_thresh=3;
void setup() 
{
  pinMode(LED,OUTPUT);
  pinMode(valv1, OUTPUT);
  pinMode(valv2, OUTPUT);
  pinMode(valv3, OUTPUT);
  Serial.begin(9600);
  Serial.println("==== Waste Water Treatment ====");    //Test the serial monitor
}

void loop() 
{
  static unsigned long samplingTime = millis();
  static unsigned long printTime = millis();
  if(millis()-samplingTime > samplingInterval)
  {
      pHArray[pHArrayIndex++]=analogRead(phPin);
      turbval=analogRead(turbidityPin);
      if(pHArrayIndex==ArrayLenth)pHArrayIndex=0;
      phvoltage = avergearray(pHArray, ArrayLenth)*5.0/1024;
      turbvoltage=turbval* (5.0 / 1024.0);
      pHValue = 3.5*phvoltage+Offset;
      samplingTime=millis();
      Serial.print("Turbidity: ");
      Serial.print(turbvoltage);
      Serial.print("  PH Value: ");
      Serial.println(pHValue);
  }
if(pHValue>=6.5 & pHValue<7.5 & turbvoltage<turb_thresh)
{
  digitalWrite(valv1, HIGH);
  digitalWrite(valv2, LOW);
  digitalWrite(valv3, LOW);
  Serial.println("Fresh Water. Valve 1 Open....");
}
else if(pHValue>=0 & pHValue<6.5)
{
  digitalWrite(valv1, LOW);
  digitalWrite(valv2, HIGH);
  digitalWrite(valv3, LOW);
  Serial.println("Acidic Water. Valve 2 Open....");
}
else
{
  digitalWrite(valv1, LOW);
  digitalWrite(valv2, LOW);
  digitalWrite(valv3, HIGH);
  Serial.println("Waste Water. Valve 3 Open....");
}
  
/*  if(millis() - printTime > printInterval)   //Every 800 milliseconds, print a numerical, convert the state of the LED indicator
  {
        Serial.print("Voltage:");
        Serial.print(voltage,2);
        Serial.print("    pH value: ");
        Serial.println(pHValue,2);
        digitalWrite(LED,digitalRead(LED)^1);
        printTime=millis();
  }
*/
}
double avergearray(int* arr, int number){
  int i;
  int max,min;
  double avg;
  long amount=0;
  if(number<=0){
    Serial.println("Error number for the array to avraging!/n");
    return 0;
  }
  if(number<5){   //less than 5, calculated directly statistics
    for(i=0;i<number;i++){
      amount+=arr[i];
    }
    avg = amount/number;
    return avg;
  }else{
    if(arr[0]<arr[1]){
      min = arr[0];max=arr[1];
    }
    else{
      min=arr[1];max=arr[0];
    }
    for(i=2;i<number;i++){
      if(arr[i]<min){
        amount+=min;        //arr<min
        min=arr[i];
      }else {
        if(arr[i]>max){
          amount+=max;    //arr>max
          max=arr[i];
        }else{
          amount+=arr[i]; //min<=arr<=max
        }
      }//if
    }//for
    avg = (double)amount/(number-2);
  }//if
  return avg;
}
