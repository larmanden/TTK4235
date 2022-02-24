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
            update_current_floor(el);
            el->state = IDLE;
    }
}


void fsm_run(elevator* el){
    while (1){
        print_queue(el);
        if(elevio_stopButton()){
            el->state = EMERGENCY_STOP;
        }
        switch (el->state)
        {
        case IDLE:
        fsm_idle(el);
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
        el->state = IDLE;el->queue[1][0] = -1;
    el->queue[0][3] = -1;
    update_queue(el);
     update_current_floor(el);

    if (order_above(el)){
        elevio_motorDirection(DIRN_UP);
    }
    if (order_below(el)){
        elevio_motorDirection(DIRN_DOWN);
    }
   
    if(el->currentFloor == el->nextFloor){
        el->state = IDLE;
        remove_last_order(el);
    }
}

void fsm_idle(elevator* el){
    elevio_motorDirection(DIRN_STOP);
    update_current_floor(el);
    update_queue(el);

    if(order_below(el) || order_above(el)){
        el->state = MOVING;
    }

}



