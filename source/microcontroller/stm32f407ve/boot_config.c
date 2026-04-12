#include "boot_config.h"

#include "microcontroller_const.h"
#include "std_includes.h"
#include "code_generator.h"
#include "macro_utils.h"

#ifdef HAS_LINKER_INFO
extern uint8_t __Core0_StackLimit, __Core0_StackTop  ;
#endif

const BootConfig_t  BootConfig[] = {
        { .num = 1,
          .fw_start_address = ROM_START,
          .valid =  true,
          .name="MBR",
#ifdef HAS_LINKER_INFO
          .stack_lim_address = (uint32_t) &__Core0_StackLimit,
          .stack_top_address = (uint32_t) &__Core0_StackTop,
#endif
        },
        { .num = 2,
          .fw_start_address = 0x08060000,
          .valid =  true,
          .name="BootLoader",
#ifdef HAS_LINKER_INFO
          .stack_lim_address = (uint32_t) &__Core0_StackLimit,
          .stack_top_address = (uint32_t) &__Core0_StackTop,
#endif
        },
};

BootHandle_t BootInstance[] = {
   { .num = 1, .valid = true, },
   { .num = 2, .valid = true, },
};

COMPONENT_GET_CNT(Boot, boot)
