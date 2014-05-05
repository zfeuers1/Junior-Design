
int IN = 31;
int LED = 13;

void setup(){
  pinMode(IN, INPUT);
  pinMode(LED, OUTPUT);
  Serial.begin(9600);
}

void loop(){
  int Button = !digitalRead(IN);
    
  if(Button == 1){
     Serial.write("On\n");
    digitalWrite(LED,HIGH);
  
  }else{
    Serial.write("Off\n");
    digitalWrite(LED,LOW);
    
  }

}






