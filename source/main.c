#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include "driver/elevio.h"

//Egne filer
#include "fsm.h"
#include "elevator.h"
#include "queue.h"


//Bug in emergency stop after discarding double previous dir. Swapping between up and down after each emergency. Explicit it can 


int main(){

    elevator el;
    el.current_motor_dir = DIRN_STOP;
    el.prev_motor_dir = DIRN_STOP;
    el.current_floor = 0;
    el.timer = 0;
    el.state = IDLE;

    fsm_init(&el);
    fsm_run(&el);
    
}
