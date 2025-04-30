#include "timer_calc_diag.h"

#include <stdio.h>

const char* TimerArtetyToStr(const TimerArtety_t* const Node) {
    static char name[80] = {0};
    if(Node) {
        snprintf(name, sizeof(name), "PSC:%2u,PER:%3u", Node->prescaler, Node->period);
    }
    return name;
}
