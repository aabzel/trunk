#include "mcal_diag.h"

#include <stdio.h>
#include <string.h>

#include "log.h"
#include "std_includes.h"

#ifdef HAS_NUM_DIAG
#include "num_to_str.h"
#endif

const char* McalMoveModeToStr(MoveMode_t move_mode) {
    const char* name = "?";
    switch(move_mode) {
    case MOVE_MODE_POLLING:
        name = "Poll";
        break;
    case MOVE_MODE_INTERRUPT:
        name = "Int";
        break;
    case MOVE_MODE_DMA:
        name = "DMA";
        break;
    default:
        name = "?";
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

bool RegisterDiag(const uint32_t reg_val, const char* const name) {
    bool res = false;
    if(name) {
#ifdef HAS_NUM_DIAG
        LOG_WARNING(SYS, "Reg%s:0x%08X=%s", name, reg_val, utoa_bin32(reg_val));
        res = true;
#endif
    }
    return res;
}
