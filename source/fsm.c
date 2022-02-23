#include "fsm.h"


void fsm_init(elevator el){
    //Sørger for forbindelse til heisserver
    elevio_init();

    //Ensure that the elevator is at a defined floor and state-> idle

    //Koden under skal kjøres hvis heisen ikke er i en etasje
    while(elevio_floorSensor() == -1){
        elevio_motorDirection(DIRN_DOWN);
    }

    if(elevio_floorSensor() != -1){
            //Elevator is in a defined floor
            elevio_motorDirection(DIRN_STOP);
            //updateCurrentFloor(el);
            el.state = IDLE;
    }
}



void fsm_run(elevator el){
    while (1){
        if(elevio_stopButton()){
            el.state = EMERGENCY_STOP;
        }

        switch (el.state)
        {
        case IDLE:
            printf('IDLE\n');
            break;
        case EMERGENCY_STOP:
            fsm_emergency_stop(el);
            break;
        default:
            break;
        }
    }
    
};


void fsm_emergency_stop(elevator el) {
    elevio_motorDirection(DIRN_STOP);
    el.state = EMERGENCY_STOP;

    printf('EMERGENCY STOP');

    /* //Sjekke om i etasje, åpne døren og holde til stoppknapp er sluppet deretter 3sek
    if(elevio_floorSensor() != -1){
        timer_start(); //"Åpne døren"
        while( elevio_stopButton() ){
            printf('Åpen dør, venter');
            timer_start(); 
            el->state = EMERGENCY_STOP;
        }
    }
    //Polle stopknappen
    if(!elevio_stopButton()){
        el->state = IDLE;
        printf('NÅ er jeg i IDLE');
    } */
}

void fsm_moving(){
    elevio_motorDirection(DIRN_UP);
}