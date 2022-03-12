/**
 * @file elevio.h
 * @brief Library used for communcation with the physical elevator.
 */
#pragma once
#define N_FLOORS 4

/**
 * @brief Directions for the elevator used in @p elevio.
 * 
 */
typedef enum { 
    DIRN_DOWN   = -1,
    DIRN_STOP   = 0,
    DIRN_UP     = 1
} MotorDirection;


#define N_BUTTONS 3
/**
 * @brief Definiton of the different buttons that can be pressed.
 * 
 */
typedef enum { 
    BUTTON_HALL_UP      = 0,
    BUTTON_HALL_DOWN    = 1,
    BUTTON_CAB          = 2
} ButtonType;

/**
 * @brief Initializes the connection between the computer and the physical elevatormodel.
 * 
 */
void elevio_init(void);

/**
 * @brief Drives the elevatormodel in the direction given by @p dirn.
 * 
 * @param [in] dirn Direction for the elevator.
 */
void elevio_motorDirection(MotorDirection dirn);

/**
 * @brief Turns either on / off the buttonlamp at the given @p floor .
 * 
 * @param floor The floor at which we toggle the light.
 * @param button The type of button we toggle the light.
 * @param value 1 for turning on the light, 0 for turning off.
 */
void elevio_buttonLamp(int floor, ButtonType button, int value);

/**
 * @brief Toggles the light for indicating which floor the elevator is currently at. If it is between two floors the most recent floor will be indicated.
 * 
 * @param [in] floor The floor at which we turn on the light.
 */
void elevio_floorIndicator(int floor);

/**
 * @brief Toggles the lamp for indicating that the elevator's door is open.
 * 
 * @param [in] value 1 for turning on, 0 for turning off.
 */
void elevio_doorOpenLamp(int value);

/**
 * @brief Toggles the lamp for indicating that the stopbutton is pressed.
 * 
 * @param [in] value 1 for turning on, 0 for turning off.
 */
void elevio_stopLamp(int value);

/**
 * @brief Checks if a  button at a given floor is currently pressed.
 * 
 * @param [in] floor The floor.
 * @param [in] button Kind of button.
 * @return int 1 if the button is pressed, 0 if not.
 */
int elevio_callButton(int floor, ButtonType button);

/**
 * @brief Checks in what floor the elevator is.
 * 
 * @return int Returns -1 if the elevator is between two floors. Returns [0-3] for floor 1-4.
 */
int elevio_floorSensor(void);

/**
 * @brief Checks if the stopbutton is pressed.
 * 
 * @return int 1 if the button is pressed, 0 if not.
 */
int elevio_stopButton(void);

/**
 * @brief Checks if the obstruction toggle is active.
 * 
 * @return int 1 if active, 0 if not.
 */
int elevio_obstruction(void);

