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

    printf("Init completado");

    while(true)
    {

        led1 = !led1;
        BLEWrite("BOCAA BOOCAAA\n");
        comUpdate();
        wait_us(TO_MILISEC * 4000);
        if (getStateBLECom() == RX_BUFFERED)
        {   
            char buffer[BUFFER_SIZE];
            if(BLERead(buffer))
            {
                printf("Received: %s\n\n", buffer);
            }
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
