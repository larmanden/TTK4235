/**
 * @file queue.h
 * @brief Library for the elevator's queue system. 
 * 
 * The queue is implemented as a 3x4 matrix. 
 */
#pragma once
#include "driver/elevio.h"
#include <stdio.h>
#include "stdlib.h"
#include "elevator.h"

/**
 * @brief Clears the queue by setting all entries in the matrix to 0. 
 * 
 * Security feature: entries corresponding to buttons that doesn't exist is set to -1.
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
 * Loops thorugh the matrix and checks if the specific button is pressed on the elevator-panel.
 * 
 * @param [in, out] queue 
 */
void queue_update(int queue[N_BUTTONS][N_FLOORS]);

