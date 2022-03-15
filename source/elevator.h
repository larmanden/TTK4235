/**
 * @file elevator.h
 * @brief The Elevator, it's states and corresponding functions for the Elevator.
 */

#pragma once
#include "driver/elevio.h"
#include "queue.h"

/**
 * @brief All possible states that the elevator can be in.
 * 
 * These states is used in the finite-state machine to control the elevator.
 */
typedef enum {
    IDLE = 0, 
    MOVING, EMERGENCY_STOP,
    DOOR_OPEN
}STATE;

/**
 * @brief The Elevator and it's member variables.
 * 
 */
struct Elevator{
    /**
     * @brief Elevator's previous motor-direction.
     * 
     * It is necessary to know the last direction for determining what way to start the elevator if it is stopped between two floors.
     */
    MotorDirection prev_motor_dir;
    MotorDirection current_motor_dir;
    /**
     * @brief Elevator's current floor.
     * 
     * When the elevator is between two floors @p current_floor will store the value of the last floor.
     */
    int current_floor;
    /**
     * @brief Stores the current state of the elevator.
     * 
     * The @p state is used for implementing control of the elevator in the fsm.h module.
     */
    STATE state;
    /**
     * @brief The elevator's queue system implemented as a 3x4 matrix. 
     * 
     * Relevant queue-functions can be found in queue.h
     */
    int queue[N_BUTTONS][N_FLOORS];
};

typedef struct Elevator Elevator;
/**
 * @brief Updates the elevators current direction to @p newdir as well as updating previous direction.
 * 
 * @param [in,out] el The elevator.
 * @param [in] newdir New direction for the elevator.
 */
void elevator_update_dir(Elevator* el, MotorDirection newdir);

/**
 * @brief Checks wether the elevator's queue has any orders.
 * 
 * @param [in] el The elevator.
 * @return 1 if there is a button pressed, 0 if not.
 */
int elevator_has_order(Elevator el);

/**
 * @brief Checks if there is an order above the elevator's current position.
 * 
 * @param [in] el The elevator.
 * @return 1 if there is an order above, 0 if not.
 */
int elevator_order_above(Elevator el);

/**
 * @brief Checks if there is an order below the elevator's current position.
 * 
 * @param [in] el The elevator.
 * @return 1 if there is an order below, 0 if not. 
 */
int elevator_order_below(Elevator el);

/**
 * @brief Removes all orders to the elevator's current floor.
 * 
 * @param [in, out] el The elevator.
 */
void elevator_remove_last_order(Elevator* el);

/**
 * @brief Updates the elevator's current floor if it is in a defined floor.
 * 
 * @param [in, out] el The elevator.
 */
void elevator_update_current_floor(Elevator* el);

/**
 * @brief Finds the furthest button pressed in the opposite direction of the elevator's current direction.
 * 
 * @param [in] el The elevator.
 * @return The floorindex to the furthest entry in opposite direction.
 */
int elevator_look_ahead(Elevator el);

/**
 * @brief Function for deciding wether to go upwards og downwards after an emergency between two floors.
 * 
 * @param [in] el The elevator.
 * @return MotorDirection, direction the elevator should go.
 */
MotorDirection elevator_move_after_emergency(Elevator el);

/**
 * @brief Turns on a buttonlight if the button is pressed. 
 * 
 * @param [in] queue The elevators queue system.
 */
void elevator_btnlights_update(int queue[N_BUTTONS][N_FLOORS]);

