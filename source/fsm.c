#include "fsm.h"


void fsm_init(elevator* el){
    elevio_init();
    while(elevio_floorSensor() == -1){
        elevio_motorDirection(DIRN_DOWN);
    }
    elev_update_dir(el, DIRN_STOP);
    el->state = IDLE;
    queue_clear(el->queue);
}

void fsm_run(elevator* el){
    while (1){
        switch (el->state)
        {
        case IDLE:
            fsm_idle(el);
            break;
        case MOVING:
            fsm_moving(el);
            break;
        case DOOR_OPEN:
            fsm_door_open(el);
            break;
        case EMERGENCY_STOP:
            fsm_emergency_stop(el);
            break;
        default:
            break;
        }
    }
}

void fsm_idle(elevator* el){
    printf("IDLE \n");
    elev_update_current_floor(el);
    queue_update(el->queue);
    elev_btnlights_update(el->queue);

    if(elevio_stopButton()){
        el->state = EMERGENCY_STOP;
    }
    else if(elev_has_order(el)){
        el->state = MOVING;
    }
}

void fsm_door_open(elevator* el){
    if(elevio_stopButton()){
        el->state = EMERGENCY_STOP;
    }

    elev_update_current_floor(el);
    elevio_doorOpenLamp(1);

    timer_start(el);
    while (!times_up(el)){
        printf("DOOR OPEN\n");
        queue_update(el->queue);
        elev_btnlights_update(el->queue);
        elev_remove_last_order(el);

        if (elevio_obstruction()){
            printf("OBSTRUCTION\n");
            timer_start(el);
        }
        if(elevio_stopButton()){
            el->state =EMERGENCY_STOP;
            return;
        }
    }
    if(elev_has_order(el)){
        el->state = MOVING;
    }
    else{el->state = IDLE;}
    elevio_doorOpenLamp(0);
}

void fsm_moving(elevator* el){

    if(elevio_stopButton()){
        el->state = EMERGENCY_STOP;
        elev_update_dir(el, DIRN_STOP);
        return;
    }

    printf("MOVING \n");
    queue_print(el->queue);
    queue_update(el->queue);
    elev_btnlights_update(el->queue);
    elev_update_current_floor(el);
    
    //Deciding wether to stop or not
    int tempfloor = elevio_floorSensor();
    if(tempfloor != -1){  
        elevio_floorIndicator(tempfloor);
        switch (el->current_motor_dir){
        case DIRN_DOWN:
            if(el->queue[BUTTON_HALL_DOWN][tempfloor] == 1 || el->queue[BUTTON_CAB][tempfloor] == 1){
                elev_update_dir(el, DIRN_STOP);
                el->state = DOOR_OPEN;
            }
            break;
        case DIRN_UP:
            if(el->queue[BUTTON_HALL_UP][tempfloor] == 1 || el->queue[BUTTON_CAB][tempfloor] == 1){
                elev_update_dir(el, DIRN_STOP);
                el->state = DOOR_OPEN;
            }
            break;
        case DIRN_STOP:
            if(el->queue[BUTTON_HALL_DOWN][tempfloor] == 1 || el->queue[BUTTON_HALL_UP][tempfloor] == 1 || el->queue[BUTTON_CAB][tempfloor] == 1){
                elev_update_dir(el, DIRN_STOP);
                el->state = DOOR_OPEN;
            }
            break;
        default:
            break;
        }
        
        if(tempfloor == elev_look_ahead(el)){
            elev_update_dir(el, DIRN_STOP);
            el->state = DOOR_OPEN;
        }
    }
    //Setting motordirection based on target
    switch (el->current_motor_dir){
    case DIRN_DOWN:
        if(elev_order_below(el)){
            elev_update_dir(el, DIRN_DOWN);
        }
        else if (elev_order_above(el)){
            elev_update_dir(el, DIRN_UP);
        }
        break;
    case DIRN_STOP:
        if(elev_order_above(el)){
            elev_update_dir(el, DIRN_UP);
        }
        else if (elev_order_below(el)){
            elev_update_dir(el, DIRN_DOWN);
        }
        else if(elevio_floorSensor() == -1){
            MotorDirection newdir = elev_move_after_emergency(el);
            elev_update_dir(el, newdir);
        }
        break;
    case DIRN_UP:  
        if(elev_order_above(el)){
            elev_update_dir(el, DIRN_UP);
        }
        else if (elev_order_below(el)){
            elev_update_dir(el, DIRN_DOWN);
        }
        break;
    }
}

void fsm_emergency_stop(elevator* el){
    queue_clear(el->queue);
    
    while (elevio_stopButton()){
        printf("EMERGENCY STOP\n");
        elevio_stopLamp(1);

        if(elevio_floorSensor() != -1){
            printf("DOOR OPEN_ EM\n");
            elevio_doorOpenLamp(1);
        }
    }
    elevio_stopLamp(0);
    if(elevio_floorSensor() != -1){
        el->state = DOOR_OPEN;
    }
    else{el->state = IDLE;}
}
