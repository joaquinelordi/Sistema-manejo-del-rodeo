//=====[#include guards - begin]===============================================

#ifndef _UART_BLE_H_
#define _UART_BLE_H_

#include "mbed.h"

//=====[Declaration of public defines]=========================================

#define BUFFER_TX_SIZE 32
#define BUFFER_RX_SIZE 32

//=====[Declaration of public data types]======================================
typedef enum{
    TX_SEND_DATA,
    RX_BUFFERED,
    RX_READ_COMPLETE,
    
    
} uartStatus_t;

//=====[Declarations (prototypes) of public functions]=========================

void comInit();

void comUpdate();

void BLEWrite(const char *);

bool BLERead(char *);

uartStatus_t getStateBLECom();


//=====[#include guards - end]=================================================

#endif // _UART_MODULE_H_