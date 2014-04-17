// ---------------------------------------------------------------------------
// movement library v1.0
//
// Created by Zachary Feuerstein - zfeuers1@binghamton.edu
// http://www.github.com/zfeuers1
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
// History:
//
// 04/17/2014 v1.0 -
//		added all intial functions including
//			The Class Contructor
//			setDirectionForward();
//			setDirectionBackward();		
//			setDirectionTurnRight();
//			setDirectionTurnLeft();
//			moveAtSameRate(bool interrupt);
//			turnXdegrees(float degree);
//			goXinches(int inches);
//
// ---------------------------------------------------------------------------


#ifndef movement_h
#define movement_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include <Arduino.h>
#else
	#include <WProgram.h>
	#include <pins_arduino.h>
#endif

#include <avr/io.h>
#include <avr/interrupt.h>

class movement{
	public:
		movement(uint8_t RightMotorDirectionPin, uint8_t RightMotorEnablePin, 
				uint8_t RightMotorQuadAPin, uint8_t RightMotorQuadBPin, 
				uint8_t LeftMotorDirectionPin, uint8_t LeftMotorEnablePin,
				uint8_t LeftMotorQuadAPin, uint8_t LeftMotorQuadBPin, uint8_t speed);
		void setDirectionForward();
		void setDirectionBackward();		
		void setDirectionTurnRight();
		void setDirectionTurnLeft();
		void moveAtSameRate(bool interrupt);
		void turnXdegrees(float degree);
		void goXinches(int inches);
	private:
		void turnOnRightMotor();
		void turnOnLeftMotor();
		void turnOnMotors();
		void turnOffRightMotor();
		void turnOffLeftMotor();
		void turnOffMotors();

		uint8_t _RightMotorDirectionPin;
		uint8_t _RightMotorEnablePin;
		uint8_t _RightMotorQuadAPin;
		uint8_t _RightMotorQuadBPin;
		uint8_t _LeftMotorDirectionPin;
		uint8_t _LeftMotorEnablePin;
		uint8_t _LeftMotorQuadAPin;
		uint8_t _LeftMotorQuadBPin;
		uint8_t _speed;
		int rCount;
		int lCount;
		int QuadR;
		int QuadL;
		int lastQuadR;
		int lastQuadL;
		float distConstTurn;
		float distConstStraight;
};

#endif