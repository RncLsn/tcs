#ifndef __TCS_UTIL__
#define __TCS_UTIL__

// sensors
#include <OneWire.h>
#include <DallasTemperature.h>
// watchdog timer for reset
#include <avr/io.h>
#include <avr/wdt.h>
// my moduels
#include "Config.h"
// sensors
#include "OneWire.h"
#include "DallasTemperature.h"

typedef struct sensData
{
	OneWire*				oneWire_bus1;
	OneWire*				oneWire_bus2;
	DallasTemperature*		sensors_bus1;
	DallasTemperature*		sensors_bus2;
	//~ DeviceAddress			addresses_bus1[3] = { DEVADRR_BUS1_NO0, DEVADRR_BUS1_NO1, DEVADRR_BUS1_NO2 };
	//~ DeviceAddress			addresses_bus2[3] = { DEVADRR_BUS2_NO0, DEVADRR_BUS2_NO1, DEVADRR_BUS2_NO2 };
} sensData;

typedef struct systemState
{
	float 	actualTemp[ROOMS_NUMBER];
	float 	desiredTemp[ROOMS_NUMBER];
	int		automaticMode;
	int		radiatorState[ROOMS_NUMBER];
	int 	zoneValve[ZONE_VALVE_NUMBER];
} systemState;

#define RESET() do{wdt_enable(WDTO_30MS); while(1) {};}while(0);

int radiatorPinByRoom(int room);

void printAddress(DeviceAddress deviceAddress);

void ttoa(char *a, double f); // converts float to string, side-effect

#define OFF 0
#define ON 1

//#define DEBUG

#endif
