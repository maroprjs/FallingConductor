
/**
 *  @file		FallingConductor.ino
 *
 *  @author		maro
 *  @date		mm/dd/yyyy
 *  @version	x.y
 *
 *  @brief 		Main
 *
 *  @section DESCRIPTION
 *
 *  Instantiation and control of objects integrated in Conveyor IND21
 *
 */

/////////// Includes /////////////////
#include "Arduino.h"
#include <Controllino.h>
#include "Defines.h"
#include "Modem.h"
#include "Flash.h"
#include "Fire.h"
#include "Schneider.h"
#include "Wheatstone.h"
#include "Tree.h"
#include "LEDStripe.h"
#include "PwrIndicator.h"
#include "GroundSensor.h"
#include "UI.h"

/////////defines //////////////////////

//defines moved to ConveyorDefines.h

////////// Object Instantiation //////////////////
/*************************************************************
 * modem - local MMI represented by serial interface, WebUI by server IP and port
 */
IPAddress udpServerIP(UDP_SERVER_IP);
IPAddress ownIP(OWN_IP);
uint16_t udpServerPort = UDP_SERVER_PORT;

Modem modem(&Serial, udpServerIP, udpServerPort, ownIP);

/*************************************************************
 * Flash - controls the three flashing light for Flash-animation when cabvle hits the ground
 */
Flash flash;

/*************************************************************
 * Fire - controls the Firebulbs
 */
Fire fire;

/*************************************************************
 * LEDStripe - status about the schneider circuit breaker
 */
LEDStripe ledStripe;

/*************************************************************
 * Schneider - Circuit Breaker/Recloser
 */
Schneider schneider(&ledStripe);


/*************************************************************
 * PwrIndicator- the three LEDs, which show if there is electricity or not
 */
PwrIndicator pwrIndicator;

/*************************************************************
 * Wheatstone - resistor bridge to sense shortcuts and cable loss
 */
Wheatstone wheatstone(&schneider, &pwrIndicator);


/*************************************************************
 * Tree - the falling tree triggers the car lock and the cable unlatch
 */
Tree tree;



/*************************************************************
 * GroundSensor -
 */

GroundSensor gndSensor(&fire, &flash);


/*************************************************************
 * UI - serial and UDP
 */
UI ui(&modem,&flash, &fire, &wheatstone, &tree);

void setup()
{
	Serial.begin(9600);
	delay(100);
	modem.begin();
	flash.begin();
	fire.begin();
	schneider.begin();
	wheatstone.begin();
	tree.begin();
	ledStripe.begin();
	pwrIndicator.begin();
	gndSensor.begin();
	ui.begin();


}


void loop()
{
	 modem.loop();
	 wheatstone.loop();
	 tree.loop();
	 schneider.loop();
	 flash.loop();
	 ledStripe.loop();
	 gndSensor.loop();
	 ui.loop();
}
