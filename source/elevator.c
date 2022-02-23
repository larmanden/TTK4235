#include "elevator.h"

void updateCurrentFLoor(elevator* el){
    el->currentFloor = elevio_floorSensor();
    //Testing comment
}
