#pragma once
#include <stdio.h>

#include "driver/elevio.h"
#include "queue.h"


typedef enum {
    IDLE = 0, 
    MOVING, EMERGENCY_STOP,
    DOOR_OPEN
}STATE;



struct elevator{
    MotorDirection current_motor_dir;
    int currentFloor;
    int nextFloor;

    int elev_timer;
    STATE state;
    int queue[N_BUTTONS][N_FLOORS];

};

typedef struct elevator elevator;



int check_obstruction(elevator* el);
void update_current_floor(elevator* el);

int elevator_get_order(elevator* el);
