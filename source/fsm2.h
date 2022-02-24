#pragma once

#include "elevator.h"
#include "timer.h"

void fsm2_init(elevator* el);
void fsm2_idle(elevator* el);

void fsm2_moving(elevator* el);
