#include "boot_config.h"

#include "microcontroller_const.h"
#include "std_includes.h"
#include "code_generator.h"

extern uint32_t __Core0_StackLimit, __Core0_StackTop  ;

const BootConfig_t SECTION_CFG_DATA BootConfig[] = {
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

COMPONENT_GET_CNT(Boot, boot)
