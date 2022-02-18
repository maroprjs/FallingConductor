/*
 * Defines.h
 *
 *  Created on: 3 Feb 2022
 *      Author: pionet
 */

#ifndef DEFINES_H_
#define DEFINES_H_
#include "Controllino.h"

//flash class
#define FLASH1_PIN CONTROLLINO_R0
#define FLASH2_PIN CONTROLLINO_R1
#define FLASH3_PIN CONTROLLINO_R2

//fire class:
#define FIRE_PIN CONTROLLINO_D6

//schneider class
#define SCHNEIDER_PIN CONTROLLINO_D7

//wheatstone class - restor bridge
#define L1_SENSE_PIN CONTROLLINO_A0
#define L2_SENSE_PIN CONTROLLINO_A1
#define L3_SENSE_PIN CONTROLLINO_A2

//Falling Tree class
#define CAR_LOCK_PIN  CONTROLLINO_R3
#define UNLATCH_PIN CONTROLLINO_R4

//LEDStripe class:
#define LED_STRIPE_PIN CONTROLLINO_D8

//PwrIndicator class:
#define LED1_PIN CONTROLLINO_D0
#define LED2_PIN CONTROLLINO_D1
#define LED3_PIN CONTROLLINO_D2

//Ground Sensor class
#define GND_SENSOR_PIN  CONTROLLINO_A3

//IP related
#define OWN_IP 10, 200, 20, 151
#define UDP_SERVER_IP 10, 200, 20, 150 //application server f�r e.g. GUI to send status information
#define UDP_SERVER_PORT 5555
#define MAC_ADDRESS { 0xDE, 0xAD, 0xEE, 0xEF, 0xFE, 0xED }
#define LOCAL_UDP_PORT 3333

#endif /* DEFINES_H_ */
