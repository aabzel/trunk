#include "software_timer_diag.h"

#include "software_timer.h"

char* SwTimDir2Str(SwTimerCntDir_t code) {
    char* name = "?";
    switch(code) {
    case SW_TIMER_CNT_DIR_UP:
        name = "Up";
        break;
    case SW_TIMER_CNT_DIR_DOWN:
        name = "Down";
        break;
    default:
        name = "?";
        break;
    }
    return name;
}

char* SwTimMode2Str(SwTimerMode_t code) {
    char* name = "?";
    switch(code) {
    case SW_TIMER_MODE_SINGLE:
        name = "Single";
        break;
    case SW_TIMER_MODE_CONTINUOUS:
        name = "Contin";
        break;
    default:
        name = "?";
        break;
    }
    return name;
}

const char* SwTimNum2Str(uint32_t sw_tim_num) {
    const char* name = "?";
    const SoftwareTimerConfig_t* Node = SwTimerGetConfigNode(sw_tim_num);
    if(Node) {
        name = Node->name;
    }
    return name;
}
