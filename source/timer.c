#include "timer.h"

void timer_start(void){
    timer = time(NULL);
}

int timer_done(void){
    time_t current_time = time(NULL);
    if( (current_time - timer) >= TIMER_DURATION){
        return 1;
    }
    else{return 0;}
}
