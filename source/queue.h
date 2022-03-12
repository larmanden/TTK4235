/**
 * @file queue.h
 * @author your name (you@domain.com)
 * @brief Functions for the elevators queue system. The queue is defined as a 3x4 matrix.
 * @version 0.1
 * @date 2022-03-11
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#pragma once
#include "driver/elevio.h"
#include <stdio.h>
#include "stdlib.h"
#include "elevator.h"

/**
 * @brief Clears the queue by setting all entries in the matrix to 0. Entries corresponding to buttons that doesn't exist is set to -1.
 * 
 * @param [in,out] queue Elevator's queue.
 */
void queue_clear(int queue[N_BUTTONS][N_FLOORS]);

/**
 * @brief Prints the queue to terminal.
 * 
 * @param [in] queue 
 */
void queue_print(int queue[N_BUTTONS][N_FLOORS]);

/**
 * @brief Updates entries in the queue if the given button is pressed on the panel.
 * 
 * @param [in, out] queue 
 */
void queue_update(int queue[N_BUTTONS][N_FLOORS]);

