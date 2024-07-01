//=====[Libraries]=============================================================
#include "mbed.h"
#include "relay.h"
#include "my_stdlib.h"
#include <string.h>
#include "arm_book_lib.h"

//=====[Declaration of private defines]========================================

//=====[Declaration of private data types]=====================================

//=====[Declaration and initialization of public global objects]===============


#ifdef RELAY_DEBUG
DigitalOut LedGreen(LED1);
#endif //RFID_DEBUG

//=====[Declaration and initialization of private global objects]===============

//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============

DigitalInOut RelayIn1(IN_1);
DigitalInOut RelayIn2(IN_2);

//=====[Declaration and initialization of private global variables]============

static relayStatus_t relayStatus;

//=====[Implementations of public functions]===================================

void relayInit()
{
    // Relay Init: OpenDrain y como entrada es alta impedancia = apagado
    relayStatus = RELAY_OFF;
    RelayIn1.mode(OpenDrain);
    RelayIn1.input();
    RelayIn2.mode(OpenDrain);
    RelayIn2.input();

    return;
}

// Debe modificar el estado de los reles en funcion del estado del control en las puertas
void relayUpdate()
{
    switch (relayStatus)
    {
        case RELAY_ON:
            RelayIn1.output();                                     
            RelayIn1 = LOW;    
            //RelayIn2.output();
            //RelayIn2 = LOW;
            
            break;

        case RELAY_OFF:
    
            RelayIn1.input();
            //RelayIn2.input();

            break;
      
    }

}

void relayON()
{
    relayStatus = RELAY_ON;
}

void relayOFF()
{
    relayStatus = RELAY_OFF;
}