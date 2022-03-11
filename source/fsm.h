#pragma once

#include "timer.h"
#include "elevator.h"


void fsm_init(elevator* el);
void fsm_run(elevator* el);
void fsm_idle(elevator* el);
void fsm_moving(elevator* el);
void fsm_door_open(elevator* el);
void fsm_emergency_stop(elevator* el);