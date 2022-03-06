#pragma once
#include <stdio.h>
#include "stdlib.h"


#include "driver/elevio.h"
#include "queue.h"


typedef enum {
    IDLE = 0, 
    MOVING, EMERGENCY_STOP,
    DOOR_OPEN
}STATE;



struct elevator{
    MotorDirection prev_motor_dir;
    MotorDirection prev_prev_dir;
    MotorDirection current_motor_dir;
    int currentFloor;

    int elev_timer;
    STATE state;
    int queue[N_BUTTONS][N_FLOORS];

};

typedef struct elevator elevator;

void elevator_update_dir(elevator* el, MotorDirection newdir);

int elevator_has_order(elevator* el);

int order_above(elevator* el);
int order_below(elevator* el);

void remove_last_order(elevator* el);


void elev_limit(elevator* el);
void elev_update_current_floor(elevator* el);
int elev_only_orders_in_opposite_dir(elevator* el);

int elev_look_ahead(elevator* el);

MotorDirection elev_move_after_emergency(elevator* el);
