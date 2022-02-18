/*
 * Flash.h
 *
 *  Created on: 11 Feb 2022
 *      Author: pionet
 */

#ifndef FLASH_H_
#define FLASH_H_

#include "Arduino.h"

#define FLASH_TIMEOUT 3000

class Flash {
public:
	Flash();
	void begin();
	void loop();
	void allFlashOff();
	void allFlashOn();
	bool isFlashOn(){return _flashIsOn;};
	void flash();
	virtual ~Flash();
private:
	uint8_t _flash1Pin;
	uint8_t _flash2Pin;
	uint8_t _flash3Pin;
	bool _flashIsOn;
	bool _permanentOn;
	unsigned long _elapsedTime;
};

#endif /* FLASH_H_ */
