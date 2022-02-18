/*
 * LEDStripe.cpp
 *
 *  Created on: 13 Feb 2022
 *      Author: pionet
 */

#include "LEDStripe.h"
#include "Defines.h"

LEDStripe::LEDStripe() {
	_pixels = new Adafruit_NeoPixel(NUMPIXELS, CONTROLLINO_D8, NEO_GRB + NEO_KHZ800);

}

void LEDStripe::begin(){
	_pixels->begin();
	showBlue();

}
void LEDStripe::loop(){

}

void LEDStripe::showBlue(void){
	   _pixels->clear(); // Set all pixel colors to 'off'
	   for(int i=0; i<NUMPIXELS; i++) { // For each pixel...
	    // pixels.Color() takes RGB values, from 0,0,0 up to 255,255,255
	    // Here we're using a moderately bright green color:
	    _pixels->setPixelColor(i, _pixels->Color(18, 65, 145));
	  }
	  _pixels->show();

}

void LEDStripe::showRed(void){
	   _pixels->clear(); // Set all pixel colors to 'off'
	   for(int i=0; i<NUMPIXELS; i++) { // For each pixel...
	    // pixels.Color() takes RGB values, from 0,0,0 up to 255,255,255
	    // Here we're using a moderately bright green color:
	    _pixels->setPixelColor(i, _pixels->Color(255, 0, 0));
	  }
	  _pixels->show();

}
void LEDStripe::showGreen(void){
	   _pixels->clear(); // Set all pixel colors to 'off'
	   for(int i=0; i<NUMPIXELS; i++) { // For each pixel...
	    // pixels.Color() takes RGB values, from 0,0,0 up to 255,255,255
	    // Here we're using a moderately bright green color:
	    _pixels->setPixelColor(i, _pixels->Color(0, 255, 0));
	  }
	  _pixels->show();

}

void LEDStripe::showOrange(void){
   _pixels->clear(); // Set all pixel colors to 'off'
   for(int i=0; i<NUMPIXELS; i++) { // For each pixel...
    // pixels.Color() takes RGB values, from 0,0,0 up to 255,255,255
    // Here we're using a moderately bright green color:
    _pixels->setPixelColor(i, _pixels->Color(255, 100, 0));
  }
  _pixels->show();
}


LEDStripe::~LEDStripe() {
	// TODO Auto-generated destructor stub
}

