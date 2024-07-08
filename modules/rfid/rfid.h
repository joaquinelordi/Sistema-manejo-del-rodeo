//=====[#include guards - begin]===============================================

#ifndef _RFID_H_
#define _RFID_H_

#define RFID_DEBUG

#include <string>
#include "my_stdlib.h"

//=====[Declaration of public defines]=========================================


#define SPI_MOSI    PA_7    // Azul
#define SPI_MISO    PA_6    // Verde
#define SPI_SCK     PA_5    // Rojo
#define SPI_CS      PA_4    // Marron
#define MF_RESET    PB_4    // Naranja

#define TO_MILISEC 1000 //msec factor
#define BUFFER_SIZE 20      //tamaño del buffer para los ID

//=====[Declaration of public data types]======================================

typedef enum
{
    RFID_IDLE,
    RFID_READING,
    RFID_READ_COMPLETED_VALID_CARD

    } rfidStatus_t;

//=====[Declarations (prototypes) of public functions]=========================


void rfidInit();
void rfidUpdate();
char * rfidReadUID();

//=====[#include guards - end]=================================================

#endif // _RFID_H_
