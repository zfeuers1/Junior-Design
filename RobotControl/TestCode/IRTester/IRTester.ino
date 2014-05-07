


void setup()
{
  Serial2.begin(300); //set IR comm baud rate
  Serial.begin(9600); //set print to screen baud rate
  pinMode(13, OUTPUT); //set up pin 13 as pwm pin
   //set square wave frequency of 38 KHz
  //pinMode(50,OUTPUT);
}

int r;
int z = 129;
void loop()
{
  //noTone(13);
  //delay(100);
  if(Serial2.available() > 0)
  {
    r = Serial2.read();
    Serial.println(r);
    /*if(r>=1){
      
        //Serial.println("Something");
        //Serial.println(r, DEC);
        z = ~r;
        tone(13, 38000, 50);
        Serial2.write(z);
        //Serial.println(z);
        noTone(13);
        delay(1000);
    }else{
      noTone(13);
      //Serial.println("Nothing");
    }
    */
  }
  else
  {
    //noTone(13);
    //Serial.println("Nothing");
  }
 
  
}
