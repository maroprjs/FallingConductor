/*
 * Flash.cpp
 *
 *  Created on: 11 Feb 2022
 *      Author: pionet
 */

#include "Flash.h"
#include "Defines.h"

Flash::Flash() {
	_flash1Pin = FLASH1_PIN ;
	_flash2Pin = FLASH2_PIN ;
	_flash3Pin = FLASH3_PIN ;
	_flashIsOn = false;
	_permanentOn = false;
	_elapsedTime = 0;


}

void Flash::begin(){
  pinMode(_flash1Pin, OUTPUT);
  pinMode(_flash2Pin, OUTPUT);
  pinMode(_flash3Pin, OUTPUT);
  allFlashOff();
}

void Flash::loop(){
	if (millis() > _elapsedTime + FLASH_TIMEOUT){
		if (_flashIsOn == true && _permanentOn == false){
			allFlashOff();
		}
	}
}

void Flash::allFlashOff(){
	digitalWrite(_flash1Pin, LOW);
	digitalWrite(_flash2Pin, LOW);
	digitalWrite(_flash3Pin, LOW);
	_flashIsOn = false;
	_permanentOn = false;
}

void Flash::allFlashOn(){
	digitalWrite(_flash1Pin, HIGH);
	digitalWrite(_flash2Pin, HIGH);
	digitalWrite(_flash3Pin, HIGH);
	_flashIsOn = true;
	_permanentOn = true;
}

void Flash::flash(){
	digitalWrite(_flash1Pin, HIGH);
	digitalWrite(_flash2Pin, HIGH);
	digitalWrite(_flash3Pin, HIGH);
	_flashIsOn = true;
	_permanentOn = false;
	_elapsedTime = millis();
}

Flash::~Flash() {
	// TODO Auto-generated destructor stub
}

