// ---------------------------------------------------------------------------
// RobotControl v1.0
//
// Created by Zachary Feuerstein - zfeuers1@binghamton.edu
//
// The MIT License (MIT)
//
// Copyright (c) 2014 Zachary Feuerstein
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
// ---------------------------------------------------------------------------
#include <movement.h>
#include <UltraSonicSystem.h>
#include <NewPing.h>
#include <PushButtonSystem.h>
#include <LightSensorSystem.h>
#include <IRCommSystem.h>

//----------------------------------------------------------------------------
// Movement Setup
//
#define RME 8 //Right Motor Enable
#define RMD 23 //Right Motor Direction
#define RMQA 25 //Right Motor input A from quadrature-encoder
#define RMQB 27 //Right Motor input B from quadrature-encoder
//
#define LME 9 //Same stuff just with left motor
#define LMD 22
#define LMQA 24
#define LMQB 26
//
#define Speed 100
//
movement Robot(RMD, RME, RMQA, RMQB, LMD, LME, LMQA, LMQB, Speed);
//
//----------------------------------------------------------------------------
// UltraSonic Setup
//
#define RTP 2 //Right Trigger Pin
#define REP 3 //Right Echo Pin
// 
//Same for Left and Front sensors
#define LTP 4
#define LEP 5
#define FTP 6
#define FEP 7
//
#define maxDistance 200
//
UltraSonicSystem USSensors(LTP, LEP, RTP, REP, FTP, FEP, maxDistance);
//
//----------------------------------------------------------------------------
// Light Sensor Setup  
//
#define FL A0//front left sensor
#define FR A1
#define BL A2//back left sensor
#define BR A3
//
LightSensorSystem LSensors(FL, FR, BL, BR);
//
//----------------------------------------------------------------------------
// Push Button Setup
//
#define LPB 50
#define MPB 51
#define RPB 52
//
PushButtonSystem PushButtons(LPB, MPB, RPB);
//
//----------------------------------------------------------------------------
// IR Communication Setup
//
#define modPin 13
//
IRCommSystem IR(modPin);
//
//----------------------------------------------------------------------------
// Main Robot Control
//

bool atObstacle = false;

void setup(){
  Serial.begin(9600);//set up for printing to console
  //Serial2.begin(300);//set baud rate of Serial2 port for IR communication
}



void loop(){
  
  //-----------------------------------------------------
  // Wait until right button is pressed to begin
  //
  
  bool off = true;
  
  while(off){
    PushButtons.readIfPressed();
    off = PushButtons.Right;
  }
  
  bool start = false;
  while(!start){
    PushButtons.readIfPressed();
    start = PushButtons.Right;
    Serial.println(start);
  } 
  Serial.println("broke out;");
  //
  //-----------------------------------------------------
  //-----------------------------------------------------
  // Wait until pen is lifted to begin game
  //
  /*
  bool inPen = true;
  float lastDistanceFront;
  USSensors.getDistances();
  lastDistanceFront = USSensors.distanceFront;
  
  while(inPen){
    USSensors.getDistances();
    if((USSensors.distanceFront - lastDistanceFront) > 5){
      inPen = false;
    }
  }
  */
  
  //
  //-----------------------------------------------------
  //-----------------------------------------------------
  // Play game for 3 min.
  unsigned long startTime = millis();
  unsigned long time = 0;
  bool interrupt = true;
  int gameTime = 0;
  
  Robot.setDirectionForward();
  
  Serial.println("\nabout to start game");
  
  //---------------------------------------------------
  // Calculate what direction the beacon is and turn to it
  //
  //    
    int degree;
    degree = LSensors.calcDirection();
    Serial.println("Turn this degree: ");
    Serial.println(degree);
    Robot.turnXdegrees(degree);
  //   
  //    
  //---------------------------------------------------    
  
  
  while(gameTime < 180000){//180000 ms = 3 min
    //-----------------------------------------------------
    // Game loop
      Serial.println("\nPlaying game");

      LSensors.readSensors();
      Serial.print("\nLeftBackSensor: ");
      Serial.println(LSensors.BackLeftSensor);
      Serial.print("\nLeftFrontSensor: ");
      Serial.println(LSensors.FrontLeftSensor);
      Serial.print("\nRightBackSensor: ");
      Serial.println(LSensors.BackRightSensor);
      Serial.print("\nRightFrontSensor: ");
      Serial.println(LSensors.FrontRightSensor);

      bool atTower = false;
      atTower = LSensors.atBeacon();
      
      atObstacle = false;
      USSensors.getDistances();
      
      if((USSensors.distanceFront > 0) && (USSensors.distanceFront < 4.5)){
        atObstacle = true;
      }
      
      interrupt = atObstacle | atTower;
      
      if(interrupt){
        //---------------------------------------------------
        // Check if at beacon and if so try to capture it
        //
        if(atTower){
         
         
          for(int i=0; i<4;i++){
             IR.SetupSerial();
             delay(1000);
          }
          IR.EndSerial();
          //Robot.moveAwayFromBeacon();
          
          //---------------------------------------------------
          // Calculate what direction the beacon is and turn to it
          //
          //    
            int degree;
            degree = LSensors.calcDirection();
            Serial.println("Turn this degree: ");
            Serial.println(degree);
            Robot.turnXdegrees(degree);
          //   
          //    
          //---------------------------------------------------  
          
         }
        //
        //---------------------------------------------------
        // Check if at obstacle and avoid it
        // 
        else if(atObstacle){
            
           obstacleAvoidance();
      }
    //
    //-----------------------------------------------------
      }else{

        Robot.setDirectionForward();
        Serial.println("\nAbout to go");
        Robot.goXinches(1);
    }
    
    time = millis();
    gameTime = (time - startTime);
  }
  
  
  //
  //-----------------------------------------------------
}
//
//----------------------------------------------------------------------------


