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