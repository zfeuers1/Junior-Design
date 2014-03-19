/*
Zachary Feuerstein
3/18/14
38khz wave generator. Use pwm pin 10 as output.
set frequency to 38khz.
*/

void setup(){
  pinMode(10,OUTPUT);  
  tone(10, 38000);
}
void loop (){

}
