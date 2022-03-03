#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include "driver/elevio.h"

//Egne filer
#include "fsm.h"
#include "elevator.h"
#include "queue.h"

//02.03 6sec ved stopp på egen etasje problem fortsatt, dette gjelder gammel versjon. Må fortsatt sjekkes


//Intro: Denne versjonen bruker en annen algo for å bestemme hvorvidt heisen skal stoppe og hvilken retning den skal kjøre idet den faktisk får en ordre.


int main(){

    elevator el = {DIRN_STOP, 0, 0, 0, IDLE};
    
    fsm_init(&el);
    fsm_run(&el);
  

}