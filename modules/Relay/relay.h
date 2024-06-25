//=====[#include guards - begin]===============================================

#ifndef _RELAY_H_
#define _RELAY_H_

#include "mbed.h"

//=====[Declaration of public defines]=========================================



//=====[Declaration of public data types]======================================

// Nucleo Pin for Relay-2CH
#define IN_1        PA_9
#define IN_2        PA_10

//=====[Declarations (prototypes) of public functions]=========================

void relayInit();
void relayUpdate();


//=====[#include guards - end]=================================================

#endif // _RELAY_H_