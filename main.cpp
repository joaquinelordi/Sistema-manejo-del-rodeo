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


DigitalOut led1(LED1);

int main()
{
    rfidInit();
    //comInit();
    

    while(true)
    {
        led1 = !led1;
        rfidUpdate();
        wait_us(TO_MILISEC * 2000);
        //comUpdate();

    }

}