#include "queue.h"
void clearQueue(elevator* el){
    for (int btn = 0; btn < N_BUTTONS; btn++){
        for (int floor = 0; floor < N_FLOORS; floor++){
            el->queue[btn][floor] = 0;
        }
    }
    el->queue[1][0] = -1;
    el->queue[0][3] = -1;
}

void print_queue(elevator* el){
     printf("\n");
    for (int btn = 0; btn < N_BUTTONS; btn++){
        printf("|");
        for (int floor = 0; floor < N_FLOORS; floor++){
            printf("%d\t", el->queue[btn][floor]);
        }
        printf("|\n");
    }
    printf("\n");
    printf("\n");

}


void update_queue(elevator* el){
    for (int btn = 0; btn < N_BUTTONS; btn++){
        for (int floor = 0; floor < N_FLOORS; floor++){
           int btnPrsd = elevio_callButton(floor,btn);
           if(btnPrsd == 1){
               el->queue[btn][floor] = 1;
            }
        }
    }
    //Sjekke om koden fungerer uten disse, skal være nok å bare sette de en gang
    el->queue[1][0] = -1;
    el->queue[0][3] = -1;

     for (int btn = 0; btn < N_BUTTONS; btn++){
        for (int floor = 0; floor < N_FLOORS; floor++){
            if(el->queue[btn][floor] == 1){
                elevio_buttonLamp(floor, btn, 1);
            }
            else{
                elevio_buttonLamp(floor,btn, 0);
            }
        }
    }
}