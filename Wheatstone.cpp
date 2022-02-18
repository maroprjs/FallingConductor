/*
 * Wheatstone.cpp
 *
 *  Created on: 12 Feb 2022
 *      Author: pionet
 */

#include "Wheatstone.h"
#include "Defines.h"
Wheatstone::Wheatstone(Schneider* schneider, PwrIndicator* pwrIndicator) {
	_l1SensePin = L1_SENSE_PIN;
	_l2SensePin = L2_SENSE_PIN;
	_l3SensePin = L3_SENSE_PIN;
	_measL1_c = 0;
	_measL2_c = 0;
	_measL3_c = 0;
	//_test_count = 0;
	_measL1Sample = 0;
	_measL2Sample = 0;
	_measL3Sample = 0;
	_sampleCountElectricity = 0;
	_sampleCountShortcut = 0;
	_sampleCount_c = 0;

	_lastCheckedForElectricity = 0;
	_lastCheckedForShortcut = 0;;
	_measL1 = 0;
	_measL2 = 0;
	_measL3 = 0;

	_schneider = schneider;
	_reactivationRequested = false; //needed for state transitin from e.g. broken cable to connected state
	_deactivationRequested = false;
	_l1CableState = CONNECTED;
	_electricityOff = true;
	_l3ShortCircuitState = ISOLATED;
	_elecFlagPropagated = false;
	_pwrIndicator = pwrIndicator;
}

void Wheatstone::begin(){
	pinMode(_l1SensePin, INPUT);
	pinMode(_l2SensePin, INPUT);
	pinMode(_l3SensePin, INPUT);
	_lastCheckedForElectricity = millis();
	_lastCheckedForShortcut = millis();

}

void Wheatstone::loop(){

	_measL1Sample = analogRead(_l1SensePin); //use this to sense broken (fast sense ...must be based on (c)ounter )
	//_measL2Sample = analogRead(_l2SensePin); //use this to sense if electricity is active - slow sense
	_measL3Sample = analogRead(_l3SensePin); //use this to sense shortcut between L2 and L3 - slow sense

	if ((_electricityOff == false) && _l3ShortCircuitState == ISOLATED) senseBrokenCable(); //fast measurement
	senseElectricity(); //slow measurement is enough
	senseShortcut(); //slow measurement enough

}

void Wheatstone::senseBrokenCable(){
	_measL1_c = _measL1_c + _measL1Sample;
	_sampleCount_c++;
	if (_sampleCount_c % MEAS_INTERVAL_C == 0 ){
			if ((_measL1_c / MEAS_INTERVAL_C) < L1_OK_VALUE){ //Broken L1 detected
				//Serial.println("L1 BROKEN !!!!!");
				//Serial.println(_measL1_c / MEAS_INTERVAL_C);
				if (_l1CableState == CONNECTED) {
					_l1CableState = BROKEN_DETECTED;
					_pwrIndicator->l1Off();
					if (_schneider->isAutomaticMode() == true){
						Serial.println("pushing");
							_schneider->push();
					}else{
						_schneider->led()->showOrange();
					};
				};
			}else{ //cable L1 is attached and all good:
				if (_l1CableState == BROKEN_DETECTED){
					_pwrIndicator->l1On();
					if (_schneider->isAutomaticMode() == false){
						_schneider->led()->showGreen();
					}
					_l1CableState = CONNECTED;
				};
			};

		_sampleCount_c = 0;
		_measL1_c = 0;
	};
}


/*
void Wheatstone::senseElectricity(){
	_measL2 = _measL2 + _measL2Sample;
	_sampleCountElectricity++;
	if (millis() > _lastCheckedForElectricity + MEAS_INTERVAL_T){
		_measL2 = _measL2 / _sampleCountElectricity;
		Serial.print("L2: ");Serial.println(_measL2);
		if (_measL2 < L2_OK_VALUE){
			_electricityOff = true;
			_schneider->led()->showRed();

		}else{
			//_electricityFlag = true;
			//_
			_electricityOff = false;
			_schneider->led()->showBlue();

		}
		_measL2 = 0;
		_sampleCountElectricity = 0;
		_lastCheckedForElectricity = millis();

	}
}
*/
void Wheatstone::senseElectricity(){

	if (millis() > _lastCheckedForElectricity + MEAS_INTERVAL_T){

		int inValue = digitalRead(_l2SensePin);

		if (( inValue == HIGH) && (_elecFlagPropagated == false)){
			_electricityOff = false;
				_schneider->led()->showGreen();

			_pwrIndicator->allOn();
			Serial.print("L2: ");Serial.println("HIGH");
			_elecFlagPropagated = true;
		}
		if (( inValue == LOW) && (_elecFlagPropagated == true)){
			_electricityOff = true;
			_schneider->led()->showRed();
			_pwrIndicator->allOff();
			Serial.print("L2: ");Serial.println("LOW");
			_elecFlagPropagated = false;
		}
		_lastCheckedForElectricity = millis();

	}
}


void Wheatstone::senseShortcut(){
	//_electricityOff = l2IsOff(); //use of L2 to dertmine
	_measL3 = _measL3 + _measL3Sample;
	_sampleCountShortcut++;
	if (millis() > _lastCheckedForShortcut + MEAS_INTERVAL_T){
		_measL3 = _measL3 / _sampleCountShortcut;
		Serial.print("L3: ");Serial.println(_measL3);
		if ((_measL3 > L3_NORM_VALUE) && (_l3ShortCircuitState == ISOLATED)){ //shortcut detected
				if (_schneider->isAutomaticMode() == true){
					//_schneider->led()->showRed();
					_schneider->startAnimateRecloser();
				};
				_l3ShortCircuitState = SHORTCUT_DETECTED;

			};
		if ((_measL3 < L3_NORM_VALUE) && (_measL3 > L3_LOW_THR ) && (_l3ShortCircuitState == SHORTCUT_DETECTED)){ //all isolated
			if (_l3ShortCircuitState == SHORTCUT_DETECTED){
				//if (_schneider->isAutomaticMode() == true){
					_schneider->stopAnimateRecloser();

				//}
				_l3ShortCircuitState = ISOLATED;


				_reactivationRequested = true;
			}


		};
		_measL3 = 0;
		_sampleCountShortcut = 0;
		_lastCheckedForShortcut = millis();
	}


}




/*
bool Wheatstone::l2IsOff(){
	bool retVal = false;
	if ((_measL2_c / MEAS_INTERVAL_C) < L2_OK_VALUE){
		retVal =  true;
	}
	return retVal;
}

bool Wheatstone::l3ShortcutDetected(){
	bool retVal = false;
	if ((_measL3_c / MEAS_INTERVAL_C) > L3_OK_VALUE){
		retVal =  true;
	}
	return retVal;
}
*/

Wheatstone::~Wheatstone() {
	// TODO Auto-generated destructor stub
}

