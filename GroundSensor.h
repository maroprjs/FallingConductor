/*
 * GroundSensor.h
 *
 *  Created on: 14 Feb 2022
 *      Author: pionet
 */

#ifndef GROUNDSENSOR_H_
#define GROUNDSENSOR_H_
#include "Arduino.h"
#include "Fire.h"
#include "Flash.h"

#define TIME_TO_CHECK_GND 300

class GroundSensor {
public:
	GroundSensor(Fire* fire, Flash* flash);
	void begin();
	void loop();
	virtual ~GroundSensor();
private:
	uint8_t _gndSensorPin;
	Fire* _fire;
	Flash* _flash;
	unsigned long _elapsedTime;
	bool _flashReported;

};

#endif /* GROUNDSENSOR_H_ */
