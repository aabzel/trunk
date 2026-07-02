#include "boot_config.h"

#include "microcontroller_const.h"
#include "std_includes.h"

extern uint32_t __Core0_StackLimit, __Core0_StackTop  ;

const BootConfig_t BootConfig[] = {
    {
        .num = 0,
        .fw_start_address = ROM_START,
        .stack_lim_address = (uint32_t) &__Core0_StackLimit,
        .stack_top_address = (uint32_t) &__Core0_StackTop,
        .valid = true,
        .name = "Core0",
    },
};

BootHandle_t BootInstance[] = {
   { .num = 0, .valid = true, },
};


uint32_t boot_get_cnt(void) {
    uint32_t cnt = 0;
    uint32_t cnt_node = 0;
    uint32_t cnt_cfg = 0;
    cnt_node = ARRAY_SIZE( BootInstance);
    cnt_cfg = ARRAY_SIZE( BootConfig);
    if(cnt_cfg <= cnt_node) {
        cnt = cnt_cfg;
    }
    return cnt;
}
