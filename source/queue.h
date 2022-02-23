#pragma once
#include "driver/elevio.h"
#include <stdio.h>
#include "stdlib.h"
#include "elevator.h"

typedef struct elevator elevator;

//Removing all ordersunknown type name 'elevator'
void clearQueue(elevator* el);
//Polling buttons and creating orders

//void updateQueue(elevator* el);


//Debugging functions to nicely print the 4x3 matrix
void print_queue(elevator* el);

void update_queue(elevator* el);


