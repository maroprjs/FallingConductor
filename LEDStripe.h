/*
 * LEDStripe.h
 *
 *  Created on: 13 Feb 2022
 *      Author: pionet
 */

#ifndef LEDSTRIPE_H_
#define LEDSTRIPE_H_
#include <Adafruit_NeoPixel.h>

#define NUMPIXELS 20


class LEDStripe {
public:
	LEDStripe();
	void begin();
	void loop();
	void showBlue(void);
	void showRed(void);
	void showGreen(void);
	void showOrange(void);
	virtual ~LEDStripe();
private:
	Adafruit_NeoPixel* _pixels;
};

#endif /* LEDSTRIPE_H_ */
