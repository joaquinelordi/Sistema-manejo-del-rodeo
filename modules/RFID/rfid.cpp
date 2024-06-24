//=====[Libraries]=============================================================
#include "mbed.h"
#include "rfid.h"
#include "MFRC522.h"
#include "string.h"

//=====[Declaration of private defines]========================================

//=====[Declaration of private data types]=====================================

//=====[Declaration and initialization of public global objects]===============

MFRC522    RfChip   (SPI_MOSI, SPI_MISO, SPI_SCK, SPI_CS, MF_RESET);
#ifdef RFID_DEBUG
DigitalOut LedGreen(LED1);
#endif //RFID_DEBUG

//=====[Declaration and initialization of private global objects]===============

//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============

//=====[Declaration and initialization of private global variables]============

static char buffer[BUFFER_SIZE] = {'\0'};
static string str;

static rfidStatus_t rfidStatus;

//=====[Implementations of public functions]===================================

void rfidInit()
{
    // Init. RC522 Chip
    printf("RFID Init starting...\r\n");
    RfChip.PCD_Init();
    rfidStatus  = RFID_IDLE;
    printf("init passed\r\n");
}

void rfidUpdate()
{
    // hay una tarjeta presente
    if (RfChip.PICC_IsNewCardPresent())
    {
        //lei una tarjeta valida
        if (RfChip.PICC_ReadCardSerial())
        {
            rfidStatus = RFID_READ_COMPLETED_VALID_CARD;
            // Print Card UID
            printf("Card UID: ");
            for (uint8_t i = 0; i < RfChip.uid.size; i++)
            {
                sprintf(buffer+i*2,"%02X", RfChip.uid.uidByte[i]);
                
            }
            printf("%s\n",buffer);
            
            // Print Card type
            uint8_t piccType = RfChip.PICC_GetType(RfChip.uid.sak);
            printf("PICC Type: %s \n\r", RfChip.PICC_GetTypeName(piccType));
        }
        // todavia no esta la lectura completada
        else
        {
            rfidStatus = RFID_READING;
            printf("card is reading\r\n");
            //wait_us( TO_MILISEC * 500); 
        }
    }
    else
    {
        printf("No lei ninguna tarjeta\r\n"); 
        rfidStatus  = RFID_IDLE;
    }


}

char * rfidReadUID()
{
    if(rfidStatus != RFID_READ_COMPLETED_VALID_CARD)
        return NULL;

    char* aux=strndup(buffer,10);
    buffer[0]={'\0'};
    rfidStatus=RFID_IDLE;//Ya procese el uid ingresado a si que vuelvo a modo de esepra
    return aux;
}