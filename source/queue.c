#include "queue.h"



void clearQueue(Queue* q){
    for (int i = 0; i < N_FLOORS; i++){
        for (int j = 0; i < N_BUTTONS; i++){
            q->queue[i][j] = 0;
        }
    }
    q->queue[0][2] = -1;
    q->queue[3][0] = -1;
}


void print_queue(Queue* q){
    /* Display the matrix */
    for (i = 0; i < 4; i++){
        for (j = 0; j < 3; j++){
            printf("%d\t", q->queue[i][j]);
        }
        printf("\n");
    }
}
