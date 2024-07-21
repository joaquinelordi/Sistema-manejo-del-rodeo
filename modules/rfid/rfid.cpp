//=====[Libraries]=============================================================
#include "mbed.h"
#include "rfid.h"
#include "relay.h"
#include "MFRC522.h"
#include <string.h>

//=====[Declaration of private defines]========================================


//=====[Declaration of private data types]=====================================

//=====[Declaration and initialization of public global objects]===============



//=====[Declaration and initialization of private global objects]===============

MFRC522    RfChip   (SPI_MOSI, SPI_MISO, SPI_SCK, SPI_CS, MF_RESET);
#ifdef RFID_DEBUG
DigitalOut LedGreen(LED1);
#endif //RFID_DEBUG

//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============

//=====[Declaration and initialization of private global variables]============

static char rfidBuffer[BUFFER_SIZE] = {'\0'};
static rfidStatus_t rfidStatus;

//=====[Implementations of public functions]===================================

void rfidInit()
{
    printf("RFID Init starting...\r\n");
    RfChip.PCD_Init();
    rfidStatus  = RFID_READING;
    printf("init passed\r\n");
}

void rfidUpdate()
{
    //printf("rfidUpdate() -> Inicio \n");

    switch(rfidStatus)
    {

        case RFID_IDLE:
            if (RfChip.PICC_IsNewCardPresent())
                rfidStatus = RFID_READING;

            else
            {
                //printf("rfid IDLE: No lei ninguna tarjeta\r\n"); 
            }
            break;

        case RFID_READING:
            if (RfChip.PICC_IsNewCardPresent())
            {
                // lei una tarjeta valida
                if (RfChip.PICC_ReadCardSerial())
                {
                    // Print Card UID
                    //printf("Card UID: ");
                    for (uint8_t i = 0; i < RfChip.uid.size; i++)
                    {
                        sprintf(rfidBuffer + i * 2, "%02X", RfChip.uid.uidByte[i]);
                    }
                    // termino la cadena con un \0
                    rfidBuffer[RfChip.uid.size * 2] = '\0';
                    printf("Buffer[%s]\n", rfidBuffer);
                    
                    // Print Card type
                    uint8_t piccType = RfChip.PICC_GetType(RfChip.uid.sak);
                    printf("PICC Type: %s \n\r", RfChip.PICC_GetTypeName(piccType));

                    // proceso la tarjeta y luego cambio el estado
                    rfidStatus = RFID_READ_COMPLETED_VALID_CARD;
                }
                else
                {
                    //printf("card is reading\r\n");
                }

            }
            break;

        case RFID_READ_COMPLETED_VALID_CARD:

            //printf("Tarjeta leida, esperando ser procesada\r\n");
                
            break;    

    
    }

    //printf("rfidUpdate() -> Fin \n");
}

char* rfidReadUID()
{

    if (rfidStatus != RFID_READ_COMPLETED_VALID_CARD)
    {
        //printf("rfidReadUID() -> estado invalido \n");
        return NULL;
    }

    // Reservar memoria para la cadena UID
    char* aux = (char*)malloc(my_strlen(rfidBuffer) + 1);
    if (aux == NULL)
    {
        //printf("rfidReadUID() -> Memory allocation failed\n");
        return NULL;
    }

    // Copiar el contenido de buffer al puntero auxiliar
    my_strcpy(aux, rfidBuffer);

    // Mostrar el resultado en la consola
    //printf("rfidReadUID() -> UID: %s\n", buffer);
    //printf("rfidReadUID() -> Aux: %s\n", aux);
    
    // Limpiar el buffer
    memset(rfidBuffer, 0, sizeof(rfidBuffer));
    
    //printf("rfidReadUID() -> RelayON \n");

    rfidStatus = RFID_READING; // Ya procesé el UID ingresado, espero que se lea

    return aux;
}

/* PARA PROBAR LA ACTIVACION DEL RELAY 

    relayON();
    relayUpdate();
    wait_us(TO_MILISEC * 1500);

    printf("rfidReadUID() -> RelayOFF \n");
    
    relayOFF();
    relayUpdate();
*/