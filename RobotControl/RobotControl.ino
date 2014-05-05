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
#define Speed 90
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
// Main Robot Control
//
void setup(){
  Serial.begin(9600);
}
void loop(){
  
  //-----------------------------------------------------
  // Wait until middle button is pressed to begin
  //
  bool start = false;
  while(!start){
    PushButtons.readIfPressed();
    start = PushButtons.Right;
  }
  //
  //-----------------------------------------------------
  //-----------------------------------------------------
  // Wait until pen is lifted to begin game
  //
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
  //
  //-----------------------------------------------------
  //-----------------------------------------------------
  // Play game for 3 min, Then stop.
  unsigned long startTime = millis();
  unsigned long time = 0;
  
  while((time - startTime) < 180000){//180000 ms = 3 min
    //-----------------------------------------------------
    // Game loop
  
  
  
  
  
  
  
    //
    //-----------------------------------------------------
    time = millis();
  }
  //
  //-----------------------------------------------------
}
//
//----------------------------------------------------------------------------
