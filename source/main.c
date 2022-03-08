#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include "driver/elevio.h"

//Egne filer
#include "fsm.h"
#include "elevator.h"
#include "queue.h"


int main(){

    elevator el;
    el.current_motor_dir = DIRN_STOP;
    el.prev_motor_dir = DIRN_STOP;
    el.prev_prev_dir = DIRN_STOP;
    el.currentFloor = 0;
    el.elev_timer = 0;
    el.state = IDLE;

    fsm_init(&el);
    fsm_run(&el);
    
}