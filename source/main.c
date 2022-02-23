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
    
    /* fsm_init(&el);
    elevio_motorDirection(DIRN_UP);
    fsm_run(&el); */ 

    clearQueue(&el);
    print_queue(&el); 

    while (1)
    {
        update_queue(&el);
        print_queue(&el);
    }
      
}

