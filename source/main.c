#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include "driver/elevio.h"


#include "fsm.h"
#include "elevator.h"
#include "queue.h"

//02.03 6sec ved stopp på egen etasje problem fortsatt


int main(){

    elevator el = {DIRN_STOP, 0, 0, 0, IDLE};
    fsm_init(&el);
    fsm_run(&el);
  

}