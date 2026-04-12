#include "stm32f407vg_diag.h"

#include "interrupt_types.h"

const IntNumInfo_t IntNumInfo[] = {

};

uint32_t interrupt_info_get_cnt(void) {
    uint32_t cnt = 0;
    cnt = ARRAY_SIZE(IntNumInfo);
    return cnt;
}
