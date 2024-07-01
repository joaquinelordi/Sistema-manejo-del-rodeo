//=====[#include guards - begin]===============================================

#ifndef _UART_BLE_H_
#define _UART_BLE_H_

#include "mbed.h"

//=====[Declaration of public defines]=========================================



//=====[Declaration of public data types]======================================

typedef enum{
    TX_STATUS,
    RX_STATUS
} uartStatus_t;

//=====[Declarations (prototypes) of public functions]=========================

void comInit();

void comUpdate();

void BLEWrite(const char *);

//=====[#include guards - end]=================================================

#endif // _UART_MODULE_H_