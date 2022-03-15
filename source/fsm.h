/**
 * @file fsm.h
 * @author your name (you@domain.com)
 * @brief The elevators control system implemented as a finite state machine.
 */
#pragma once
#include "timer.h"
#include "elevator.h"

/**
 * @brief Initializing the elevator. Makes sure the elevator is in a defined floor before handling orders.
 * 
 * @param [in,out] el The elevator.
 */
void fsm_init(Elevator* el);

/**
 * @brief The main loop for the program. Controls the switching of the elevators given states.
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
 * @param [in,out] el The elevator.
 */
void fsm_moving(Elevator* el);

/**
 * @brief Running actions for the elevator when it has arrived at it's destination.
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