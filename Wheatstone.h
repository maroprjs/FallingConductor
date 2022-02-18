/*
 * Wheatstone.h
 *
 *  Created on: 12 Feb 2022
 *      Author: pionet
 */

#ifndef WHEATSTONE_H_
#define WHEATSTONE_H_

#include "Arduino.h"
#include "Schneider.h"
#include "PwrIndicator.h"

#define MEAS_INTERVAL_C 10 // as [count]
#define MEAS_INTERVAL_T 500 //in [ms]
#define L1_OK_VALUE 10 //detect falling cable -normal around 800....goes to around 2
#define L2_OK_VALUE 750 //detect electricity status - normal around 800, but this only to detect when lectricity is cut off
#define L3_NORM_VALUE 710 //detect shurtcut - normal at short cut around 755 and normal operation 670
#define L3_LOW_THR 500

class Wheatstone {
	enum BrokenCableState{
		CONNECTED,
		BROKEN_DETECTED
	};
	enum ShortCircuitState{
		ISOLATED,
		SHORTCUT_DETECTED
	};
public:
	Wheatstone(Schneider* schneider, PwrIndicator* pwrIndicator);
	void begin();
	void loop();
	//bool l2IsOff();
	//bool l3ShortcutDetected();
	void senseBrokenCable();
	void senseElectricity();
	void senseShortcut();
	BrokenCableState isBrokenCable(){ return _l1CableState;};
	bool isElectricityOff(){return _electricityOff;};
	ShortCircuitState isShortcut(){return _l3ShortCircuitState;};
	Schneider* recloser(){return _schneider;};
	virtual ~Wheatstone();
private:
	uint8_t _l1SensePin;
	uint8_t _l2SensePin;
	uint8_t _l3SensePin;
	int _measL1_c, _measL2_c,_measL3_c;// , _test_count;
	int _measL1Sample, _measL2Sample,_measL3Sample ;
	int _sampleCountElectricity, _sampleCountShortcut, _sampleCount_c;
	unsigned long _lastCheckedForElectricity, _lastCheckedForShortcut;
	unsigned long _measL1, _measL2,_measL3 ;
	Schneider* _schneider;
	bool _reactivationRequested,_deactivationRequested;
	BrokenCableState _l1CableState;
	ShortCircuitState _l3ShortCircuitState;
	bool _electricityOff;
	bool _elecFlagPropagated;
	PwrIndicator* _pwrIndicator;
};

#endif /* WHEATSTONE_H_ */
