//=====[Libraries]=============================================================

#include "non_blocking_delay.h"

//=====[Declaration of private defines]========================================

//=====[Declaration of private data types]=====================================

//=====[Declaration and initialization of public global objects]===============

//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============

//=====[Declaration and initialization of private global variables]============

static Ticker ticker;
static tick_t tickCounter;

//=====[Declarations (prototypes) of private functions]========================

void tickerCallback();
tick_t tickRead();

//=====[Implementations of public functions]===================================

void tickInit()
{
    printf("tickInit -> Inicio \n");
    ticker.attach( tickerCallback, ((float) 0.001 ));
    printf("tickInit -> Fin \n");
}

void nonBlockingDelayInit( nonBlockingDelay_t * delay, tick_t durationValue )
{
    printf("nonBlockingDelayInit -> Inicio \n");
    delay->duration = durationValue;
    delay->isRunning = false;
    printf("nonBlockingDelayInit -> Fin \n");
}

bool nonBlockingDelayRead( nonBlockingDelay_t * delay )
{
   bool timeArrived = false;
   tick_t elapsedTime;

   if( !delay->isRunning ) {
      delay->startTime = tickCounter;
      delay->isRunning = true;
   } else {
      elapsedTime = tickCounter - delay->startTime;
      if ( elapsedTime >= delay->duration ) {
         timeArrived = true;
         delay->isRunning = false;
      }
   }

   return timeArrived;
}

void nonBlockingDelayWrite( nonBlockingDelay_t * delay, tick_t durationValue )
{
   delay->duration = durationValue;
}

//=====[Implementations of private functions]==================================

void tickerCallback( void ) 
{
    tickCounter++;
}