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

//RELAY DEBERIA SER UNA CLASE, que se inicialize con el pin asociado
void relayInit();
void relayUpdate();
void relay_1_ON();
void relay_1_OFF();
void relay_2_ON();
void relay_2_OFF();

//=====[#include guards - end]=================================================

#endif // _RELAY_H_