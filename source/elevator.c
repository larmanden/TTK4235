#include "elevator.h"


int elevator_has_order(elevator* el){
     for (int btn = 0; btn < N_BUTTONS; btn++){
        for (int floor = 0; floor < N_FLOORS; floor++){
            if(el->queue[btn][floor] == 1){
                return 1;
            }
        }
    }
    return 0;
}


int order_above(elevator* el){
    for (int btn = 0; btn < N_BUTTONS; btn++){
        for (int floor = el->currentFloor + 1 ; floor < N_FLOORS; floor++){
            if (el->queue[btn][floor] == 1){
                return 1;
            }
        }
    }
    return 0;
}
int order_below(elevator* el){
      for (int btn = 0; btn < N_BUTTONS; btn++){
        for (int floor = 0; floor < el->currentFloor; floor++){
            if (el->queue[btn][floor] == 1){
                return 1;
            }
        }
    }
    return 0;
}

void remove_last_order(elevator* el){
    for (int btn = 0; btn < N_BUTTONS; btn++){
        el->queue[btn][el->currentFloor] = 0;
    }
    //Koden bør funke uten disse her
    el->queue[1][0] = -1;
    el->queue[0][3] = -1;
    
}


void elevator_update_dir(elevator* el, MotorDirection newdir){
    MotorDirection tmp1 = el->prev_motor_dir;

    el->prev_prev_dir = tmp1;

    MotorDirection tmp2 = el-> current_motor_dir;
    el->prev_motor_dir = tmp2;

    el->current_motor_dir = newdir;
    //Mulig at denne burde bli kalt på i fsm for å unngå for mye dependecies
    elevio_motorDirection(el->current_motor_dir);
}

void elev_limit(elevator* el){
    if(elevio_floorSensor() == 0 || elevio_floorSensor() == 3){
        el->state = IDLE;
    }
}

void elev_update_current_floor(elevator* el){
    int tmpflr = elevio_floorSensor();
    if(tmpflr != -1){
        el->currentFloor = elevio_floorSensor();
    }
}

int elev_only_orders_in_opposite_dir(elevator* el){
    int btnindex = 0;
    if(el->current_motor_dir == DIRN_DOWN){
        btnindex = BUTTON_HALL_DOWN;
    }
    else{btnindex = BUTTON_HALL_UP;}

    for (int floor = 0; floor < N_FLOORS; floor++){
        if(el->queue[btnindex][floor] == 1){return 0;}
    }
    return 1;
}



int elev_look_ahead(elevator* el){
    int stopfloor = -1;
    switch (el->current_motor_dir){
        case DIRN_DOWN:
            for (int floor = 0; floor < N_FLOORS; floor++){
                if(el->queue[BUTTON_HALL_DOWN][floor] == 1){
                    stopfloor = floor; 
                    return stopfloor;
                }
                if(el->queue[BUTTON_HALL_UP][floor] == 1){
                    stopfloor = floor;
                    return stopfloor;
                }
            }
            break;
        case DIRN_UP:
            for (int floor = N_FLOORS - 1; floor >= 0; floor--){
                if(el->queue[BUTTON_HALL_UP][floor] == 1){
                    stopfloor = floor;
                    return stopfloor;
                }
                if(el->queue[BUTTON_HALL_DOWN][floor] == 1){
                    stopfloor = floor;
                    return stopfloor;
                }
            }
            break;
        default:
            break;
    }
    return stopfloor;
}

MotorDirection elev_move_after_emergency(elevator* el){
    switch (el->prev_prev_dir)
    {
    case DIRN_DOWN:
        for (int btn = 0; btn < N_BUTTONS; btn++){
            for (int floor = el->currentFloor; floor < N_FLOORS; floor++){
                if(el->queue[btn][floor] == 1){

                    return DIRN_UP;
                }
            }
        }
        for (int btn = 0; btn < N_BUTTONS; btn++){
            for (int floor = 0; floor < el->currentFloor - 1; floor++){
                if(el->queue[btn][floor] == 1){
                    return DIRN_DOWN;
                }
            }
        }
        break;
    
    case DIRN_UP:
         for (int btn = 0; btn < N_BUTTONS; btn++){
            for (int floor = el->currentFloor + 1; floor < N_FLOORS; floor++){
                if(el->queue[btn][floor] == 1){
                    return DIRN_UP;
                }
            }
        }
        for (int btn = 0; btn < N_BUTTONS; btn++){
            for (int floor = 0; floor <= el->currentFloor; floor++){
                if(el->queue[btn][floor] == 1){
                    return DIRN_DOWN;
                }
            }
        }
        break;
    default:
        break;
    }
    return DIRN_STOP;  
}

