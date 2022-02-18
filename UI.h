/*
 * UI.h
 *
 *  Created on: 11 Feb 2022
 *      Author: pionet
 */

#ifndef UI_H_
#define UI_H_
#include "Modem.h"
#include "Flash.h"
#include "Fire.h"
#include "Wheatstone.h"
#include "Tree.h"

#define PUBLISH_TIME_INTERVAL_MS 1000
#define PUBLISH_MSG_ID 3

class UI {
public:
	UI(Modem* modem,Flash* flash, Fire* fire, Wheatstone* wheatstone, Tree* tree);
	void begin();
	void loop();
	bool serialMMI(char command);
	virtual ~UI();
private:
	void publishStatus();
private:
	Modem* _modem;
	Flash* _flash;
	Fire* _fire;
	Wheatstone* _wheatstone;
	Tree* _tree;

	uint32_t _elapsedPublishTime;
	uint32_t _publishInterval;
	char* _rxMsg;
	char* _txMsg;
};

#endif /* UI_H_ */
