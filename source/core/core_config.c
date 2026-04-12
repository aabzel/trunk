#include "core_config.h"

#include "data_utils.h"

#ifdef HAS_LINKER_INFO
extern uint8_t __Core0_StackTop;
extern uint8_t __Core0_StackLimit;
#endif

#ifdef HAS_MULTICORE
extern uint8_t __Core1_StackTop;
extern uint8_t __Core1_StackLimit;

extern uint8_t __Core2_StackTop;
extern uint8_t __Core2_StackLimit;
#endif

const CoreConfig_t CoreConfig[] = {
    { .num = 0,
      .valid = true,
      .name = "CORE0",
#ifdef HAS_LINKER_INFO
            .stack_top = (uint32_t)&__Core0_StackTop,
            .stack_limit = (uint32_t)&__Core0_StackLimit,
#endif
    },
#ifdef HAS_MULTICORE
    { .num = 1, .stack_top = (uint32_t)&__Core1_StackTop, .stack_limit = (uint32_t)&__Core1_StackLimit, .valid = true, .name = "CORE1",    },
    { .num = 2, .stack_top = (uint32_t)&__Core2_StackTop, .stack_limit = (uint32_t)&__Core2_StackLimit, .valid = true, .name = "CORE2",    },
#endif
};

CoreHandle_t CoreInstance[] = {
    { .num = 0, .valid = true,    },
#ifdef HAS_MULTICORE
    { .num = 1, .valid = true,    },
    { .num = 2, .valid = true,    },
#endif
};

COMPONENT_GET_CNT(Core, core)
