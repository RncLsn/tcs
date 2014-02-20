#include "tcsUtil.h"
// sensors
#include "OneWire.h"
#include "DallasTemperature.h"

#define ANALOG_BASE (14)
#define NUMERICAL_SYSTEM_BASE 10

// radiator-pin mapping
int radiatorPinByRoom(int room) 
{
	/*
	 * 	A0 is referred to as Pin 14
		A1 is referred to as Pin 15
		A2 is referred to as Pin 16
		A3 is referred to as Pin 17
		A4 is referred to as Pin 18
		A5 is referred to as Pin 19
	 * */
	 return ANALOG_BASE + room;
		
}

// function to print a device address
void printAddress(DeviceAddress deviceAddress)
{
  for (uint8_t i = 0; i < 8; i++)
  {
    // zero pad the address if necessary
    if (deviceAddress[i] < 16) Serial.print("0");
    Serial.print(deviceAddress[i], HEX);
  }
}

void ttoa(char *a, double f)
{
	// che zozzata!
	long heiltal = (long)f;
	sprintf(a, "%2d", heiltal);
	while (*a != '\0') a++;
	*a++ = '.';
	long desimal = abs((long)((f - heiltal) * 10));
	sprintf(a, "%1d", desimal);
}
