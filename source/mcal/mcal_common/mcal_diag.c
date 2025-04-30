#include "mcal_diag.h"

#include <stdio.h>
#include <string.h>

#include "log.h"
#include "std_includes.h"

const char* McalMoveModeToStr(MoveMode_t move_mode) {
    const char* name = "?";
    switch((uint32_t)move_mode) {
    case MOVE_MODE_INTERRUPT:
        name = "INTERR";
        break;
    case MOVE_MODE_DMA:
        name = "DMA";
        break;
    }

    return name;
}

bool McalOkCntToRes(uint32_t okCnt, uint32_t dataQty) {
    bool res = false;
    if(dataQty == okCnt) {
        res = true;
    }
    return res;
}
