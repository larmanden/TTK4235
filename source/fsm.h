#pragma once

/* #include <stdio.h>
#include "stdlib.h"
#include <unistd.h> */

#include "timer.h"
#include "queue.h"
#include "elevator.h"


void fsm_init(elevator* el);
void fsm_run(elevator* el);
void fsm_idle(elevator* el);
void fsm_moving(elevator* el);
void fsm_door_open(elevator* el);
void fsm_emergency_stop(elevator* el);