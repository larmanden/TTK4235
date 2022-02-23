#include "fsm.h"


void fsm_init(elevator* el){
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
            el->state = MOVING;
    }
}


void fsm_run(elevator* el){
    while (1){
        if(elevio_stopButton()){
            el->state = EMERGENCY_STOP;
        }
        switch (el->state)
        {
        case IDLE:
            printf("IDLE\n");
            break;
        case EMERGENCY_STOP:
            fsm_emergency_stop(el);
            break;
        case MOVING:
            fsm_moving(el);
        default:
            break;
        }
    }
}


void fsm_emergency_stop(elevator* el) {
    printf("EMERGENCY STOP\n");

    elevio_motorDirection(DIRN_STOP);
    

    if(elevio_floorSensor() != -1){
        printf("OPENING DOOR");
        timer_start(el); 
        while(!times_up(el)){
            printf("WAITING");
        }
    }

    //Mulighet for å komme til IDLE
    if(!elevio_stopButton()){
        el->state = IDLE;
    }
}


void fsm_moving(elevator* el){
    if (elevio_floorSensor() == 0){
        elevio_motorDirection(DIRN_UP);
    }

    if (elevio_floorSensor() == 3){
        elevio_motorDirection(DIRN_DOWN);
    }
}