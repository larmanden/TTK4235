/**
 * @file timer.h
 * @brief Functions to keep the door open for a  period of time.
 */

#pragma once
#include <time.h>
#include <stdio.h>
#include "elevator.h"

static time_t timer;
#define DOOR_TIME 3 

/**
 * @brief Starts the timer.
 */
void timer_start(void);

/**
 * @brief Checking wether the time
 * 
 * @return 1 if the time is up, 0 if not.
 */
int timer_done(void);