#include "fsm2.h"

//Mangler å finne plasser for å oppdatere køen, update_queue


void fsm2_init(elevator* el){
    elevio_init();

    while(elevio_floorSensor() == -1){
        elevio_motorDirection(DIRN_DOWN);
    }
    elevio_motorDirection(DIRN_STOP);
    update_current_floor(el);
    el->state = IDLE;
}

void fsm2_idle(elevator* el){
    elevio_motorDirection(DIRN_STOP);
    update_current_floor(el);
    if (order_below(el) || order_above(el)){
        el->state = MOVING;
    }    
}

void fsm2_moving(elevator* el){
    //utfør ordre utifra køen
    execute_order(el);
}


void fsm2_run(elevator* el){
    while (1){
        switch (el->state)
        {
        case IDLE:
            fsm2_idle(el);
            break;
        case MOVING:
            fsm_moving(el);
            break;
        default:
            break;
        }
    }
}