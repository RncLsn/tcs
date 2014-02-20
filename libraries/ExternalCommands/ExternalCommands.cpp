#include "ExternalCommands.h"

#include <Arduino.h>
// ethernet
#include <Ethernet.h>
//~ #include <EthernetServer.h>
//~ #include <Ethernet2.h>

// my modules
#include "tcsUtil.h"

int readParam(char* buffer, int size, EthernetClient client);

void runExternalCommands(EthernetServer* _server, systemState* _state) 
{
	// local variables
	int i, buffer_ptr;
	int room, radiatorState, automaticMode;
	float temperature;
	
	
	EthernetClient client = _server->available(); // is non-blocking
	if(client.available() > 2)
	{
		#ifdef DEBUG
		Serial.println("Connection established");
		#endif
		
		char buffer[32];
		
		// read command field
		readParam(buffer, 3, client);
		
		// switch case on commands
		if(strcmp(buffer, "STM") == 0) // set temperature
		{
			#ifdef DEBUG
			Serial.println("Set temperature command received");
			#endif
			
			// read fisrt param: room number (one digit)
			readParam(buffer, 1, client);
			room = atoi(buffer);
			
			// read second param: temperature (format xx.y)
			readParam(buffer, 4, client);
			temperature = atof(buffer);
			
			_state->desiredTemp[room] = temperature;
			
			client.write((unsigned char*)"STM", 3);
			client.write((unsigned char*)"OOK", 3);
		}
		else if(strcmp(buffer, "RTM") == 0) // read temperature
		{
			#ifdef DEBUG
			Serial.println("Read temperature command received");
			#endif
			// read fisrt param: room number (one digit)
			readParam(buffer, 1, client);
			
			room = atoi(buffer);
			
			temperature = _state->actualTemp[room];
			//buffer_ptr = sprintf(buffer, "%4.1f", temperature);
			ttoa(buffer, temperature);
			
			client.write((unsigned char*)"RTM", 3);
			client.write((unsigned char*)"OOK", 3);
			client.write((unsigned char*)buffer, 4);
		}
		else if(strcmp(buffer, "SRD") == 0) // set radiator
		{
			#ifdef DEBUG
			Serial.println("Set radiator command received");
			#endif
			// read fisrt param: room number (one digit)
			readParam(buffer, 1, client);
			room = atoi(buffer);
			
			// read second param: radiator state (one digit)
			readParam(buffer, 1, client);
			radiatorState = atoi(buffer);
			
			_state->radiatorState[room] = radiatorState;
			
			client.write((unsigned char*)"SRD", 3);
			client.write((unsigned char*)"OOK", 3);
		}
		else if(strcmp(buffer, "RRD") == 0) // read radiator
		{
			#ifdef DEBUG
			Serial.println("Read radiator command received");
			#endif
			// read fisrt param: room number (one digit)
			readParam(buffer, 1, client);
			room = atoi(buffer);

			radiatorState = _state->radiatorState[room];
			sprintf(buffer, "%d", radiatorState);
			
			client.write((unsigned char*)"RRD", 3);
			client.write((unsigned char*)"OOK", 3);
			client.write((unsigned char*)buffer, 1);
		}
		else if(strcmp(buffer, "SAM") == 0) // set automatic mode
		{
			#ifdef DEBUG
			Serial.println("Set automatic mode command received");
			#endif
			// read second param: radiator state (one digit)
			readParam(buffer, 1, client);
			automaticMode = atoi(buffer);
			
			_state->automaticMode = automaticMode;
			
			client.write((unsigned char*)"SAM", 3);
			client.write((unsigned char*)"OOK", 3);
		}
		else if(strcmp(buffer, "RAM") == 0) // read automatic mode
		{
			#ifdef DEBUG
			Serial.println("Read automatic mode command received");
			#endif
			automaticMode = _state->automaticMode;
			
			sprintf(buffer, "%d", automaticMode);
			
			client.write((unsigned char*)"RAM", 3);
			client.write((unsigned char*)"OOK", 3);
			client.write((unsigned char*)buffer, 1);
		}
		else if(strcmp(buffer, "RDT") == 0) // read desired temperature
		{
			#ifdef DEBUG
			Serial.println("Read desired temperature command received");
			#endif
			// read fisrt param: room number (one digit)
			readParam(buffer, 1, client);
			room = atoi(buffer);
			
			temperature = _state->desiredTemp[room];
			//buffer_ptr = sprintf(buffer, "%4.1f", temperature);
			ttoa(buffer, temperature);
			
			client.write((unsigned char*)"RDT", 3);
			client.write((unsigned char*)"OOK", 3);
			client.write((unsigned char*)buffer, 4);
		}
		else // invalid command
		{
			#ifdef DEBUG
			Serial.println("Invalid command received");
			#endif
			client.write((unsigned char*)"ERR", 3);
			client.write((unsigned char*)"ERR", 3);
		}
		//~ client.flush(); // NEW to verify ---> it seems not working
		//~ delay(2000);
		
		while(client.connected())
		{
			client.stop();
			//delay(1000);
		}
	}
	
}

/* the function reads 'size' bytes from the 'client' 
 * and store them into the 'buffer'. 
 * It is useful to read parameters sent from client
 * */
int readParam(char* buffer, int size, EthernetClient client)
{
	/* TODO return error code if received bytes are less than 'size' */
	int i, buffer_ptr = 0;
	for(i = 0; i < size; i++)
	{
		if(client.available()) buffer[buffer_ptr++] = client.read();
		else return -1;
	}
	buffer[buffer_ptr++] = NULL;
	return 0;
}
