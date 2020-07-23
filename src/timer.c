#include "timer.h"

uint64_t timer_start() {
    uint64_t time, tmp;

    tmp = get_timer_value();
    do {
        time = get_timer_value();
    } while (time == tmp);

    return time;
}

int timer_diff_in_milliseconds(uint64_t time) {
    uint64_t delta_time = get_timer_value() - time;
    
    return (int) delta_time / 20000;
}