void obstacleAvoidance(){

          delay(500);
          Robot.setDirectionBackward();
          Robot.goXinches(1);
          delay(500);
          
          USSensors.getDistances();
          
          if(USSensors.distanceRight >= USSensors.distanceLeft){
            
            Robot.turnXdegrees(90);
            USSensors.getDistances();
            
            float obstacleDistance = USSensors.distanceLeft;
            float currentDistance = obstacleDistance;
            while(currentDistance < (obstacleDistance + 10)){
              Robot.setDirectionForward();
              Robot.goXinches(1);    
              USSensors.getDistances();
              currentDistance = USSensors.distanceLeft;
              
                if((USSensors.distanceFront > 0) && (USSensors.distanceFront < 4.5)){
              
                  obstacleAvoidance();
                  return;
                }
              
            }
            
            Robot.goXinches(1); 
            Robot.turnXdegrees(-90);
            
            float obstacleDistance2 = USSensors.distanceLeft;
            float currentDistance2 = obstacleDistance2;
            
            while(currentDistance2 < (obstacleDistance2 + 10)){
            
              Robot.setDirectionForward();
              Robot.goXinches(1);    
              
              USSensors.getDistances();
              currentDistance2 = USSensors.distanceLeft;
              
              if((USSensors.distanceFront > 0) && (USSensors.distanceFront < 4.5)){
              
                obstacleAvoidance();
                return;
              }
            }
            
            Robot.goXinches(1); 
            Robot.turnXdegrees(-90);
  //--------------------------------------------------------
  // If distance on the left is greater than the distance on the right  
          }else{
            
            Robot.turnXdegrees(-90);
            
            USSensors.getDistances();
            
            float obstacleDistanceR = USSensors.distanceRight;
            float currentDistanceR = obstacleDistanceR;
            while(currentDistanceR < (obstacleDistanceR + 10)){
              Robot.setDirectionForward();
              Robot.goXinches(1);    
              USSensors.getDistances();
              currentDistanceR = USSensors.distanceRight;
              
                if((USSensors.distanceFront > 0) && (USSensors.distanceFront < 4.5)){
              
                  obstacleAvoidance();
                  return;
                }
              
            }
            
            Robot.goXinches(1); 
            Robot.turnXdegrees(90);
            
            float obstacleDistanceR2 = USSensors.distanceRight;
            float currentDistanceR2 = obstacleDistanceR2;
            
            while(currentDistanceR2 < (obstacleDistanceR2 + 10)){
            
              Robot.setDirectionForward();
              Robot.goXinches(1);    
              
              USSensors.getDistances();
              currentDistanceR2 = USSensors.distanceRight;
              
              if((USSensors.distanceFront > 0) && (USSensors.distanceFront < 4.5)){
              
                obstacleAvoidance();
                return;
              }
            }
            
            Robot.goXinches(1); 
            Robot.turnXdegrees(90);            
           
          }
          
  //-----------------------------------------------------------        
          delay(500);
          Robot.setDirectionForward();
          atObstacle = false;
  }
