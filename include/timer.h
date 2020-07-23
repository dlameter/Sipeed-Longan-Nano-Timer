#ifndef TIMER_H
#define TIMER_H

#include "gd32vf103.h"

uint64_t timer_start();
int timer_diff_in_milliseconds(uint64_t time);

#endif
