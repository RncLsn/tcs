#ifndef __CONFIG__
#define __CONFIG__

// sensors
#include "OneWire.h"
#include "DallasTemperature.h"

// OneWire Buses. The pin numbers where the relays controlling radiators are connected
#define ONE_WIRE_FIRST_BUS 2
#define ONE_WIRE_SECOND_BUS 3



#define DEVADRR_BUS1_NO0 {0x28,0xF9,0xE5,0xB2,0x4,0x0,0x0,0xFA}; // salone
#define DEVADRR_BUS2_NO1 {0x28,0xC1,0x21,0xB3,0x4,0x0,0x0,0x4 }; // bagno grande // sbagliato, sta sul bus 1
#define DEVADRR_BUS2_NO2 {0x28,0x13,0x61,0xB3,0x4,0x0,0x0,0x47};
#define DEVADRR_BUS2_NO0 {0x28,0x78,0x38,0xB3,0x4,0x0,0x0,0x1A}; // bagno piccolo
#define DEVADRR_BUS1_NO1 {0x28,0x13,0x61,0xB3,0x4,0x0,0x0,0x47}; // camera grande
#define DEVADRR_BUS1_NO2 {0x28,0x6C,0x1D,0xB3,0x4,0x0,0x0,0xB7}; // cameretta

typedef unsigned char* DeviceAddress_ptr;

DeviceAddress_ptr getAddressByRoom(int room);

/*
 * 
 * Device 0 Address on the first bus: 	28 6C 1D B3 04 00 00 B7
 * Device 1 Address on the first bus: 	28 C1 21 B3 04 00 00 04
 * Device 2 Address on the first bus: 	28 F9 E5 B2 04 00 00 FA
 * Device 0 Address on the second bus: 	28 78 38 B3 04 00 00 1A
 * Device 1 Address on the second bus: 	28 13 61 B3 04 00 00 47
 * Device 2 Address on the second bus: 	28 27 75 B3 04 00 00 15
 * */

// number of bits used by sensors to store temperature
#define TEMPERATURE_PRECISION 9

// ethernet
#define MAC_ADDR 0x90,0xA2,0xDA,0x0E,0xD7,0xB3 // 90,A2,DA,0E,D7,B3 mac address of the arduino interface
#define IP_ADDR 192, 168, 0, 50
#define PORT_NO 5050 // port number on which connections are received

// keating system config
#define DELTA_TMP 1.00f		// a radiator is turned off at a temperature equals to desiredTemp + DELTA_TEMP
#define ROOMS_NUMBER 6		// number of the rooms where a radiator is present
#define ZONE_VALVE_NUMBER 2	// number of the zone valve
#define DEFAULT_TEMP 17.0f	// default desired temperature
#define ZONE_VALVE_NO1 5	// pin for zone valve #1
#define ZONE_VALVE_NO2 6	// pin for zone valve #2
#endif
