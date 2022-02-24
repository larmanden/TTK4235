#include "queue.h"
void clearQueue(elevator* el){
    for (int i = 0; i < N_BUTTONS; i++){
        for (int j = 0; j < N_FLOORS; j++){
            el->queue[i][j] = 0;
        }
    }
    el->queue[1][0] = -1;
    el->queue[0][3] = -1;
}

void print_queue(elevator* el){
     //Display the matrix
     printf("\n");
    for (int i = 0; i < N_BUTTONS; i++){
        printf("|");
        for (int j = 0; j < N_FLOORS; j++){
            printf("%d\t", el->queue[i][j]);
        }
        printf("|\n");
    }
    printf("\n");
    printf("\n");

}


void update_queue(elevator* el){
    for (int i = 0; i < N_BUTTONS; i++){
        for (int j = 0; j < N_FLOORS; j++){
           int btnPrsd = elevio_callButton(j,i);
           if(btnPrsd == 1){
               el->queue[i][j] = 1;
            }
        }
    }
    el->queue[1][0] = -1;
    el->queue[0][3] = -1;
}