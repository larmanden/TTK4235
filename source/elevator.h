#pragma once
#include <stdio.h>

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



