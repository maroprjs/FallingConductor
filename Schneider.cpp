/*
 * Schneider.cpp
 *
 *  Created on: 11 Feb 2022
 *      Author: pionet
 */

#include "Schneider.h"
#include "Defines.h"

Schneider::Schneider(LEDStripe* ledStripe) {
	_activatePin = SCHNEIDER_PIN;
	_isPushed = false;
	_elapsedTime = 0;
	_isAutomaticMode = false;
	_animateRecloser = false;
	_elapsedAnimationTime = 0;
	_ledStripe = ledStripe;
}

void Schneider::begin(){
   pinMode(_activatePin, OUTPUT);
   digitalWrite(_activatePin, HIGH);
}

void Schneider::loop(){
	if (millis() > _elapsedTime + SCHNEIDER_TIMEOUT){
		if (_isPushed == true){
			release();
		}
	}
	if (_animateRecloser == true){
		animate();
	}
}

void Schneider::startAnimateRecloser(){
	_animateRecloser = true;
}

void Schneider::stopAnimateRecloser(){
	_animateRecloser = false;
}

void Schneider::push(){
	digitalWrite(_activatePin, LOW);
	_isPushed = true;
	_elapsedTime = millis();

}

void Schneider::automaticOn(){
	_isAutomaticMode = true;
}
void Schneider::automaticOff(){
	_isAutomaticMode = false;
}

void Schneider::release(){
	digitalWrite(_activatePin, HIGH);
	_isPushed = false;
}

void Schneider::animate(){
    if (millis() > _elapsedAnimationTime + ANIMATION_TIMEOUT){
    	push();
    	_elapsedAnimationTime = millis();;
    }
}



Schneider::~Schneider() {
	// TODO Auto-generated destructor stub
}

