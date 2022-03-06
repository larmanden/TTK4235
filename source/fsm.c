#include "fsm.h"


void fsm_init(elevator* el){
    elevio_init();
    while(elevio_floorSensor() == -1){
        elevio_motorDirection(DIRN_DOWN);
    }
    //Now we are in a defined floor
    elev_update_current_floor(el);

    elevator_update_dir(el, DIRN_STOP);
    el->state = IDLE;
}

void fsm_run(elevator* el){
    //Gameloopen vår
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

    if(elevio_stopButton()){
        el->state = EMERGENCY_STOP;
    }
    
    elev_update_current_floor(el);
    update_queue(el);
    //Mulighet for å kunne sjekke om det har kommet en ordre i matrisen
    if(elevator_has_order(el)){
        el->state = MOVING;
    }
    //elevator_update_dir(el, DIRN_STOP);
}

void fsm_door_open(elevator* el){

    if(elevio_stopButton()){
        el->state = EMERGENCY_STOP;
    }

    elev_update_current_floor(el);
    elevator_update_dir(el, DIRN_STOP);
    elevio_doorOpenLamp(1);

    //Timer and obstruction implementation
    timer_start(el);
    while (!times_up(el))
    {
        printf("DOOR OPEN\n");
        update_queue(el);
        remove_last_order(el);
        if (elevio_obstruction()){
            printf("OBSTRUCTION\n");
            timer_start(el);
        }

        //Mulighet for å komme til EMERGENCY_STOP når dørene er åpne
        if(elevio_stopButton()){
            el->state =EMERGENCY_STOP;
            return;
        }
    }

    remove_last_order(el);
    update_queue(el);
    if(elevator_has_order(el)){
        el->state = MOVING;
    }
    else{
        el->state = IDLE;
        //elevator_update_dir(el, DIRN_STOP);
    }
    
    elevio_doorOpenLamp(0);
}

void fsm_moving(elevator* el){

    if(elevio_stopButton()){
        el->state = EMERGENCY_STOP;
        //Viktig at denne er her fordi den bare skal kalles en gang?
        elevator_update_dir(el, DIRN_STOP);
        return;
    }


    printf("MOVING \n");
    update_queue(el);

    elev_update_current_floor(el);
    
    int tmpflr = elevio_floorSensor();

    if(tmpflr != -1){  
        elevio_floorIndicator(tmpflr);   
        switch (el->current_motor_dir){
        case DIRN_DOWN:
            if(el->queue[BUTTON_HALL_DOWN][tmpflr] == 1 || el->queue[BUTTON_CAB][tmpflr] == 1){
                elevator_update_dir(el, DIRN_STOP);
                el->state = DOOR_OPEN;
            }
            break;
        case DIRN_UP:
            if(el->queue[BUTTON_HALL_UP][tmpflr] == 1 || el->queue[BUTTON_CAB][tmpflr] == 1){
                elevator_update_dir(el, DIRN_STOP);
                el->state = DOOR_OPEN;
            }
            break;
        case DIRN_STOP:
            //Hvis heisen kommer fra IDLE vil vi ha den innom MOVING før den går til DOOR_OPEN
            if(el->queue[BUTTON_HALL_DOWN][tmpflr] == 1 || el->queue[BUTTON_HALL_UP][tmpflr] == 1 || el->queue[BUTTON_CAB][tmpflr] == 1){
                elevator_update_dir(el, DIRN_STOP);
                el->state = DOOR_OPEN;
            }
            break;
        default:
            break;
        }
        

        //Denne er ikke vanntett, vi må ha en mulighet for å sjekke når denne skal kalles på
        //Skal sørge for å stoppe ved knapper som er motsatt rettet av egen retning uavhenig av hvor mange det er i matrisen.
        if(tmpflr == elev_look_ahead(el)){
            elevator_update_dir(el, DIRN_STOP);
            el->state = DOOR_OPEN;
        }

        //Vi trenger en mulighet for å stoppe på motsatt-retning knapp selvom det er en annen "samme vei" knapp som er trykket inn
        //Mulgihet for å generalisere look_ahead()?

    }

    switch (el->current_motor_dir){
    case DIRN_DOWN:
        if(order_below(el)){
            elevator_update_dir(el, DIRN_DOWN);
        }
        else if (order_above(el)){
            elevator_update_dir(el, DIRN_UP);
        }
        break;
    case DIRN_STOP:
        if(order_above(el)){
            elevator_update_dir(el, DIRN_UP);
        }
        else if (order_below(el)){
            elevator_update_dir(el, DIRN_DOWN);
        }
        else if(elevio_floorSensor() == -1){
            MotorDirection newdir = elev_move_after_emergency(el);
            elevator_update_dir(el, newdir);
        }
        break;
    case DIRN_UP:  
        if(order_above(el)){
            elevator_update_dir(el, DIRN_UP);
        }
        else if (order_below(el)){
            elevator_update_dir(el, DIRN_DOWN);
        }
        break;
    }
}


void fsm_emergency_stop(elevator* el){
    /* elevator_update_dir(el, DIRN_STOP); */
    
    clearQueue(el);

    while (elevio_stopButton()){
        printf("EMERGENCY STOP\n");
        elevio_stopLamp(1);

        if(elevio_floorSensor() != -1){
            //Pseudo door_open
            printf("DOOR OPEN_ EM\n");
            elevio_doorOpenLamp(1);
        }
    }
    elevio_stopLamp(0);
    elevio_doorOpenLamp(0); //cmt: logikken bak rundt når disse lampene skal av og på må fikses.
    if(elevio_floorSensor() != -1){
        el->state = DOOR_OPEN;
    }
    else{
        el->state = IDLE;
    }
}
