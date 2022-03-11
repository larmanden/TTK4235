#include "queue.h"
void queue_clear(int queue[N_BUTTONS][N_FLOORS]){
    for (int btn = 0; btn < N_BUTTONS; btn++){
        for (int floor = 0; floor < N_FLOORS; floor++){
            queue[btn][floor] = 0;
        }
    }
    //Security measure since these buttons dont exist
    queue[1][0] = -1;
    queue[0][3] = -1;
}

void queue_print(int queue[N_BUTTONS][N_FLOORS]){
     printf("\n");
    for (int btn = 0; btn < N_BUTTONS; btn++){
        printf("|");
        for (int floor = 0; floor < N_FLOORS; floor++){
            printf("%d\t", queue[btn][floor]);
        }
        printf("|\n");
    }
    printf("\n");
    printf("\n");
}

void queue_update(int queue[N_BUTTONS][N_FLOORS]){
    for (int btn = 0; btn < N_BUTTONS; btn++){
        for (int floor = 0; floor < N_FLOORS; floor++){
           int btnPrsd = elevio_callButton(floor,btn);
           if(btnPrsd == 1){
               queue[btn][floor] = 1;
            }
        }
    }
}

