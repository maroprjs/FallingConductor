/*
 * Fire.cpp
 *
 *  Created on: 11 Feb 2022
 *      Author: pionet
 */

#include "Fire.h"
#include "Defines.h"


Fire::Fire() {
	_firePin = FIRE_PIN;
	_isOn = false;

}

void Fire::begin(){
   pinMode(_firePin, OUTPUT);
   digitalWrite(_firePin, LOW);
}

void Fire::on(){
	digitalWrite(_firePin, HIGH);
	_isOn = true;

}

void Fire::off(){
	digitalWrite(_firePin, LOW);
	_isOn = false;
}

Fire::~Fire() {
	// TODO Auto-generated destructor stub
}

