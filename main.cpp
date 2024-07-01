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
#include "rfid.h"
//#include "uart_module.h"
#include "relay.h"


DigitalOut led1(LED1);

int main()
{
    rfidInit();
    //comInit();
    relayInit();
/*
    while(true)
    {
        led1 = !led1;
        printf("relay ON\n");
        relayON();
        relayUpdate();
        wait_us(TO_MILISEC * 1000);
        printf("relay OFF\n");
        relayOFF();
        relayUpdate();
        wait_us(TO_MILISEC * 1000);
    }
*/

    while(true)
    {
        led1 = !led1;
        rfidUpdate();
        wait_us(TO_MILISEC * 2000);
        //relayUpdate();
        //comUpdate();

    }

}