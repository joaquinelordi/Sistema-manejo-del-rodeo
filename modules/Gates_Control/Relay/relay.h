//=====[#include guards - begin]===============================================

#ifndef _RELAY_H_
#define _RELAY_H_

#include "mbed.h"

//=====[Declaration of public defines]=========================================

// Nucleo Pin for Relay-2CH
#define IN_1        PA_1
#define IN_2        PA_0

//=====[Declaration of public data types]======================================

typedef enum{
    RELAY_ON,
    RELAY_OFF
} relayStatus_t;

//=====[Declarations (prototypes) of public functions]=========================

void relayInit();
void relayUpdate();
void relayON();
void relayOFF();

//=====[#include guards - end]=================================================

#endif // _RELAY_H_