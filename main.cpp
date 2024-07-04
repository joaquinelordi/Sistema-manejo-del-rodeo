#include "mbed.h"
#include "rfid.h"
#include "uart_BLE.h"
#include "relay.h"


DigitalOut led1(LED1);

int main()
{
    rfidInit();
    comInit();
    relayInit();

    while(true)
    {
        //printf("while principal \n");
        led1 = !led1;
        //printf("En el loop principal  \n");
        BLEWrite("BOCAA");
        wait_us(TO_MILISEC * 4000);
        //comUpdate();
        char buffer[BUFFER_SIZE];
        if (comRead(buffer)) {
            printf("Received: %s\n\n", buffer);
        }
    }

}



/*
DigitalOut myled(LED1);

int main() {
  while(1) {
    myled = 1;
    wait(0.2);
    myled = 0;
    wait(0.2);
  }
}
*/
