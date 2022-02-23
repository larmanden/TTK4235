#include "fsm.h"


void fsm_init(elevator el){
    //Sørger for forbindelse til heisserver
    elevio_init();

    //Koden under skal kjøres hvis heisen ikke er i en etasje
    while(elevio_floorSensor() == -1){
        elevio_motorDirection(DIRN_DOWN);
    }
    if(elevio_floorSensor() != -1){
            //Elevator is in a defined floor
            elevio_motorDirection(DIRN_STOP);
            //updateCurrentFloor(el);

            //Mulig at denne er feil
            el.state = IDLE;
    }
}


void fsm_run(elevator el){
    while (1){
        if(elevio_stopButton()){
            el.state = EMERGENCY_STOP;
        }
        switch (el.state)
        {
        case IDLE:
            printf("IDLE\n");
            break;
        case EMERGENCY_STOP:
            fsm_emergency_stop(el);
            break;
        case MOVING:
        default:
            break;
        }
    }
}


void fsm_emergency_stop(elevator el) {
    elevio_motorDirection(DIRN_STOP);
    el.state = EMERGENCY_STOP;
    printf("EMERGENCY STOP");
}


void fsm_moving(elevator el){
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