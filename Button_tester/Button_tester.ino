
int IN = 31;
int LED = 13;
int POWER = 32;

void setup(){
  pinMode(IN, INPUT);
  pinMode(LED, OUTPUT);
}

void loop(){

  digitalWrite(POWER,HIGH);
  int Button = !digitalRead(IN);
    
  if(Button == 1){
  
    digitalWrite(LED,HIGH);
  
  }else{
  
    digitalWrite(LED,LOW);
    
  }

}
