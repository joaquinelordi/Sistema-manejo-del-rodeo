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

static char rxBuffer[BUFFER_SIZE];
static volatile int rxIndex = 0;

//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============

//=====[Declaration and initialization of private global variables]============

static uartStatus_t uartState;

//=====[Declarations (prototypes) of private functions]========================

static void comWrite(const char* str);
static char* comRead();
static void uartBLE_isr();

//=====[Implementations of public functions]===================================

void comInit()
{
    printf("comInit -> Inicio \n");
    uartBLE.attach(&uartBLE_isr, Serial::RxIrq);
}

void comUpdate()
{
    printf("comUpdate -> Inicio \n");
/*
    switch(uartState)
    {
        // hay algo para transmitir
        case TX_STATUS:
            // espero un tiempo para transmitir
            wait_us(TO_MILISEC * 2000);
            comWrite("AT");

            break;

        case RX_STATUS:
            // hay algo para leer
            char* receivedMsg = comRead();
            if (receivedMsg != NULL)
            {
                printf("UART recibi: [%s]\n", receivedMsg);
                free(receivedMsg); // Liberar la memoria asignada por comRead
            }

            break;    
    }
*/

    return;
}

void BLEWrite(const char * str)
{
    comWrite("Boca Boocaaa \n\n");
}

//=====[Implementations of private functions]==================================

static void comWrite(const char* str)
{
    //  paso a estado quiero transmitir datos
    uartState = TX_STATUS;
    printf("UART escribo: %s", str);
    uartBLE.printf("%s", str);
}

// Falta incluir el delay no bloqueante para usar de timeout 
// por si se queda colgado en este método
bool comRead(char* buffer)
{
    //printf("comRead -> Inicio \n");
    if (uartState == RX_BUFFERED)
    {
        my_strcpy(buffer, rxBuffer);
        uartState = RX_READ_COMPLETE;
        return true;
    }
    return false;
}

static void uartBLE_isr()
{
    while (uartBLE.readable()) {
        char c = uartBLE.getc();
        //printf("char:%c  \n",c);
        
        if (c == '\n' || rxIndex >= BUFFER_SIZE - 1) {
            rxBuffer[rxIndex] = '\0';
            uartState = RX_BUFFERED;
            rxIndex = 0;
        } else {
            rxBuffer[rxIndex++] = c;
        }

    } 
}