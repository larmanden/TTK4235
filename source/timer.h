/**
 * @file timer.h
 * @author your name (you@domain.com)
 * @brief Functions to keep the door open for a  period of time.
 * @version 0.1
 * @date 2022-03-11
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#pragma once
#include <time.h>
#include <stdio.h>
#include "elevator.h"

#define DOOR_TIMER 3 
/**
 * @brief Starts the timer.
 * 
 * @param [in,out] el The elevator.
 */
void timer_start(elevator* el);

/**
 * @brief Checking wether the time is up.
 * 
 * @param [in, out] el The elevator.
 * @return 1 if the time is up, 0 if not.
 */
int times_up(elevator* el);