#pragma once
#include "driver/elevio.h"
#include <stdio.h>
#include "stdlib.h"
#include "elevator.h"


typedef struct elevator elevator;

void clearQueue(elevator* el);
void print_queue(elevator* el);
//Handles lights as well
void update_queue(elevator* el);



