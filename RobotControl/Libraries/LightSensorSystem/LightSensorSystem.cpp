// ---------------------------------------------------------------------------
// LightSensorSystem library v1.0
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
//
// See "LightSensorSystem.h" for syntax, version history and more.
// ---------------------------------------------------------------------------
#include "Arduino.h"
#include "LightSensorSystem.h"


//defining the sensors as numbers
#define FRS 1
#define FLS 2 
#define BLS 3
#define BRS 4


//LightSensorSystem Constructor

LightSensorSystem::LightSensorSystem(uint8_t LightSensorFrontLeftPin, uint8_t LightSensorFrontRightPin,
						uint8_t LightSensorBackLeftPin, uint8_t LightSensorBackRightPin){

	pinMode(LightSensorFrontLeftPin, INPUT);
	_LightSensorFrontLeftPin = LightSensorFrontLeftPin;

	pinMode(LightSensorFrontRightPin, INPUT);
	_LightSensorFrontRightPin = LightSensorFrontRightPin;

	pinMode(LightSensorBackRightPin, INPUT);
	_LightSensorBackRightPin = LightSensorBackRightPin;

	pinMode(LightSensorBackLeftPin, INPUT);
	_LightSensorBackLeftPin = LightSensorBackLeftPin;

	sensorMaxConst = 1400; //change after testing
	sensor1 = 10;//arbitrary number that is not part of array
	sensor2 = 10;
	sensor3 = 10;
	sensor4 = 10;
	equivFactor = 20;//change
}

//LightSensorSystem Methods

void LightSensorSystem::readSensors(){
	FrontRightSensor = analogRead(_LightSensorFrontRightPin);
	FrontLeftSensor = analogRead(_LightSensorFrontLeftPin);
	BackLeftSensor = analogRead(_LightSensorBackLeftPin);
	BackRightSensor = analogRead(_LightSensorBackRightPin);

	SensorArray[0] = FrontRightSensor;
	SensorArray[1] = FrontLeftSensor;
	SensorArray[2] = BackLeftSensor;
	SensorArray[3] = BackRightSensor;

}
void LightSensorSystem::sortSensors(){

	//1=FrontRightSensor, 2=FrontLeftSensor, 3=BackLeftSensor, 4=BackRightSensor
	int temp = 0;
	int temp2 = 0;
	int temp3 = 0;
	
	for(int i=0;i<4;i++)
    {
        if(SensorArray[i] > temp){
        	temp3 = temp2;
        	temp2 = temp;
        	temp = SensorArray[i];

        	sensor4 = sensor3;
        	sensor3 = sensor2;
        	sensor2 = sensor1;
        	sensor1 = i + 1;
        }else if(SensorArray[i] > temp2){
        	temp3 = temp2;
        	temp2 = SensorArray[i];

        	sensor4 = sensor3;
        	sensor3 = sensor2;
        	sensor2 = i+1;
        }else if(SensorArray[i] > temp3){
        	temp3 = SensorArray[i];

        	sensor4 = sensor3;
        	sensor3 = i+1;
        }else{
        	sensor4 = i+1;
        }        
    }
}

int LightSensorSystem::calcDirection(){

	readSensors();
	sortSensors();

	int degree;

	switch(sensor1){

		case FRS:
			switch(sensor2){
		
				case BRS:
					if((FrontRightSensor - BackRightSensor) <= equivFactor){//basically the same
						degree = 90;
					}else{
						degree = 45;
					}
					break;
		
				case FLS:
					if((FrontRightSensor - FrontLeftSensor) <= equivFactor){//basically the same
						degree = 0;
					}else{
						degree = 45;						
					}
					break;
		
				default:
						degree = 45;
					break;
			}
			break;
		
		case BRS:
			switch(sensor2){
		
				case FRS:
					if((BackRightSensor - FrontRightSensor) <= equivFactor){//basically the same
						degree = 90;
					}else{
						degree = 135;
					}
					break;
		
				case BLS:
					if((BackRightSensor - BackLeftSensor) <= equivFactor){//basically the same
						degree = 180;
					}else{
						degree = 135;
					}
					break;
		
				default:
					degree = 135;
					break;
			}
			break;
		
		case FLS:
			switch(sensor2){

				case BLS:
					if((FrontLeftSensor - BackLeftSensor) <= equivFactor){//basically the same
						degree = -90;
					}else{
						degree = -45;
					}
					break;

				case FRS:
					if((FrontLeftSensor - FrontRightSensor) <= equivFactor){//basically the same
						degree = 0;
					}else{
						degree = -45;
					}
					break;

				default:
					degree = -45;
					break;
			}

			break;

		case BLS:
			switch(sensor2){

				case BRS:
					if((BackLeftSensor - BackRightSensor) <= equivFactor){//basically the same
						degree = 180;
					}else{
						degree = -135;
					}
					break;

				case FLS:
					if((BackLeftSensor - FrontLeftSensor) <= equivFactor){//basically the same
						degree = -90;
					}else{
						degree = -135;
					}
					break;

				default:
					degree = -135;
					break;
			}
			break;
		
		default:
			break;	
	}

	return degree;
}

bool LightSensorSystem::atBeacon(){

	readSensors();
	sortSensors();

	if((FrontLeftSensor + FrontRightSensor) > sensorMaxConst){
		return true;
	}
	else{
		return false;
	}
}
