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
}

void IRCommSystem::SetupSerial(){

	//Stop Carrier
   	noTone(_modPin);
  
  	//Set as output
	 pinMode(_modPin, OUTPUT);
  
  	//Set low
  	digitalWrite(_modPin, LOW);

	Serial2.begin(300);
}

void IRCommSystem::EndSerial(){


	//Stop Carrier
   	noTone(_modPin);
  
  	//Set as output
	pinMode(_modPin, OUTPUT);
  
  	//Set low
  	digitalWrite(_modPin, LOW);

	Serial2.end();

}


void serialEvent2(void)
{
  byte data = 0;
  unsigned long StartTime = millis();
  
  //Read data
  while (Serial2.available() > 0)
  {
    data = Serial2.read();
    
    //Start Carrier
    tone(13, 38000);
  
    //If serial data is available, sent the bitwise inversion of it back out 
    Serial2.write(~data);

    //Wait for send to complete
    while ((millis() - StartTime) <50){}

    //Stop Carrier
   	noTone(13);
  
  	//Set as output
	   pinMode(13, OUTPUT);
  
  	//Set low
  	digitalWrite(13, LOW);
  }


  //Clear the read buffer
  if (Serial2.available() > 0) 
    Serial2.read();
}

