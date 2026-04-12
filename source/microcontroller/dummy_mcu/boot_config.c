#include "boot_config.h"

#include "microcontroller_const.h"
#include "std_includes.h"

extern uint8_t __Core0_StackLimit, __Core0_StackTop  ;
#ifdef HAS_MULTICORE
extern uint8_t __Core1_StackLimit, __Core1_StackTop  ;
extern uint8_t __Core2_StackLimit, __Core2_StackTop  ;
#endif

const BootConfig_t BootConfig[] = {
        { .num = 0,
          .fw_start_address = ROM_START,
          .stack_lim_address = (uint32_t) &__Core0_StackLimit,
          .stack_top_address = (uint32_t) &__Core0_StackTop,
          .valid =  true,
          .name="Core0",
        },
#ifdef HAS_MULTICORE
        {
          .num = 1,
          .fw_start_address = 0x01200000,
          .stack_lim_address = (uint32_t) &__Core1_StackLimit,
          .stack_top_address = (uint32_t) &__Core1_StackTop,
          .valid =  true,
          .name="Core1",
        },

        { .num=2,
          .fw_start_address = 0x01400000,
          .stack_lim_address = (uint32_t) &__Core2_StackLimit,
          .stack_top_address = (uint32_t) &__Core2_StackTop,
          .valid =  true, .name="Core2",
        },
#endif

};

BootHandle_t BootInstance[] = {
   { .num = 0, .valid = true, },
#ifdef HAS_MULTICORE

   { .num = 1, .valid = true, },
   { .num = 2, .valid = true, },
#endif
};

uint32_t boot_get_cnt(void) {
    uint32_t cnt = 0;
    uint32_t cnt1 = ARRAY_SIZE(BootConfig);
    uint32_t cnt2 = ARRAY_SIZE(BootInstance);
    if(cnt1==cnt2){
        cnt = cnt1;
    }
    return cnt;
}
