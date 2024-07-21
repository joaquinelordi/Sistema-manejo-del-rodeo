//=====[Libraries]=============================================================
#include "mbed.h"
#include "uart_BLE.h"
#include "my_stdlib.h"
#include <cstring>

//=====[Declaration of private defines]========================================

// UART Pins
#define TX PA_9                 // UART Tx pin
#define RX PA_10                // UART Rx pin
#define COM_BAUDRATE 9600       // A CHEQUEAR

#define TO_MILISEC 1000 //msec factor

//=====[Declaration of private data types]=====================================


//=====[Declaration and initialization of public global objects]===============



//=====[Declaration and initialization of private global objects]===============

Serial  uartBLE(TX, RX, COM_BAUDRATE);

static char rxBuffer[BUFFER_RX_SIZE];
static char txBuffer[BUFFER_TX_SIZE];
static volatile int rxIndex = 0;

//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============

//=====[Declaration and initialization of private global variables]============

static uartStatus_t uartState;

//=====[Declarations (prototypes) of private functions]========================

static void comWrite(const char* str);
static bool comRead(char*);
static void uartBLE_isr();

//=====[Implementations of public functions]===================================

void comInit()
{
    printf("comInit -> Inicio \n");
    uartBLE.attach(&uartBLE_isr, Serial::RxIrq);
    uartState = COM_IDLE;
    printf("comInit -> Fin \n");
}

void comUpdate()
{
    //printf("comUpdate -> Inicio \n");

    switch(uartState)
    {
        // no hay nada que hacer
        case RX_READ_COMPLETE:
            printf("No hay nada que leer/enviar");
            uartState = COM_IDLE;
            break;

        // hay algo para transmitir
        case TX_SEND_DATA:

            comWrite(txBuffer);
            uartState = COM_IDLE;
            break;

        // hay algo para leer del buffer
        case RX_BUFFERED:
            printf("Hay datos que leer en el buffer");
            break;   

        case COM_IDLE:
            break;    

    }
    //printf("comUpdate -> Fin \n");

    return;
}

void BLEWrite(const char* str)
{
    my_strcpy(txBuffer, str);
    //Cambio estado a enviar datos
    uartState = TX_SEND_DATA;

}

bool BLERead(char* buffer)
{
    bool ret = false;

    char str[BUFFER_RX_SIZE];
    if (comRead(str))
    {
        my_strcpy(buffer, str);
        ret = true;
    }
    
    return ret;
}

uartStatus_t getStateBLECom()
{
    return uartState;
}

//=====[Implementations of private functions]==================================

static void comWrite(const char* str)
{
    printf("UART escribo: %s", str);
    uartBLE.printf("%s", str);
}

bool comRead(char* str)
{
    //printf("comRead -> Inicio \n");
    if (uartState == RX_BUFFERED)
    {
        my_strcpy(str, rxBuffer);
        uartState = RX_READ_COMPLETE;
        return true;
    }
    return false;
}

// Falta incluir el delay no bloqueante para usar de timeout 
// por si se queda colgado en este método
static void uartBLE_isr()
{
    while (uartBLE.readable()) {
        char c = uartBLE.getc();
        
        if (c == '\n' || rxIndex >= BUFFER_RX_SIZE - 1) {
            rxBuffer[rxIndex] = '\0';
            uartState = RX_BUFFERED;
            rxIndex = 0;
        } else {
            rxBuffer[rxIndex++] = c;
        }

    } 
}