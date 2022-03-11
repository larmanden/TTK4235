#pragma once
#include "driver/elevio.h"
#include "queue.h"


typedef enum {
    IDLE = 0, 
    MOVING, EMERGENCY_STOP,
    DOOR_OPEN
}STATE;


struct elevator{
    MotorDirection prev_motor_dir;
    MotorDirection current_motor_dir;
    int current_floor;
    int timer;
    STATE state;
    int queue[N_BUTTONS][N_FLOORS];
};

typedef struct elevator elevator;

void elev_update_dir(elevator* el, MotorDirection newdir);
int elev_has_order(elevator* el);
int elev_order_above(elevator* el);
int elev_order_below(elevator* el);
void elev_remove_last_order(elevator* el);
void elev_update_current_floor(elevator* el);
int elev_look_ahead(elevator* el);

MotorDirection elev_move_after_emergency(elevator* el);
void elev_btnlights_update(int queue[N_BUTTONS][N_FLOORS]);

