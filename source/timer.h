/**
 * @file timer.h
 * @brief Timer library.
 * Is used to keep the Elevator's door open for 3 seconds.
 */

#pragma once
#include <time.h>
#include <stdio.h>


/**
 * @brief @p timer stores the time.
 * 
 */
static time_t timer;

/**
 * @brief Definition of the timer's duration.
 * 
 */
#define TIMER_DURATION 3 

/**
 * @brief Starts the timer by overwriting  @p timer variable to current time.
 */
void timer_start(void);

/**
 * @brief Checks if the timer is done.
 * 
 * @return 1 if the time is up, 0 if not.
 */
int timer_done(void);