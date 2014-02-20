 /*
  Temeperature Control System - Arduino sketch
  
  This sketch reads temperature sensors, it sets relays ON/OFF (the relays control radiators)
  in order to control rooms temperature.  
  It provides APIs accessible from network.
*/


#include <Arduino.h>

// ethernet
#include <SPI.h>
#include "Ethernet.h"
//#include "EthernetServer.h"
//#include "Ethernet2.h"

// temperature
#include "OneWire.h"
#include "DallasTemperature.h"

// my modules
#include "SetupActivity.h"
//#include "ExternalCommands.h"
#include "ExternalCommandsPersistent.h"
#include "SenseAndControl.h"
#include "Config.h"
#include "tcsUtil.h"

sensData* sd;
EthernetServer* server;
systemState* state;

void setup() {
  runSetupActivity(&sd, &server, &state);
}

void loop() {
  runExternalCommandsPersistent(server, state);
  runSenseAndControl(state, sd);
}
