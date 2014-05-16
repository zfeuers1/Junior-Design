/*
Zachary Feuerstein
3/12/14

*/


#define FSI A2

int FrontSensor = 0;

void setup(){
  Serial.begin(9600);
  pinMode(FSI, INPUT);

}

void loop(){

  FrontSensor = analogRead(FSI);//make sure you want will be outputing voltage from sensor
  
  Serial.print("\nFront Sensor: ");
  Serial.print(FrontSensor);
  
  delay(500);
  Serial.print("\n");
  
}
