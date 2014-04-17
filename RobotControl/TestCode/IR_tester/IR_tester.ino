#include <NewSoftSerial.h>
//#include <SoftwareSerial.h>

#define rxPin 15
#define txPin 14
#define modWavePin 13

//SoftwareSerial mySerial(rxPin, txPin); // RX, TX
NewSoftSerial mySerial(rxPin,txPin);

char IR_Recieve;// = B10011110;
byte IR_Transmit;

unsigned char uart_receive()
{
    //Pause until RXC is nonzero
    while (!(UCSR0A & (1 << RXC0)));
    
    //Get data
    return UDR0;
    
}

void setup(){
  pinMode(rxPin, INPUT);
  pinMode(txPin, OUTPUT);
  mySerial.begin(300);
  mySerial.write(B10101110);
  Serial.begin(9600);
  tone(modWavePin, 38000);
}


void loop(){  
  
 if(mySerial.available() == 0){
    IR_Recieve = mySerial.read();
    Serial.println(IR_Recieve);  
   // IR_Transmit = ~IR_Recieve;
   // Serial.println(IR_Transmit);
   // IR.write(IR_Transmit);
    delay(1000);  
  }
 else{
   Serial.println("Not Recieving");
 }
 
  //mySerial.write(IR_Recieve);
  
}
