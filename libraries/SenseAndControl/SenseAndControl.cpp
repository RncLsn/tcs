#include "SenseAndControl.h"

#include <Arduino.h>
// my modules
#include "tcsUtil.h"
// sensors
#include "OneWire.h"
#include "DallasTemperature.h"

static unsigned int time1 = 0;
static unsigned int time2 = 0;

#define SQRT_INTERVAL 256 // 512, integers are represented in 2 bytes

void runSenseAndControl(systemState* _state, sensData* _sensData)
{
	/* TODO time interval */
	
	// local variables
	unsigned char room;
	float temp;
	
	if(time1++ == SQRT_INTERVAL)
	{
		time1 = 0;
		if(time2++ == SQRT_INTERVAL)
		{
			time2 = 0;
					
			_sensData->sensors_bus1->requestTemperatures();
			_sensData->sensors_bus2->requestTemperatures();
	
			for(room = 0; room < 6; room++)
			{
	
				// read sensor
				if(room < 3)
				{	
					Serial.println("Read sensors");
					temp = _sensData->sensors_bus1->getTempC(getAddressByRoom(room));
					if(temp > 0 && temp < 50) _state->actualTemp[room] = temp;
				}
				else
				{
		 			temp = _sensData->sensors_bus2->getTempC(getAddressByRoom(room));
					if(temp > 0 && temp < 50) _state->actualTemp[room] = temp;
				}
				
				// store temperature
				#ifdef DEBUG
				Serial.print("Control temperature for room n.");
				Serial.println(room);
				Serial.print("\tMeasured temperature: ");
				Serial.println(_state->actualTemp[room]);
				Serial.print("\tDesired temperature: ");
				Serial.println(_state->desiredTemp[room]);
				#endif
			}
		}
	}
	
	if(_state->automaticMode == ON)
	{	
		//Serial.println("Sense and control: automatic mode");
		for(room = 0; room < 6; room++)
		{
			//Serial.print("room");
			//Serial.println(room);
			// check temperature
			if(_state->radiatorState[room] == OFF) // radiator is OFF
			{
				//Serial.println("Sense and control: check 1");
				if(_state->actualTemp[room] <= _state->desiredTemp[room])
				{	
					//Serial.println("Sense and control: check 2");
					// set the radiator state (both in systemState and on pin)
					_state->radiatorState[room] = ON;
					digitalWrite(radiatorPinByRoom(room), LOW);
				}
			}
			else // radiator is ON
			{
				if(_state->actualTemp[room] > _state->desiredTemp[room] + DELTA_TMP)
				{
					// set the radiator state (both in systemState and on pin)
					_state->radiatorState[room] = OFF;
					digitalWrite(radiatorPinByRoom(room), HIGH);
				}
			}
			
			#ifdef DEBUG
			Serial.print("\tRadiator is ");
			if(_state->radiatorState[room] == OFF) 	Serial.println("OFF");
			else 									Serial.println("ON");
			#endif
			
			// to delete
			/*
			// set zone valve
			int someoneIsOn = 0;
			for(room = 0; room < 6; room++) 
			{
				if(_state->radiatorState[room] == ON) someoneIsOn = 1;
			}
			if(someoneIsOn == 1)	digitalWrite(ZONE_VALVE_NO1, LOW); // that means ON
			else 					digitalWrite(ZONE_VALVE_NO1, HIGH); // that means OFF
			*/
		}
	}
}
