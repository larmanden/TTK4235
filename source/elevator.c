#include "elevator.h"

void elev_update_dir(elevator* el, MotorDirection newdir){
    el->prev_motor_dir = el->current_motor_dir;
    el->current_motor_dir = newdir;
    elevio_motorDirection(el->current_motor_dir);
}

int elev_has_order(elevator* el){
     for (int btn = 0; btn < N_BUTTONS; btn++){
        for (int floor = 0; floor < N_FLOORS; floor++){
            if(el->queue[btn][floor] == 1){
                return 1;
            }
        }
    }
    return 0;
}

int elev_order_above(elevator* el){
    for (int btn = 0; btn < N_BUTTONS; btn++){
        for (int floor = el->current_floor + 1 ; floor < N_FLOORS; floor++){
            if (el->queue[btn][floor] == 1){
                return 1;
            }
        }
    }
    return 0;
}

int elev_order_below(elevator* el){
      for (int btn = 0; btn < N_BUTTONS; btn++){
        for (int floor = 0; floor < el->current_floor; floor++){
            if (el->queue[btn][floor] == 1){
                return 1;
            }
        }
    }
    return 0;
}

void elev_remove_last_order(elevator* el){
    for (int btn = 0; btn < N_BUTTONS; btn++){
        el->queue[btn][el->current_floor] = 0;
    }
    //Security measure since these buttons dont exist
    el->queue[1][0] = -1;
    el->queue[0][3] = -1;  
}

void elev_update_current_floor(elevator* el){
    int tempfloor = elevio_floorSensor();
    if(tempfloor != -1){
        el->current_floor = elevio_floorSensor();
    }
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
    //Loop variables
    int startfloor_loop_up = 0;
    int endfloor_loop_up = N_FLOORS;

    int startfloor_loop_down = 0;
    int endfloor_loop_down = 0;

    //Deciding boundaries for the loops
    switch (el->prev_motor_dir)
    {
    case DIRN_DOWN:
        startfloor_loop_up = el->current_floor;
        endfloor_loop_down = el->current_floor -1;
        break;
    case DIRN_UP:
        startfloor_loop_up = el->current_floor + 1;
        endfloor_loop_down = el->current_floor + 1;
        break;
    default:
        break;
    }

    for (int btn = 0; btn < N_BUTTONS; btn++){
        //Deciding wether to go upwards
        for(int floor = startfloor_loop_up; floor < endfloor_loop_up; floor++){
            if(el->queue[btn][floor] == 1){
                return DIRN_UP;
            }
        }
        //Deciding wether to go downwards
        for (int floor = startfloor_loop_down; floor < endfloor_loop_down; floor++){
            if(el->queue[btn][floor] == 1){
                return DIRN_DOWN;
            }
        }
    }
    //Default
    return DIRN_STOP;
}

void elev_btnlights_update(int queue[N_BUTTONS][N_FLOORS]){
     for (int btn = 0; btn < N_BUTTONS; btn++){
        for (int floor = 0; floor < N_FLOORS; floor++){
            if(queue[btn][floor] == 1){
                elevio_buttonLamp(floor, btn, 1);
            }
            else{
                elevio_buttonLamp(floor,btn, 0);
            }
        }
    }
}
