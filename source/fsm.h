#pragma once

#include "elevator.h"
#include "timer.h"


void fsm_init(elevator* el);

//The state functions
void fsm_run(elevator* el);
void fsm_emergency_stop(elevator* el);
void fsm_moving(elevator* el);

