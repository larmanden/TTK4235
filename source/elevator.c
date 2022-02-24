#include "elevator.h"

int check_obstruction(elevator* el){
    if(el->state != DOOR_OPEN){
        return 0;
    }
    while (elevio_obstruction()){
        //Hold døren åpen
        el->state = DOOR_OPEN;
    }
    //Slette denne eller
    return 0;
}


void update_current_floor(elevator* el){
    el->currentFloor = elevio_floorSensor();
};



int elevator_get_order(elevator* el){
     for (int i = 0; i < N_BUTTONS; i++){
        for (int j = 0; j < N_FLOORS; j++){
            if(el->queue[i][j] == 1){
                el->nextFloor = j;
                printf("NEXTFLR:\n");
                printf("%d", el->nextFloor);
                return j;
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
    for (int i = 0; i < N_BUTTONS; i++){
        el->queue[i][el->nextFloor] = 0;
    }
}

int check_next_floor(elevator* el){
    //Sjekke i etasjen over om noen skal samme retning som heisen går
    if (el->current_motor_dir == DIRN_UP){
        if (el->queue[el->current_motor_dir][el->currentFloor+1]){
        return 1;
    }
    

    
}