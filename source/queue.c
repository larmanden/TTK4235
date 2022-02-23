#include "queue.h"




void clearQueue(elevator* el){
    for (int i = 0; i < N_BUTTONS; i++){
        for (int j = 0; j < N_FLOORS; j++){
            el->queue[i][j] = 0;
        }
    }
    el->queue[2][0] = -1;
    el->queue[0][3] = -1;
}


void print_queue(elevator* el){
     //Display the matrix
    for (int i = 0; i < N_BUTTONS; i++){
        printf("|");
        for (int j = 0; j < N_FLOORS; j++){
            printf("%d\t", el->queue[i][j]);
        }
        printf("|\n");
    }
}