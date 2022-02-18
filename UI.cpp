/*
 * UI.cpp
 *
 *  Created on: 11 Feb 2022
 *      Author: pionet
 */

#include "UI.h"


UI::UI(Modem* modem, Flash* flash, Fire* fire, Wheatstone* wheatstone, Tree* tree) {
	_modem = modem;
	_flash = flash;
	_fire = fire;
	_wheatstone = wheatstone;
	_tree = tree;
	_elapsedPublishTime = 0;
	_publishInterval = PUBLISH_TIME_INTERVAL_MS;
	_rxMsg = new char[UDP_TX_PACKET_MAX_SIZE];
	_txMsg = new char[UDP_TX_PACKET_MAX_SIZE];

}

void UI::begin(){
	_elapsedPublishTime = millis();
}

void UI::loop(){
	if (_modem->msgArrived()){
		_modem->readMsg(_rxMsg);
		//Serial.println(_rxMsg);
		serialMMI(_rxMsg[0]);
	}
	while(_modem->mmiPort()->available()){
		char cmd = _modem->mmiPort()->read();
		_modem->mmiPort()->flush();
		serialMMI(cmd);
	}
	publishStatus();
}

/****************************
 *
 *
 *  a - (a) flashes shortly
 *  b - flash permanently on
 *  c - flash off
 *  d - fire on
 *  e - fire off
 *  f - schneider - toggle circuite breaker
 *  g - tree fall (unlatches relay and shakes the tree)
 *  h - turns automatic mode on
 *  i - turns automatic mode off
 *
 *
 */
bool UI::serialMMI(char command){
	bool retVal = false;
	_modem->mmiPort()->print(command);
	switch (command){
	case 'a':{
			_flash->flash();
		}
		retVal = true;
		break;
	case 'b':{
			_flash->allFlashOn();
		}
		retVal = true;
		break;
	case 'c':{
			_flash->allFlashOff();
		}
		retVal = true;
		break;
	case 'd':{
			_fire->on();
		}
		retVal = true;
		break;
	case 'e':{
			_fire->off();
		}
		retVal = true;
		break;
	case 'f':{
			_wheatstone->recloser()->push();
		}
		retVal = true;
		break;
	case 'g':{
			_tree->fall();
		}
		retVal = true;
		break;
	case 'h':{
			_wheatstone->recloser()->automaticOn();
		}
		retVal = true;
		break;
	case 'i':{
		_wheatstone->recloser()->automaticOff();
		}
		retVal = true;
		break;
	}
	return retVal;
}

/*
 * this must be called in loop function
 *
 * protocol fields:
 *   *
 Falling Conductor Message Fields:
[msg ID], 						- can be ignred
[flashings lights on/off], 				- can be ignored
[is fire on/off], 					- can be ignored
[is falling cable detected/or not], 			- "1" means that cable 1 is not hanging anymore (in automatic mode the recloser will be turned off an LEDs red and in manual mode only LEDs will switch to orange)
[is electricity turned off (1 = off)],			- measures actually on cable2(in the middle) to determine if the recloser is off or not (the recloser doesn't know his state, there is only a toggle button)
[is there a shortccut between two lines, yes/mo], 	-it recognized if there is a branch fallen on the electricity line; in automatic mode the recloser will try to revive and try to turn on again every 2 seconds
[is the recloser automatic or non-automatic mode]	-is tells if the recloser is in automatic mode, in this mode the electricy is turned off as sson as e.g. broken cable is detected, in non-automatic mode, fire will burn
[is recloser animating, yes/no], 			-if shortcut is recognized, the recloser should animate, meaning to retry the electricity connection
[is recloser toggled (in turn-on or turn-off state)] 	-whenever the recloser is toggled (also during animation), this flas will be set to "1" for some time

 */
void UI::publishStatus(){
	//if (_nfcReader1->isNewTagToPublish() || _nfcReader2->isNewTagToPublish() || _nfcReader3->isNewTagToPublish()){
	//	_elapsedPublishTime = 0; //that will make next if condition true immediately
	//};
	if (millis() >= (_elapsedPublishTime + _publishInterval)){
		//build message
		sprintf((char*)_txMsg,"%u,%u,%u,%u,%u,%u,%u,%u,%u", (unsigned int)PUBLISH_MSG_ID, \
											(unsigned int)_flash->isFlashOn(), \
											(unsigned int)_fire->isOn(), \
											(unsigned int)_wheatstone->isBrokenCable(), \
											(unsigned int)_wheatstone->isElectricityOff(), \
											(unsigned int)_wheatstone->isShortcut(), \
											(unsigned int)_wheatstone->recloser()->isAutomaticMode(), \
											(unsigned int)_wheatstone->recloser()->recloserIsAnimating(), \
											(unsigned int)_wheatstone->recloser()->recloserIsToggled());
		_modem->sendUdpMsg(_txMsg);
		_elapsedPublishTime = millis();
	}
}

UI::~UI() {
	// TODO Auto-generated destructor stub
}

