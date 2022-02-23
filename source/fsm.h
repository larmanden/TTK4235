#pragma once

#include "elevator.h"

void fsm_init(elevator el);

void fsm_run(elevator el);
void fsm_emergency_stop(elevator el);

void fsm_moving(elevator el);