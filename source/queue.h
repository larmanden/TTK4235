#pragma once
#include "driver/elevio.h"
#include <stdio.h>
#include "stdlib.h"
#include "elevator.h"


typedef struct elevator elevator;

void queue_clear(int queue[N_BUTTONS][N_FLOORS]);
void queue_print(int queue[N_BUTTONS][N_FLOORS]);
void queue_update(int queue[N_BUTTONS][N_FLOORS]);

