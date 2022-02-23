#pragma once
#include "elevio.h"
#include <stdio.h>
#include "stdlib.h"


typedef struct Queue{
    int queue[N_FLOORS][N_BUTTONS];
}Queue;


//Removing all orders
void clearQueue(Queue* q);
//Polling buttons and creating orders
void updateQueue(Queue* q);


//Debugging functions to nicely print the 4x3 matrix
void print_queue(Queue* q);