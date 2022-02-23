#pragma once

#include "driver/elevio.h"


typedef struct{
     int queue[N_FLOORS][N_BUTTONS];
}Queue;


int updateQueue(Queue* q);
int clearQueue(Queue* q);




