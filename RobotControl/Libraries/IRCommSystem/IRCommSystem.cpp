// ---------------------------------------------------------------------------
// IRCommSystem library v1.0
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
// See "IRCommSystem.h" for syntax, version history and more.
// ---------------------------------------------------------------------------
#include "Arduino.h"
#include "IRCommSystem.h"

IRCommSystem::IRCommSystem(uint8_t modPin){

	pinMode(modPin, OUTPUT);
	_modPin = modPin;
	tone(_modPin, 38000);
}

bool IRCommSystem::isRecieving(){

	if(Serial2.available() > 0){

		Serial.println("Recieving");
		return true;
	}else{
		Serial.println("Not Recieving");
		return false;
	}

}

void IRCommSystem::read(){
	recievedIR = Serial2.read();
	Serial.print("\nRead IR: ");
	Serial.print(recievedIR);
}

void IRCommSystem::write(){
	transmitIR = ~recievedIR;
	Serial2.write(transmitIR);
	Serial.print("\nTransmit IR: ");
	Serial.print(transmitIR);
}

bool IRCommSystem::capture(){

	if(isRecieving()){
		read();
		write();
		return true;
	}else{
		return false;
	}

}