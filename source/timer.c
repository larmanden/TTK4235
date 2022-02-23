#include "timer.h"


void timer_start(elevator* el){
    el->elev_timer = time(NULL);
}


//Checking if there has elapsed 3 seconds since last call on timer_start
int times_up(elevator* el){
    int current_time = time(NULL);

    if( (current_time - el->elev_timer) > 3){
        return 1;
    }
    else{
        return 0;
    }
}

int timer(elevator* el){
    timer_start(el);
    int diff = 0;
    do
    {
        diff = time(NULL) - el->elev_timer;
        //printf("%d",diff);
    } while (diff < 3);
    return 1;  
}
