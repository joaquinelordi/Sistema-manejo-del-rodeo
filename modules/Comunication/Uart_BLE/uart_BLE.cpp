//=====[Libraries]=============================================================
#include "mbed.h"
#include "uart_BLE.h"
#include "my_stdlib.h"
#include <queue>
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

// Cola para almacenar caracteres leídos
std::queue<char> rxBuffer;

//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============

//=====[Declaration and initialization of private global variables]============

static uartStatus_t uartState;

//=====[Declarations (prototypes) of private functions]========================

static void comWrite(const char* str);
static char* comRead();
static void rxBuffer_isr();

//=====[Implementations of public functions]===================================

void comInit()
{
    printf("comInit -> Inicio \n");
    //uartBLE.attach(&rxBuffer_isr, Serial::RxIrq);
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
    comWrite("Boca Boocaaa");
}

//=====[Implementations of private functions]==================================

static void comWrite(const char* str)
{
    //  paso a estado quiero transmitir datos
    uartState = TX_STATUS;
    printf("UART escribo: %s\n", str);
    uartBLE.printf("%s", str);
}

// Falta incluir el delay no bloqueante para usar de timeout 
// por si se queda colgado en este método
static char* comRead()
{
    char c;
    std::queue<char> localBuffer;

    // Transferir datos del buffer global al buffer local
    while (!rxBuffer.empty())
    {
        c = rxBuffer.front();
        rxBuffer.pop();
        localBuffer.push(c);
        if (c == '\0')
        {
            break;
        }
    }

    // Calcular la longitud del mensaje
    int length = localBuffer.size();
    if (length == 0)
    {
        return NULL;
    }

    // Asignar memoria para el mensaje
    char* sBuffer = (char*)malloc(length + 1);
    if (sBuffer == NULL)
    {
        return NULL;
    }

    // Copiar el mensaje desde el buffer local a la cadena
    for (int i = 0; i < length; i++)
    {
        sBuffer[i] = localBuffer.front();
        localBuffer.pop();
    }
    sBuffer[length] = '\0';

    //  paso a modo recibi datos
    uartState = RX_STATUS;

    return sBuffer;
}

static void rxBuffer_isr()
{
    while (uartBLE.readable())
    {
        printf("UART leyendo datos\n");
        rxBuffer.push(uartBLE.getc());
    }
}