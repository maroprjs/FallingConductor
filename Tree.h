/*
 * Tree.h
 *
 *  Created on: 12 Feb 2022
 *      Author: pionet
 */

#ifndef TREE_H_
#define TREE_H_
#include "Arduino.h"

#define FALLING_TIME 500

class Tree {
public:
	Tree();
	void begin();
	void loop();
	void fall();
	virtual ~Tree();
private:
	uint8_t _carLockPin;
	uint8_t _unlatchPin;
	bool _treeIsFalling;
	unsigned long _elapsedTime;

};

#endif /* TREE_H_ */
