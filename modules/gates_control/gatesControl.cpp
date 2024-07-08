//=====[Libraries]=============================================================
#include "mbed.h"
#include "gatesControl.h"
#include "rfid.h"
#include "tag.h"
#include "relay.h"

//=====[Declaration of private defines]========================================



//=====[Declaration of private data types]=====================================


//=====[Declaration and initialization of public global objects]===============



//=====[Declaration and initialization of private global objects]===============



//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============

//=====[Declaration and initialization of private global variables]============

// INICIALIZACION A MANO DE LOS TAGS, A FUTURO QUEDA PROBAR INGRESARLOS DESDE LA BLE
TagList* pTagListGatesControl = new TagList();
Tag* pTag1 = new Tag(TAG1_UID);
Tag* pTag2 = new Tag(TAG2_UID); 
static controlGatesStatus_t gatesControlState;
static char* pUIDQueue = NULL;
static Tag* pTagQueue = NULL;
static bool isControlGatesActivated;

//=====[Declarations (prototypes) of private functions]========================

// para inicializar a que corral se asocia cada puerta a traves de defines
void gateInit();


//=====[Implementations of public functions]===================================

void gatesControlInit()
{
    //Inicializacion a mano de la lista de tags
    pTagListGatesControl->addTag(pTag1);
    pTagListGatesControl->addTag(pTag2);
    gatesControlState = CONTROL_GATES_IDLE;
    isControlGatesActivated = true;
}

void gatesControlUpdate()
{
    switch (gatesControlState)
    {
        //ACA SE PUEDE VER SI HAY ALGO PARA LEER
        case CONTROL_GATES_IDLE:
            
            rfidUpdate();
            //Esto esta feo, mejor si el update devuelve algo para indicar que se leyo un tag
            pUIDQueue = rfidReadUID();
            if(pUIDQueue != NULL )
            {
                // si lei un tag hay que procesar para accionar la puerta que corresponda
                // Busco el tag y acciono el relay correspondiente

                // cambio de estado
                gatesControlState = TAG_QUEUE;
            }
                

            break;

        case TAG_QUEUE:

            if(isControlGatesActivated == true)
            {
                gatesControlState = OPEN_GATES;
            }
            else
            {
                // la puerta por defecto siempre queda abierta y no hay que hacer nada
                gatesControlState = CONTROL_GATES_DESACTIVATED;
            }
            break;

        case OPEN_GATES:

            if(pUIDQueue != NULL )
            {
                pTagQueue = pTagListGatesControl->getTag(pUIDQueue);
                openGate(pTagQueue->getAssignedGroup());
            }            
            // lanzo timer
            break;
        
        case CLOSE_GATES:
            // ACA VA UN TIMER FIJO, NO TENGO FORMA DE SABER SI YA SE FUE EL ANIMAL
            closeGate(pTagQueue->getAssignedGroup());
            break;

        case CONTROL_GATES_DESACTIVATED:
            break;


    }

}

//=====[Implementations of private functions]==================================

void openGate(group_t group)
{
    // aca hacemos la asignacion de la puerta con un define
    switch (group)
    {
        case GROUP_A:
            relay_1_ON();
            //dispatamos un timer para cerrar la puerta abierta
            break;
        
        case GROUP_B:
            relay_2_ON();
            //dispatamos un timer para cerrar la puerta abierta
            break;
        case GROUP_DEFAULT:
            relay_1_ON();
            //dispatamos un timer para cerrar la puerta abierta
            break;
    }
}

void closeGate(group_t group)
{
    // TODAVIA NO IMPLEMENTADO APAGAMOS LOS DOS
    relay_1_OFF();
    relay_2_OFF();
}