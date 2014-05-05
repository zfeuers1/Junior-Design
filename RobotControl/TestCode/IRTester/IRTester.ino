


void setup()
{
  Serial1.begin(300); //set IR comm baud rate
  Serial.begin(9600); //set print to screen baud rate
  pinMode(13, OUTPUT); //set up pin 13 as pwm pin
  tone(13, 38000); //set square wave frequency of 38 KHz
}

int r;
int z = 129;
void loop()
{

  if(Serial1.available() > 0)
  {
  
    Serial.println("Something");
    r = Serial1.read();
    z = ~r;
    Serial1.write(z);
    Serial.println(r);
    Serial.println(z);
    delay(1000);
  }
  else
  {
  
    Serial.println("Nothing");
    
  }
  

}
