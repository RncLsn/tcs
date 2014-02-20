#include "SetupActivity.h"

#include <Arduino.h>
#include <string.h>
// ethernet
#include <Ethernet.h>
#include <EthernetServer.h>
//~ #include <Ethernet2.h>
// my modules
#include "tcsUtil.h"
#include "Config.h"
// sensors
#include "OneWire.h"
#include "DallasTemperature.h"

// #define DEBUG_SETUP
#ifdef DEBUG_SETUP
	#ifndef DEBUG
	#define DEBUG
	#endif
#endif



void runSetupActivity(sensData** sd, EthernetServer** server, systemState** ss) 
{
	// local variables
	int room;
	
	#ifdef DEBUG
	/* *** serial port *** */
	Serial.begin(9600);
	#endif
	
	// /* *** structures initialization *** */
	#ifdef DEBUG_SETUP
	Serial.print("Initializing data structures...");
	#endif
	
	EthernetServer* _server = *server = new EthernetServer(PORT_NO);
	
	sensData* _sd = *sd = (sensData*) malloc(sizeof(sensData));
	
	systemState* _state = *ss = (systemState*) malloc(sizeof(systemState));
	_state->automaticMode = OFF;
	for(room = 0; room < ROOMS_NUMBER; room++) _state->desiredTemp[room] = DEFAULT_TEMP;
	for(room = 0; room < ROOMS_NUMBER; room++) _state->radiatorState[room] = OFF;
	for(room = 0; room < ROOMS_NUMBER; room++) _state->actualTemp[room] = 0;
	for(room = 0; room < ZONE_VALVE_NUMBER; room++) _state->zoneValve[room] = OFF;
	
	#ifdef DEBUG_SETUP
	Serial.println("done");
	#endif
	
	/* *** temperature sensors *** */
	_sd->oneWire_bus1 = new OneWire(ONE_WIRE_FIRST_BUS);
	_sd->oneWire_bus2 = new OneWire(ONE_WIRE_SECOND_BUS);
	_sd->sensors_bus1 = new DallasTemperature(_sd->oneWire_bus1);
	_sd->sensors_bus2 = new DallasTemperature(_sd->oneWire_bus2);
	
	// start up the library
	_sd->sensors_bus1->begin();
	_sd->sensors_bus2->begin();
	
	#ifdef DEBUG_SETUP
	// locate devices on the bus
	Serial.print("Locating devices...");
	Serial.print("Found ");
	Serial.print(_sd->sensors_bus1->getDeviceCount(), DEC);
	Serial.print(" devices on the first bus and ");
	Serial.print(_sd->sensors_bus2->getDeviceCount(), DEC);
	Serial.println(" devices on the second bus.");
	#endif
	
	// set the resolution to 9 bit
	_sd->sensors_bus1->setResolution(getAddressByRoom(0), TEMPERATURE_PRECISION);
	_sd->sensors_bus1->setResolution(getAddressByRoom(1), TEMPERATURE_PRECISION);
	_sd->sensors_bus1->setResolution(getAddressByRoom(2), TEMPERATURE_PRECISION);
	_sd->sensors_bus2->setResolution(getAddressByRoom(3), TEMPERATURE_PRECISION);
	_sd->sensors_bus2->setResolution(getAddressByRoom(4), TEMPERATURE_PRECISION);
	_sd->sensors_bus2->setResolution(getAddressByRoom(5), TEMPERATURE_PRECISION);
	
	#ifdef DEBUG_SETUP
	Serial.print("Device 0 Resolution on the first bus: ");
	Serial.print(_sd->sensors_bus1->getResolution(getAddressByRoom(0)), DEC); 
	Serial.println();
	
	Serial.print("Device 1 Resolution on the first bus: ");
	Serial.print(_sd->sensors_bus1->getResolution(getAddressByRoom(1)), DEC); 
	Serial.println();
	
	Serial.print("Device 2 Resolution on the first bus: ");
	Serial.print(_sd->sensors_bus1->getResolution(getAddressByRoom(2)), DEC); 
	Serial.println();
	
	Serial.print("Device 0 Resolution on the second bus: ");
	Serial.print(_sd->sensors_bus2->getResolution(getAddressByRoom(3)), DEC); 
	Serial.println();
	
	Serial.print("Device 1 Resolution on the second bus: ");
	Serial.print(_sd->sensors_bus2->getResolution(getAddressByRoom(4)), DEC); 
	Serial.println();
	
	Serial.print("Device 2 Resolution on the second bus: ");
	Serial.print(_sd->sensors_bus2->getResolution(getAddressByRoom(5)), DEC); 
	Serial.println();
	#endif
	
	#ifdef DEBUG_SETUP
	// test temperature sensing
	_sd->sensors_bus1->requestTemperatures();
	_sd->sensors_bus2->requestTemperatures();
	
	float tempC;
	for(room = 0; room < 6; room++)
	{
		if(room < 3) 	tempC = _sd->sensors_bus1->getTempC(getAddressByRoom(room));
		else 			tempC = _sd->sensors_bus2->getTempC(getAddressByRoom(room));
		Serial.print("Temp in the room n.");
		Serial.print(room);
		Serial.print(" is ");
		Serial.print(tempC);
		Serial.println(" C");
	}
	#endif
	
	/* *** initialize system state *** */
	
	/* *** ethernet *** */
	#ifdef DEBUG_SETUP
	Serial.print("Initializing ethernet interface...");
	#endif
	byte mac[] = 	{MAC_ADDR};
	byte ip[]  =  	{IP_ADDR};
	//~ IPAddress ip(IP_ADDR);
	byte dns[]  =  	{8, 8, 8, 8};
	byte gateway[]= {192, 168, 0, 1};
	byte subnet[] = {255, 255, 255, 0};
	//~ Ethernet.begin(mac, ip, dns, gateway, subnet); 
	//~ Ethernet.begin(mac, ip);
	//~ Ethernet.begin(mac);
	
	// attempt a DHCP connection:
	if (!Ethernet.begin(mac)) {
		Serial.print(" DHCP request failed.. assign static address");
		// if DHCP fails, start with a hard-coded address:
		Ethernet.begin(mac, ip);
	}
	
	_server->begin();
	#ifdef DEBUG_SETUP
	Serial.println("done");
	Serial.print("Local IP address: ");
	Serial.println(Ethernet.localIP());
	#endif
	
	/* *** radiators *** */
	#ifdef DEBUG_SETUP
	Serial.print("Initializing pins...");
	#endif
	for(room = 0; room < ROOMS_NUMBER; room++)
	{
		pinMode(radiatorPinByRoom(room), OUTPUT);
		digitalWrite(radiatorPinByRoom(room), HIGH);	//	relays work in negative logic
	}
	
	pinMode(ZONE_VALVE_NO1, OUTPUT);
	digitalWrite(ZONE_VALVE_NO1, HIGH);
	pinMode(ZONE_VALVE_NO2, OUTPUT);
	digitalWrite(ZONE_VALVE_NO2, HIGH);
	
	#ifdef DEBUG_SETUP
	Serial.println("done");
	#endif
}
