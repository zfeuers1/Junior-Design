// ---------------------------------------------------------------------------
// LightSensorSystem library v1.0
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
//		Constructor
//		readSensors
//		sortSensors
// 04/28/2014 v1.1 -
//		calcDirection
//		atBeacon
//
// ---------------------------------------------------------------------------


#ifndef LightSensorSystem_h
#define LightSensorSystem_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include <Arduino.h>
#else
	#include <WProgram.h>
	#include <pins_arduino.h>
#endif

#include <avr/io.h>
#include <avr/interrupt.h>

class LightSensorSystem{

	public:
		LightSensorSystem(uint8_t LightSensorFrontLeftPin, uint8_t LightSensorFrontRightPin,
						uint8_t LightSensorBackLeftPin, uint8_t LightSensorBackRightPin);
		void readSensors();
		int calcDirection();
		bool atBeacon();
		void sortSensors();
		
		int FrontRightSensor;
		int FrontLeftSensor;
		int BackRightSensor;
		int BackLeftSensor;

		uint8_t sensor1;
		uint8_t sensor2;
		uint8_t sensor3;
		uint8_t sensor4;
	private:
		
		int SensorArray[4];

		uint8_t _LightSensorFrontLeftPin;
		uint8_t _LightSensorFrontRightPin;
		uint8_t _LightSensorBackLeftPin;
		uint8_t _LightSensorBackRightPin;

		int equivFactor;
		int sensorMaxConst;
};

#endif