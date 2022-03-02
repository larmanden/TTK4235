#include "fsm.h"


void fsm_init(elevator* el){
    elevio_init();
    while(elevio_floorSensor() == -1){
        elevio_motorDirection(DIRN_DOWN);
    }
    //Now we are in a defined floor
    elev_update_current_floor(el);
    el->state = IDLE;
}

void fsm_run(elevator* el){
    //Gameloopen vår
    while (1){
    if(elevio_stopButton()){
        el->state = EMERGENCY_STOP;
    }
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
    update_queue(el);
    //Mulighet for å kunne sjekke om det har kommet en ordre i matrisen
    if(elevator_has_order(el)){
        el->state = MOVING;
    }
    elevator_update_dir(el, DIRN_STOP);
}

void fsm_door_open(elevator* el){

    elev_update_current_floor(el);
    //Stop the elevator, ønsker ikke å ha DIRN_STOP som en forrige retning
    elevator_update_dir(el, DIRN_STOP);
    remove_last_order(el);  
    
    elevio_doorOpenLamp(1);

    //Timer and obstruction implementation
    timer_start(el);
    while (!times_up(el))
    {
        printf("DOOR OPEN\n");
        update_queue(el);
        if (elevio_obstruction()){
            printf("OBSTRUCTION\n");
            timer_start(el);
        }
    }
    
    //Mulig ikke needed
    update_queue(el);
    /* if(elevator_has_order(el)){
        el->state = MOVING;
    }
    else{
        el->state = IDLE;
    } */

    el->state = IDLE;

    elevio_doorOpenLamp(0);
}


void fsm_moving(elevator* el){
    //Default
    printf("MOVING \n");
    print_queue(el);
    update_queue(el);

    //Kontrollere at den ikke går til endestop
    elev_limit(el);
    

    //Kontinuerlig mulighet for å stoppe på en etasje idet vi kjører forbi
    int tmpflr = elevio_floorSensor();
    if(tmpflr != -1){
        //Fix the floorlights

        elevio_floorIndicator(tmpflr);
        switch (el->current_motor_dir){
            case DIRN_UP:
                if(el->queue[BUTTON_HALL_UP][tmpflr] == 1  || el->queue[BUTTON_CAB][tmpflr] == 1){
                    el->state = DOOR_OPEN;
                }
                else if (el->queue[BUTTON_HALL_DOWN][tmpflr] == 1 && elev_only_orders_in_opposite_dir(el, DIRN_UP) == 1){
                    el->state = DOOR_OPEN;
                }
                break;
            case DIRN_DOWN:
                if(el->queue[BUTTON_HALL_DOWN][tmpflr] == 1 || el->queue[BUTTON_CAB][tmpflr] == 1 ){
                    el->state = DOOR_OPEN;
                }
                else if (el->queue[BUTTON_HALL_UP][tmpflr] == 1 && elev_only_orders_in_opposite_dir(el, DIRN_DOWN) == 1){
                    el->state = DOOR_OPEN;
                }
                //If there is only opposite buttons, need a function
                break;
            case DIRN_STOP:
                for (int i = 0; i < N_BUTTONS; i++){
                    //Her fucker d seg muligens
                    if(tmpflr == el->currentFloor && el->queue[i][tmpflr] == 1){
                        el->state = DOOR_OPEN;
                    }
                }
                break;
            default:
                printf("DEFAULT \n");
                break;
            }
    }



    //Her har vi mulighet for å sette retning hvis vi ikke skulle stoppe

    //We need to prioritize the cabin buttons

    switch (el->current_motor_dir){
    case DIRN_DOWN:
        if(order_below(el)){
            elevator_update_dir(el, DIRN_DOWN);
        }
        else if (order_above(el)){
            elevator_update_dir(el, DIRN_UP);
        }
        break;
        
    default:    //Skal både gjelde for oppover og for i ro
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
    elevator_update_dir(el, DIRN_STOP);
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

    if(elevio_floorSensor() != -1){
        el->state = DOOR_OPEN;
    }
    else{el->state = IDLE;
            elevio_stopLamp(0);
    }
}
