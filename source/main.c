#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include "driver/elevio.h"

#include "fsm.h"

void examplereet(){
    elevio_init();
    elevio_motorDirection(DIRN_DOWN);
    while(1){
         if(elevio_floorSensor() == 1){
             elevio_motorDirection(DIRN_STOP);
             elevio_motorDirection(DIRN_UP);
         }
         if(elevio_floorSensor() == 3){
             elevio_motorDirection(DIRN_DOWN);
         }
    }
}


int main(){
    //printf("halla\n");
    
    elevator el;

    //examplereet();

    fsm_init(el);
    fsm_run(el); 

}

