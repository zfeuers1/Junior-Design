// ---------------------------------------------------------------------------
// movement library v1.0
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
// See "movement.h" for syntax, version history and more.
// ---------------------------------------------------------------------------
#include "Arduino.h"
#include "movement.h"

/*
Movement Constructor
*/
movement::movement(uint8_t RightMotorDirectionPin, uint8_t RightMotorEnablePin, 
				uint8_t RightMotorQuadAPin, uint8_t RightMotorQuadBPin, 
				uint8_t LeftMotorDirectionPin, uint8_t LeftMotorEnablePin,
				uint8_t LeftMotorQuadAPin, uint8_t LeftMotorQuadBPin, uint8_t speed){


	//Setting up all of the pins for the Right Motor
	pinMode(RightMotorDirectionPin, OUTPUT);
	_RightMotorDirectionPin = RightMotorDirectionPin;

	pinMode(RightMotorEnablePin, OUTPUT);
	_RightMotorEnablePin = RightMotorEnablePin;

	pinMode(RightMotorQuadAPin, INPUT);
	_RightMotorQuadAPin = RightMotorQuadAPin;

	pinMode(RightMotorQuadBPin, INPUT);
	_RightMotorQuadBPin = RightMotorQuadBPin;


	//Setting up all of the pins for the Right Motor
	pinMode(LeftMotorDirectionPin, OUTPUT);
	_LeftMotorDirectionPin = LeftMotorDirectionPin;

	pinMode(LeftMotorEnablePin, OUTPUT);
	_LeftMotorEnablePin = LeftMotorEnablePin;

	pinMode(LeftMotorQuadAPin, INPUT);
	_LeftMotorQuadAPin = LeftMotorQuadAPin;

	pinMode(LeftMotorQuadBPin, INPUT);
	_LeftMotorQuadBPin = LeftMotorQuadBPin;

	_speed = speed;

	rCount = 0;
	lCount = 0;
	QuadR = 0;
	QuadL = 0;
	lastQuadR = 0;
	lastQuadL = 0;
	distConstTurn = 1.7;//change later
	distConstStraight = 100;//change later

}


/*
Movement methods
*/
void movement::turnOffRightMotor(){
	analogWrite(_RightMotorEnablePin, 0);
}

void movement::turnOffLeftMotor(){
	analogWrite(_LeftMotorEnablePin, 0);
}


void movement::turnOffMotors(){
	turnOffLeftMotor();
	turnOffRightMotor();
}

void movement::setDirectionForward(){
	turnOffMotors();
	digitalWrite(_LeftMotorDirectionPin, 1);
	digitalWrite(_RightMotorDirectionPin, 0);
}

void movement::setDirectionBackward(){
	turnOffMotors();
	digitalWrite(_LeftMotorDirectionPin, 0);
	digitalWrite(_RightMotorDirectionPin, 1);
}

void movement::turnOnRightMotor(){
	analogWrite(_RightMotorEnablePin, _speed);
}

void movement::turnOnLeftMotor(){
	analogWrite(_LeftMotorEnablePin, _speed);
}

void movement::turnOnMotors(){
	analogWrite(_LeftMotorEnablePin, _speed);
	analogWrite(_RightMotorEnablePin, _speed);
}

void movement::setDirectionTurnRight(){
	turnOffMotors();
	digitalWrite(_LeftMotorDirectionPin, 1);
	digitalWrite(_RightMotorDirectionPin, 1);
}

void movement::setDirectionTurnLeft(){
	turnOffMotors();
	digitalWrite(_LeftMotorDirectionPin, 0);
	digitalWrite(_RightMotorDirectionPin, 0);
}

void movement::moveAtSameRate(bool interrupt){

	if(!interrupt){

		//Reading in the quad encoders
		//Shifting one of them by 1 bit and then adding another to get 2 bit quad signal
		QuadL = (digitalRead(_LeftMotorQuadAPin) << 1) + digitalRead(_LeftMotorQuadBPin);
		QuadR = (digitalRead(_RightMotorQuadAPin) << 1) + digitalRead(_RightMotorQuadBPin);

		if(QuadR != lastQuadR)
			rCount++;
		if(QuadL != lastQuadL)
			lCount++;
		if(rCount > lCount){
			turnOffRightMotor();
			turnOnLeftMotor();
		}else if(lCount > rCount){
			turnOffLeftMotor();
			turnOnRightMotor();
		}else{
			turnOnMotors();
		}

		lastQuadL = QuadL;
		lastQuadR = QuadR;
		


	}else{
		turnOffMotors();
		rCount = 0;
		lCount = 0;
		QuadR = 0;
		QuadL = 0;
		lastQuadR = 0;
		lastQuadL = 0;
	}

}

void movement::turnXdegrees(float degree){

	if(degree > 0 && degree <= 180){
		setDirectionTurnRight();
	}else{
		setDirectionTurnLeft();
		if(degree < 0){
			degree = degree * -1;
		}
	}

	degree = degree * distConstTurn;
	int distance = 0;
	int lastRcount = 0;

	while(distance < degree){

		moveAtSameRate(0);
		if(lastRcount < rCount){//if rCount went up. aka the robot every even quad increment
			distance++;
		}
		lastRcount = rCount;
	}
	moveAtSameRate(1);//reset everything back to zero

}

void movement::goXinches(int inches){
	inches = inches * distConstStraight;
	int distance = 0;
	int lastRcount = 0;

	while(distance < inches){

		moveAtSameRate(0);
		if(lastRcount < rCount){//if rCount went up. aka the robot every even quad increment
			distance++;
		}
		lastRcount = rCount;
	}
	moveAtSameRate(1);//reset everything back to zero

}
