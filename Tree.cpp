/*
 * Tree.cpp
 *
 *  Created on: 12 Feb 2022
 *      Author: pionet
 */

#include "Tree.h"
#include "Defines.h"

Tree::Tree() {
	_carLockPin = CAR_LOCK_PIN;
	_unlatchPin = UNLATCH_PIN;
	_treeIsFalling = false;
	_elapsedTime = 0;

}

void Tree::begin(){
	pinMode(_carLockPin, OUTPUT);
	pinMode(_unlatchPin, OUTPUT);
	digitalWrite(_carLockPin, LOW);
	digitalWrite(_unlatchPin, LOW);
}

void Tree::loop(){
	if (millis() > _elapsedTime + FALLING_TIME){
		if (_treeIsFalling == true){
			_treeIsFalling = false;
			digitalWrite(_carLockPin, LOW);
			digitalWrite(_unlatchPin, LOW);
		}
	}
}

void Tree::fall(){
	digitalWrite(_carLockPin, HIGH);
	//delay(1000);
	digitalWrite(_unlatchPin, HIGH);
	_treeIsFalling = true;
	_elapsedTime = millis();


}

Tree::~Tree() {
	// TODO Auto-generated destructor stub
}

