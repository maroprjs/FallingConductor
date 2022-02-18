/*
 * Schneider.h
 *
 *  Created on: 11 Feb 2022
 *      Author: pionet
 */

#ifndef SCHNEIDER_H_
#define SCHNEIDER_H_
#include "Arduino.h"
#include "LEDStripe.h"

#define SCHNEIDER_TIMEOUT 200
#define ANIMATION_TIMEOUT 2000

class Schneider {
public:
	Schneider(LEDStripe* ledStripe);
	void begin();
	void loop();
	void push();
	void release();
	void automaticOn();
	void automaticOff();
	LEDStripe* led(){return _ledStripe;};
	bool isAutomaticMode(){return _isAutomaticMode;};
	void startAnimateRecloser();
	void stopAnimateRecloser();
	bool recloserIsToggled(){return _isPushed;};
	bool recloserIsAnimating(){return _animateRecloser;};
	virtual ~Schneider();
private:
	uint8_t _activatePin;
	bool _isPushed;
	unsigned long _elapsedTime;
	unsigned long _elapsedAnimationTime;
	bool _isAutomaticMode;
	bool _animateRecloser;
	LEDStripe* _ledStripe;

	void animate();
};

#endif /* SCHNEIDER_H_ */
