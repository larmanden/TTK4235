/**
 * @file fsm.h
 * @brief The elevators control system implemented as a finite state machine.
 */
#pragma once
#include "timer.h"
#include "elevator.h"

/**
 * @brief Initializing the elevator. Makes sure the elevator is in a defined floor before handling orders.
 * 
 * If the elevator is between two floors it will go downwards until it is in a defined floor.
 * 
 * @param [in,out] el The elevator.
 */
void fsm_init(Elevator* el);

/**
 * @brief The main loop for the program. Controls the switching of the elevators given states.
 * 
 * The main control system for the elevator implementes as a finite-state machine modeled by a game-loop switching on the elevator's state.
 * 
 * @param [in,out] el The elevator.
 */
void fsm_run(Elevator* el);

/**
 * @brief Running actions for the elevator when it is waiting for an order.
 * 
 * @param [in,out] el The elevator.
 */
void fsm_idle(Elevator* el);

/**
 * @brief Running actions for the elevator when it is handling an order.
 * 
 * First part of the function checks wether the elevator should stop if it is in a defined floor. Second part of the function decides what direction to drive the elevator based on a given order in the queue-matrix.
 * 
 * @param [in,out] el The elevator.
 */
void fsm_moving(Elevator* el);

/**
 * @brief Running actions for the elevator when it has arrived at it's destination.
 * 
 * Makes use of the timer module to keep the elevator's door open for 3 seconds.
 * 
 * @param [in,out] el The elevator.
 */
void fsm_door_open(Elevator* el);

/**
 * @brief Running actions for the elevator when the stopbutton is pressed.
 * 
 * @param [in,out] el The elevator.
 */
void fsm_emergency_stop(Elevator* el);