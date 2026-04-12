#include "boot_config.h"

#include "microcontroller_const.h"
#include "std_includes.h"

const BootConfig_t BootConfig[] = {
    {
        .num = 0,
        .fw_start_address = ROM_START,
        //.stack_lim_address = &__Core0_StackLimit,
        //.stack_top_address = &__Core0_StackTop,
        .valid = true,
        .name = "Core0",
    },
};

BootHandle_t BootInstance[] = {
    {
        .num = 0,
        .valid = true,
    },

};

uint32_t boot_get_cnt(void) {
    uint32_t cnt = 0;
    uint32_t cnt1 = ARRAY_SIZE(BootConfig);
    uint32_t cnt2 = ARRAY_SIZE(BootInstance);
    if(cnt1 == cnt2) {
        cnt = cnt1;
    }
    return cnt;
}
