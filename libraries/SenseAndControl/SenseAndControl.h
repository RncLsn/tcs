#ifndef __SENSECONTROL__
#define __SENSECONTROL__

#include <Arduino.h>
//my modules
#include "tcsUtil.h"
// sensors
#include "OneWire.h"
#include "DallasTemperature.h"

void runSenseAndControl(systemState* _state, sensData* _sensData);

#endif
