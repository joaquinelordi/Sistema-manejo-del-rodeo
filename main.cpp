
#include "mbed.h"
#include "gatesControl.h"
#include "rfid.h"
#include "uart_BLE.h"
#include "relay.h"
#include "tag.h"
#include "non_blocking_delay.h"
#include "stringParser.h"

DigitalOut led1(LED1);
static nonBlockingDelay_t timerLed;

int main()
{
    char buffer[BUFFER_SIZE];
    char** vTag;
    TagList* pTagList = new TagList();

    comInit();
    tickInit();
    gatesControlInit();
    nonBlockingDelayInit(&timerLed, 2000);

    printf("Init completado \n");

    while(true)
    {
        //Parpadeo del led para probar el delay
        if(nonBlockingDelayRead(&timerLed))
        {
            led1 = !led1;
        }

        gatesControlUpdate();
        comUpdate();
        if (getStateBLECom() == RX_BUFFERED)
        {   
            if(BLERead(buffer))
            {
                printf("Received: %s\n", buffer);
                if(isAValidTag(buffer))
                {   
                    printf("recibi un tag valido\n");
                    setStrTag(buffer);
                }
            }
        }
    }
}




// PLAYGROUND DEL BLE
/*
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
*/


/*
//PROBADO CON TAG Y TAGLITE 
// PlayGround para probar las clases tag listaTags
int main()
{
    rfidInit();
    comInit();
    relayInit();

    // inicialize
    Tag* pTag1 = new Tag("Bokita");
    Tag* pTag2 = new Tag("El mas grande");
    Tag* pTag3 = new Tag("aguante booocaaaa");
        
    TagList* pTagList = new TagList();
    
    printf("Tag1 UID: %s\n", pTag1->getTagUID());


    pTagList->addTag(pTag1);
    pTagList->addTag(pTag2);
    pTagList->addTag(pTag3);
    
    printf("TagList size: %d\n", pTagList->getTagListSize());
    
    // prueba de metodos
    if (pTagList->find(pTag1->getTagUID()))
    {
        printf("Tag encontrado en la lista: %s\n", pTag1->getTagUID());
    }
    else
    {
        printf("Tag no encontrado en la lista.\n");
    }
    
    pTagList->clear();

    printf("TagList despues de clear() \n", pTagList->getTagListSize());

    if (pTagList->find(pTag1->getTagUID()))
    {
        printf("Tag encontrado en la lista: %s\n", pTag1->getTagUID());
    }
    else
    {
        printf("Tag no encontrado en la lista.\n");
    }

    return 0;
}
*/



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
