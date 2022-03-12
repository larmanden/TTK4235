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
 */
typedef enum {
    IDLE = 0, 
    MOVING, EMERGENCY_STOP,
    DOOR_OPEN
}STATE;

/**
 * @brief The elevators and it's corresponding member variables.
 * 
 */
struct elevator{
    MotorDirection prev_motor_dir;
    MotorDirection current_motor_dir;
    int current_floor;
    int timer;
    STATE state;
    int queue[N_BUTTONS][N_FLOORS];
};

typedef struct elevator elevator;
/**
 * @brief Updates the elevators current direction to @p newdir as well as updating previous direction.
 * 
 * @param [in,out] el The elevator.
 * @param [in] newdir New direction for the elevator.
 */
void elevator_update_dir(elevator* el, MotorDirection newdir);

/**
 * @brief Checks wether the queue has any orders.
 * 
 * @param [in,out] el The elevator.
 * @return 1 if there is a button pressed, 0 if not.
 */
int elevator_has_order(elevator* el);

/**
 * @brief Checks if there is an order above the elevator's current position.
 * 
 * @param [in,out] el The elevator.
 * @return 1 if there is an order above, 0 if not.
 */
int elevator_order_above(elevator* el);

/**
 * @brief Checks if there is an order below the elevator's current position.
 * 
 * @param [in,out] el The elevator.
 * @return 1 if there is an order below, 0 if not. 
 */
int elevator_order_below(elevator* el);

/**
 * @brief Removes all orders to the elevator's current floor.
 * 
 * @param [in, out] el The elevator.
 */
void elevator_remove_last_order(elevator* el);

/**
 * @brief Updates the elevator's current floor if it is in a defined floor.
 * 
 * @param [in, out] el The elevator.
 */
void elevator_update_current_floor(elevator* el);

/**
 * @brief Finds the furthest button pressed in the opposite direction of the elevator's current direction.
 * 
 * @param [in,out] el The elevator.
 * @return The floorindex to the furthest entry in opposite direction.
 */
int elevator_look_ahead(elevator* el);

/**
 * @brief Function for deciding wether to go upwards og downwards after an emergency between two floors.
 * 
 * @param [in,out] el The elevator.
 * @return MotorDirection, direction the elevator should go.
 */
MotorDirection elevator_move_after_emergency(elevator* el);

/**
 * @brief Turns on a buttonlight if the button is pressed. 
 * 
 * @param [in] queue The elevators queue system.
 */
void elevator_btnlights_update(int queue[N_BUTTONS][N_FLOORS]);

