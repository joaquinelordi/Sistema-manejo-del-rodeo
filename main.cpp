/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

/* EJEMPLO ORIGINAL DEL REPOSITORIO
    #define TO_MILISEC 1000 //msec factor

DigitalOut led1(LED1);

int main()
{
    while (true)
    {
        led1 = !led1;
        wait_us(TO_MILISEC * 500);
    }
}
*/


#include "mbed.h"
#include "MFRC522.h"

#define TO_MILISEC 1000 //msec factor

#define SPI_SCK     PA_5    // Rojo
#define SPI_CS      PA_4    // Marron
#define SPI_MISO    PA_6    // Verde
#define SPI_MOSI    PA_7    // Azul
#define MF_RESET    PB_4    // Naranja

// Nucleo Pin for Relay-2CH
#define IN_1        PF_12
#define IN_2        PF_13

MFRC522    RfChip   (SPI_MOSI, SPI_MISO, SPI_SCK, SPI_CS, MF_RESET);
DigitalOut LedGreen(LED1);

//DigitalInOut RelayIn1(PF_12);
//DigitalInOut RelayIn2(PF_13);

int main()
{
    // Relay Init OpenDrain y como entrada es alta impedancia = apagado
    /*
    RelayIn1.mode(OpenDrain);
    RelayIn1.input();
    RelayIn2.mode(OpenDrain);
    RelayIn2.input();
    */
    printf("starting...\r\n");

    // Init. RC522 Chip
    RfChip.PCD_Init();

    printf("init passed\r\n");


    while (true) {
        LedGreen = 1;


        // Look for new cards
        if ( ! RfChip.PICC_IsNewCardPresent())
        {
            wait_us(TO_MILISEC * 500);
            // Relay OFF
            //RelayIn1.input();
            //RelayIn2.input();
            printf("No lei ninguna tarjeta\r\n");            
            continue;
        }

        // Select one of the cards
        if (!RfChip.PICC_ReadCardSerial())
        {
            wait_us( TO_MILISEC * 500);
            printf("card read\r\n");
            
            continue;
        }

        LedGreen = 0;
        // Relay ON
        /*
        RelayIn1.output();                                     
        RelayIn1 = LOW;    
        RelayIn1.output();
        RelayIn2 = LOW;
        */

        // Print Card UID
        printf("Card UID: ");
        for (uint8_t i = 0; i < RfChip.uid.size; i++)
        {
            printf(" %X02", RfChip.uid.uidByte[i]);
        }
        printf("\n\r");

        // Print Card type
        uint8_t piccType = RfChip.PICC_GetType(RfChip.uid.sak);
        printf("PICC Type: %s \n\r", RfChip.PICC_GetTypeName(piccType));
        wait_us(TO_MILISEC * 1000);

    }
}