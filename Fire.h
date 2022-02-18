/*
 * Fire.h
 *
 *  Created on: 11 Feb 2022
 *      Author: pionet
 */

#ifndef FIRE_H_
#define FIRE_H_
#include "Arduino.h"

class Fire {
public:
	Fire();
	void begin();
	void on();
	void off();
	bool isOn(){return _isOn;};;
	virtual ~Fire();
private:
	uint8_t _firePin;
	bool _isOn;
};

#endif /* FIRE_H_ */
