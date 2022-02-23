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

int elevator_has_order(elevator* el){
    //Først sjekke om det er en ordre i matrisen vår
    for (int i = 0; i < N_BUTTONS; i++){
        for (int j = 0; j < N_FLOORS; j++){
            if(el->queue[i][j] == 1){
                return 1;
            }
        }
    }
    return 0;
}