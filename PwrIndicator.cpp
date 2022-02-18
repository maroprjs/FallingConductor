/*
 * PwrIndicator.cpp
 *
 *  Created on: 14 Feb 2022
 *      Author: pionet
 */

#include "PwrIndicator.h"
#include "Defines.h"

PwrIndicator::PwrIndicator() {
	_led1Pin = LED1_PIN;
	_led2Pin = LED2_PIN;
	_led3Pin = LED3_PIN;


}
void PwrIndicator::begin(){
	pinMode(_led1Pin, OUTPUT);
	pinMode(_led2Pin, OUTPUT);
	pinMode(_led3Pin, OUTPUT);
}

void PwrIndicator::l1On(){
	digitalWrite(_led1Pin, HIGH);
}

void PwrIndicator::l1Off(){
	digitalWrite(_led1Pin, LOW);
}

void PwrIndicator::l2On(){
	digitalWrite(_led2Pin, HIGH);
}

void PwrIndicator::l2Off(){
	digitalWrite(_led2Pin, LOW);
}
void PwrIndicator::l3On(){
	digitalWrite(_led3Pin, HIGH);
}

void PwrIndicator::l3Off(){
	digitalWrite(_led3Pin, LOW);
}


void PwrIndicator::allOn(){
	l1On();
	l2On();
	l3On();
}

void PwrIndicator::allOff(){
	l1Off();
	l2Off();
	l3Off();
;}

PwrIndicator::~PwrIndicator() {
	// TODO Auto-generated destructor stub
}

