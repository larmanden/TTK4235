#include "timer.h"


void timer_start(elevator* el){
    el->elev_timer = time(NULL);
}


int times_up(elevator* el){
    int current_time = time(NULL);

    if( (current_time - el->elev_timer) > 3){
        return 1;
    }
    else{
        return 0;
    }
}
