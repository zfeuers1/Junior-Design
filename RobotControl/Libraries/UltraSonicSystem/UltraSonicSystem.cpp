// ---------------------------------------------------------------------------
// UltraSonicSystem library v1.0
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
// See "UltraSonicSystem.h" for syntax, version history and more.
// ---------------------------------------------------------------------------
#include "Arduino.h"
#include "UltraSonicSystem.h"
#include "NewPing.h"


UltraSonicSystem::UltraSonicSystem(uint8_t TPL, uint8_t EPL, uint8_t TPR, uint8_t EPR, uint8_t TPF, uint8_t EPF, int maxDistance){

	NewPing lSonar(TPL,EPL,maxDistance);
	leftSensor = lSonar;

	NewPing rSonar(TPR,EPR,maxDistance);
	rightSensor = rSonar;

	NewPing fSonar(TPF,EPF, maxDistance);
	frontSensor = fSonar;
}

void UltraSonicSystem::getDistances(){

	delay(50);                      // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
    unsigned int uS = leftSensor.ping(); // Send ping, get ping time in microseconds (uS).
    Serial.print("Distance: ");
    distanceLeft = uS / US_ROUNDTRIP_CM;
    distanceLeft = .393701 * distanceLeft; //inches
    delay(50);
    unsigned int uS2 = rightSensor.ping(); // Send ping, get ping time in microseconds (uS).
    Serial.print("Distance: ");
    distanceRight = uS2 / US_ROUNDTRIP_CM;
    distanceRight = .393701 * distanceRight;
    delay(50);
    unsigned int uS3 = frontSensor.ping(); // Send ping, get ping time in microseconds (uS).
    Serial.print("Distance: ");
    distanceFront = uS3 / US_ROUNDTRIP_CM;
    distanceFront = .393701 * distanceFront;

}
