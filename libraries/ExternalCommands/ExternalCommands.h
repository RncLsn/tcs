#ifndef __EXTCMD__
#define __EXTCMD__

#include <Arduino.h>
// ethernet
#include <Ethernet.h>
//~ #include <EthernetServer.h>
//~ #include <Ethernet2.h>
// my modules
#include "tcsUtil.h"

void runExternalCommands(EthernetServer* _server, systemState* _state);

#endif
