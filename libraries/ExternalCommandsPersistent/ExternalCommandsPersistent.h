#ifndef __EXTCMDP__
#define __EXTCMDP__

#include <Arduino.h>
// ethernet
#include <Ethernet.h>
//~ #include <EthernetServer.h>
//~ #include <Ethernet2.h>
// my modules
#include "tcsUtil.h"

void runExternalCommandsPersistent(EthernetServer* _server, systemState* _state);

#endif
