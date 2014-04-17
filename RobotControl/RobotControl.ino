/*
Zachary Feuerstein
2/16/14
 
 Junior Design Project
 
 */

int RME = 8; //Right Motor Enable
int RMD = 23; //Right Motor Direction
int RMA = 25; //Right Motor input A from quadrature-encoder
int RMB = 27; //Right Motor input B from quadrature-encoder

int LME = 13; //Same stuff just with left motor
int LMD = 22;
int LMA = 24;
int LMB = 26;

int LMC = 0; //Left Motor Counter
int RMC = 0; //Right Motor Counter

int Speed = 200;

int LMS = 0; //Left Motor Signal
int LLMS = 0; //Last Left Motor Signal
int RMS = 0;  //Right Motor Signal
int LRMS = 0; //Last Right Motor Signal

void moveForward(){

  while(1){

    
    LMS = (digitalRead(LMA) << 1) + digitalRead(LMB);

    RMS = (digitalRead(RMA) << 1) + digitalRead(RMB);

    if(LMS != LLMS){
      LMC++;
    }
    if(RMS != LRMS){
      RMC++;
    }

    if(RMC == LMC){

      analogWrite(RME, Speed);
      analogWrite(LME, Speed);

    }
    else if(RMC > LMC){

      analogWrite(RME, 0);
      analogWrite(LME, Speed);

    }
    else{

      analogWrite(RME, Speed);
      analogWrite(LME, 0);

    }

  }

  LLMS = LMS;
  LRMS = RMS;


}

void setup(){

  pinMode(RME, OUTPUT);  
  pinMode(RMD, OUTPUT);
  pinMode(RMA, INPUT);  
  pinMode(RMB, INPUT);

  pinMode(LME, OUTPUT);  
  pinMode(LMD, OUTPUT);
  pinMode(LMA, INPUT);  
  pinMode(LMB, INPUT);  

}

void loop(){

  analogWrite(RME, 0);
  analogWrite(LME, 0);

  digitalWrite(RMD, 0);
  digitalWrite(LMD, 1);

  moveForward();

}


