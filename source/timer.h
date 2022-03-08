#pragma once

#include <time.h>
#include <stdio.h>
#include "elevator.h"


#define DOOR_TIMER 3 

typedef struct elevator elevator;

void timer_start(elevator* el);
int times_up(elevator* el);