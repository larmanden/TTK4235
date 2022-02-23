#pragma once

#include "driver/elevio.h"
#include "queue.h"



typedef enum {
    IDLE = 0, 
    MOVING, EMERGENCY_STOP,
    DOOR_OPEN
}STATE;

typedef struct elevator{
    MotorDirection current_motor_dir;
    int currentFloor;
    int nextFloor;
    int elev_timer;

    STATE state;
    Queue queue;

} elevator;


//Floor member functions
void updateCurrentFloor(elevator* el);

int elevatorControlRange();
int ordersAbove(elevator* el);
int ordersBelow(elevator* el);

void removeOrder(elevator* el);

//Ideen her er og sette nextFloor for å kunne sjekke hvor vi skal
void executeOrder(elevator* el);

