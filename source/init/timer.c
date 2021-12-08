#include "init.h"


int TIME_TICK = 0;


int tick_1s = 0;

//0.01s
void TIMER0_UP_IRQHandler(void) {

    if (timer_interrupt_flag_get(TIMER0, TIMER_INT_FLAG_UP) != RESET) {
        tick_1s++;
        if (tick_1s >= 60) {
            TIME_TICK++;
            tick_1s = 0;
        }

        timer_interrupt_flag_clear(TIMER0, TIMER_INT_FLAG_UP);
    }
    
}
