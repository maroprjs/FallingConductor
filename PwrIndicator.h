/*
 * PwrIndicator.h
 *
 *  Created on: 14 Feb 2022
 *      Author: pionet
 */

#ifndef PWRINDICATOR_H_
#define PWRINDICATOR_H_
#include "Arduino.h"

class PwrIndicator {
public:
	PwrIndicator();
	void begin();
	void l1On();
	void l1Off();
	void l2On();
	void l2Off();
	void l3On();
	void l3Off();
	void allOn();
	void allOff();
	virtual ~PwrIndicator();
private:
	uint8_t _led1Pin;
	uint8_t _led2Pin;
	uint8_t _led3Pin;
};

#endif /* PWRINDICATOR_H_ */
