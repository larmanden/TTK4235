#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include "driver/elevio.h"

#include "fsm.h"
#include "elevator.h"
#include "queue.h"





int main(){

    
    elevator el = {DIRN_STOP, 0, 0, 0, IDLE};

    //Denne er fackings keeeey_UAns
    //elevio_init();

    fsm_init(&el);
    fsm_run(&el);
}

