//=====[#include guards - begin]===============================================

#ifndef _GATESCONTROL_H_
#define _GATESCONTROL_H_

#include "mbed.h"
#include "tag.h"


//=====[Declaration of public defines]=========================================

#define TAG1_UID "BOCA"
#define TAG2_UID "JUNIORS"

//=====[Declaration of public data types]======================================

typedef enum
{
    CONTROL_GATES_IDLE,
    TAG_QUEUE,
    OPEN_GATES,
    CLOSE_GATES,
    CONTROL_GATES_DESACTIVATED

    } controlGatesStatus_t;

//=====[Declarations (prototypes) of public functions]=========================

void gatesControlInit();
void gatesControlUpdate();
void openGate(group_t group);
void closeGate(group_t group);


//=====[#include guards - end]=================================================

#endif // _GATESCONTROL_H_
