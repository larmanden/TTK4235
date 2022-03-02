#include "elevator.h"


int elevator_has_order(elevator* el){
     for (int i = 0; i < N_BUTTONS; i++){
        for (int j = 0; j < N_FLOORS; j++){
            if(el->queue[i][j] == 1){
                return 1;
            }
        }
    }
    return 0;
}


int order_above(elevator* el){
    for (int i = 0; i < N_BUTTONS; i++){
        for (int j = el->currentFloor + 1; j < N_FLOORS; j++){
            if (el->queue[i][j] == 1){
                return 1;
            }
        }
    }
    return 0;
}
int order_below(elevator* el){
      for (int i = 0; i < N_BUTTONS; i++){
        for (int j = 0; j < el->currentFloor; j++){
            if (el->queue[i][j] == 1){
                return 1;
            }
        }
    }
    return 0;
}

void remove_last_order(elevator* el){
    //Ønsker å fjerne både cabin og den gitte retningen fra matrisen
    for (int i = 0; i < N_BUTTONS; i++){
        el->queue[i][el->currentFloor] = 0;
    }
    
    el->queue[1][0] = -1;
    el->queue[0][3] = -1;
    
}


void elevator_update_dir(elevator* el, MotorDirection newdir){
    /* if(newdir == DIRN_STOP){
        el->current_motor_dir = newdir;
        elevio_motorDirection(el->current_motor_dir);
        return;
    } */
    el->prev_motor_dir = el->current_motor_dir;
    el->current_motor_dir = newdir;
    //Mulig at denne burde bli kalt på i fsm for å unngå for mye dependecies
    elevio_motorDirection(el->current_motor_dir);
}





//Mulig shady at vi går innom idle, hvis ikke må denne implementeres som en fsm funksjon muligens
void elev_limit(elevator* el){
    if(elevio_floorSensor() == 0 || elevio_floorSensor() == 3){
        el->state = IDLE;
    }
}

void elev_update_current_floor(elevator* el){
    //Mulig at vi et sted i koden nytter at currentfloor faktisk er -1, tror ikke d. Isåfall bruk floorsensor direkte
    int tmpflr = elevio_floorSensor();
    //el->currentFloor = elevio_floorSensor();
    if(tmpflr != -1){
        el->currentFloor = elevio_floorSensor();
    }
}

int elev_only_orders_in_opposite_dir(elevator* el, MotorDirection dirn){
    switch (dirn)
    {
    case DIRN_DOWN:
        //Want to check opposite
        for (int i = 0; i < N_FLOORS; i++){
            if(el->queue[BUTTON_HALL_DOWN][i] == 1){
                return 0;
            }
        }
        
        break;
    case DIRN_UP:
          //Want to check opposite
        for (int i = 0; i < N_FLOORS; i++){
            if(el->queue[BUTTON_HALL_UP][i] == 1){
                return 0;
            }
        }
        break;
    default:
        break;
    }
    return 1;
}