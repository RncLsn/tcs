#ifndef __SETUP_ACTIVITY__
#define __SETUP_ACTIVITY__
#include <Arduino.h>
#include <Ethernet.h>
//~ #include <EthernetServer.h>
//~ #include <Ethernet2.h>
#include "Config.h"

// temperature
#include "OneWire.h"
#include "DallasTemperature.h"

#include "tcsUtil.h"

void runSetupActivity(sensData** sd, EthernetServer** server, systemState** ss);

#endif
