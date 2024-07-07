#include "mbed.h"
#include "rfid.h"
#include "uart_BLE.h"
#include "relay.h"
#include "tagLITE.h"


DigitalOut led1(LED1);


// PlayGround para probal als clases tag listaTags
int main()
{
    rfidInit();
    comInit();
    relayInit();

    // inicialize
// Crear una instancia de TagLITE
    TagLITE tag1;
    TagLITE_initWithUID(&tag1, "ABC123");
    printf("Tag1 UID: %s\n", TagLITE_getUID(&tag1));
    
    // Crear una instancia de TagListLITE
    TagListLITE tagList;
    TagListLITE_init(&tagList);
    
    // Agregar tags a la lista
    TagListLITE_addTag(&tagList, "ABC123");
    TagListLITE_addTag(&tagList, "DEF456");
    TagListLITE_addTag(&tagList, "GHI789");
    
    // Mostrar la cantidad de tags en la lista
    printf("TagList size: %zu\n", TagListLITE_getSize(&tagList));
    
    // Buscar un tag en la lista
    if (TagListLITE_find(&tagList, "DEF456")) {
        printf("Tag DEF456 encontrado en la lista.\n");
    } else {
        printf("Tag DEF456 no encontrado en la lista.\n");
    }
    
    // Remover un tag de la lista
    TagListLITE_removeTag(&tagList, "DEF456");
    
    // Mostrar la cantidad de tags en la lista después de la eliminación
    printf("TagList size after removal: %zu\n", TagListLITE_getSize(&tagList));
    
    // Intentar buscar el tag eliminado
    if (TagListLITE_find(&tagList, "DEF456")) {
        printf("Tag DEF456 encontrado en la lista.\n");
    } else {
        printf("Tag DEF456 no encontrado en la lista.\n");
    }
    
    // Limpiar la lista de tags
    TagListLITE_clear(&tagList);
    printf("TagList size after clearing: %zu\n", TagListLITE_getSize(&tagList));

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
