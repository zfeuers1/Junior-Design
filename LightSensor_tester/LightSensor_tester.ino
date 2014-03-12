/*
Zachary Feuerstein
3/12/14

*/

#define LSI A0
#define RSI A1
#define FSI A2

//#define FSV 52 
//#define LSV 50

int LeftSensor = 0;
int RightSensor = 0;
int FrontSensor = 0;

void setup(){
  Serial.begin(9600);
 // pinMode(LSI, INPUT);
 // pinMode(RSI, INPUT);
  pinMode(FSI, INPUT);
 // pinMode(FSV, OUTPUT);
  //pinMode(LSV, OUTPUT);
}

void loop(){

  //digitalWrite(FSV, HIGH);
  //digitalWrite(LSV, HIGH);
  
  //LeftSensor = analogRead(LSI);//make sure you want will be outputing voltage
  //RightSensor = analogRead(RSI);//between 5mv to 5v or this wont work
  FrontSensor = analogRead(FSI);
  
  //Serial.print("\nLeft Sensor: ");
  //Serial.print(LeftSensor);
  
  //Serial.print("\tRight Sensor: ");
  //Serial.print(RightSensor);
  
  Serial.print("\tFront Sensor: ");
  Serial.print(FrontSensor);
  delay(500);
  Serial.print("\n");
  
}