#pragma once

#include <time.h>
#include <stdio.h>
#include "elevator.h"


#define DOOR_TIMER 3 

//Denne trengs vel egentlig ikke
typedef struct elevator elevator;

void timer_start(elevator* el);
int times_up(elevator* el);

int timer(elevator* el);