/*
 * GroundSensor.cpp
 *
 *  Created on: 14 Feb 2022
 *      Author: pionet
 */

#include "GroundSensor.h"
#include "Defines.h"
GroundSensor::GroundSensor(Fire* fire, Flash* flash) {
	_gndSensorPin = GND_SENSOR_PIN;
	_fire = fire;
	_flash = flash;
	_elapsedTime = 0;
	_flashReported = false;

}

void GroundSensor::begin(){
	pinMode(_gndSensorPin, INPUT);
	_elapsedTime = millis();
}

void GroundSensor::loop(){
	if (millis() > _elapsedTime + TIME_TO_CHECK_GND ){
		int pinVal = digitalRead(_gndSensorPin);
		//Serial.print("pinval: "); Serial.println(pinVal);
		if ((pinVal == HIGH) && (_flashReported == false)){
			_flash->flash();
			_fire->on();
			_flashReported = true;

		}
		if ((digitalRead(_gndSensorPin) == LOW) && (_flashReported == true)){
		//	//_flash->allFlashOff();
		//	_fire->off();
			_flashReported = false;

		};
		_elapsedTime = millis();

	}

}




GroundSensor::~GroundSensor() {
	// TODO Auto-generated destructor stub
}

