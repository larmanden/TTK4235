#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include "driver/elevio.h"

#include "fsm.h"

int main(){

    elevator el;
    el.current_motor_dir = DIRN_STOP;
    el.prev_motor_dir = DIRN_STOP;
    el.current_floor = 0;
    el.state = IDLE;

    fsm_init(&el);
    fsm_run(&el);
    
}
