//=====[Libraries]=============================================================
#include "mbed.h"
#include "gatesControl.h"
#include "rfid.h"
#include "tag.h"
#include "relay.h"
#include "non_blocking_delay.h"
#include "stringParser.h"

//=====[Declaration of private defines]========================================



//=====[Declaration of private data types]=====================================


//=====[Declaration and initialization of public global objects]===============



//=====[Declaration and initialization of private global objects]===============



//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============

//=====[Declaration and initialization of private global variables]============

// INICIALIZACION A MANO DE LOS TAGS, A FUTURO QUEDA PROBAR INGRESARLOS DESDE LA BLE
TagList* pTagListGatesControl = new TagList();
Tag* pTag1 = new Tag(TAG1_UID, GROUP_A);
Tag* pTag2 = new Tag(TAG2_UID, GROUP_B);
Tag* pTag3 = new Tag(TAG3_UID); 
static controlGatesStatus_t gatesControlState;
static char* pUIDQueue = NULL;
static Tag* pTagQueue = NULL;
static char _strTag[MAX_SIZE_SERIALIZE_TAG];
static bool isControlGatesActivated;
static nonBlockingDelay_t timerCloseGate;

//=====[Declarations (prototypes) of private functions]========================

// para inicializar a que corral se asocia cada puerta a traves de defines
//void gateInit();
void _tagListUpdate();

//=====[Implementations of public functions]===================================

void gatesControlInit()
{
    //Inicializo los modulos que dependen
    rfidInit();
    relayInit();
    tickInit();

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
                printf("gatesControlUpdate-> Lei una tarjeta \n");
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
                printf("gatesControlUpdate-> OPEN_GATES UID[%s]\n", pUIDQueue);
                if(pTagListGatesControl->find(pUIDQueue))
                {

                    pTagQueue = pTagListGatesControl->getTag(pUIDQueue);
                    openGate(pTagQueue->getAssignedGroup());
                }
                // si el tag no esta en la lista igualmente abro la puerta por defecto
                else
                    openGate(GROUP_DEFAULT);
            }            
            break;
        
        case CLOSE_GATES:
            // ACA VA UN TIMER FIJO, NO TENGO FORMA DE SABER SI YA SE FUE EL ANIMAL
            if( nonBlockingDelayRead(&timerCloseGate) )
            {
                closeGate(pTagQueue->getAssignedGroup());
                // paso a estado IDLE
                gatesControlState = CONTROL_GATES_IDLE;
            }
            break;

        case CONTROL_GATES_DESACTIVATED:
            break;

        case UPDATE_TAG_LIST:
            _tagListUpdate();
            gatesControlState = CONTROL_GATES_IDLE;
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
            printf("openGate -> Group A \n");
            relay_1_ON();
            break;
        
        case GROUP_B:
            printf("openGate -> Group B \n");
            relay_2_ON();
            break;
        case GROUP_DEFAULT:
            printf("openGate -> Group Default \n");
            relay_1_ON();
            break;
    }
    relayUpdate();
    
    // arranco el timer y cambio de estado a CLOSE_GATES
    nonBlockingDelayInit(&timerCloseGate, DELAY_CLOSE_GATE_MS);
    gatesControlState = CLOSE_GATES;

}

void closeGate(group_t group)
{
    printf("closeGate -> apago los dos relay \n");
    // TODAVIA NO IMPLEMENTADO APAGAMOS LOS DOS
    relay_1_OFF();
    relay_2_OFF();
    relayUpdate();
}

void setStrTag(char *str)
{
    if (str != NULL)
    {
        my_strcpy(_strTag,  str);
        // cargo el tag serializado y cambio al estado a actualizar lista de tags
        gatesControlState = UPDATE_TAG_LIST;
        printf("setStrTag -> str[%s], _strTag[%s] \n", str, _strTag);
    }
}
void _tagListUpdate()
{
    printf("_tagListUpdate Inicio strTag[%s] \n", _strTag);
    if (isAValidTag(_strTag))
    {
        Tag* pTag = NULL;
        char ** sTag = deserializeTag(_strTag);

        // Si esta en la lista actualizo el grupo asignado
        if (pTagListGatesControl->find(_strTag))
        {
            printf("_tagListUpdate-> actualizo corral de tag:%s \n", _strTag);
            pTag = pTagListGatesControl->getTag(_strTag);
            pTag->setAssignedGroup(sTag[1]);
        }
        // agrego el nuevo tag
        else
        {
            pTag = new Tag(sTag[0], sTag[1]);
            pTagListGatesControl->addTag(pTag);
        }
    }
}