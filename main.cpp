#include "mbed.h"
//#include "rfid.h"
//#include "uart_BLE.h"
//#include "relay.h"
#include "tag.h"


DigitalOut led1(LED1);

// PlayGround para probal als clases tag listaTags
int main()
{
    //comInit();

    // inicialize
    char* tag1 = "tag1";
    char* tag2 = "tag2";
    char* tag3 = "tag3";
    char* tag4 = "tag4";

    TagList* pTagList = new TagList();
    Tag* pTag1 = new Tag(tag1);
    Tag* pTag2 = new Tag(tag2);
    Tag* pTag3 = new Tag(tag3);
    Tag* pTag4 = new Tag(tag4);

    pTagList->addTag(tag1);
    pTagList->addTag(tag2);
    pTagList->addTag(tag3);
    pTagList->addTag(tag4);


    printf("TagList_size[%d]", pTagList->getTagListSize());

    if(pTagList->find(tag1))
    {
        printf("encontre el tag:%s \n", tag1);
    }    

    pTagList->removeTag(tag1);
    if(!pTagList->find(tag1))
    {
        printf("NO encontre el tag:%s \n", tag1);
    } 

    return 0;
}



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
