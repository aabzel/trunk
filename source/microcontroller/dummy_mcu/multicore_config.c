#include "multicore_config.h"

#include "data_utils.h"
#include "microcontroller_const.h"

#if 0
#define CORE_1_VECTOR_ADDR 0x01200000U
//#define CORE_1_VECTOR_ADDR 0x01600000U (also works OK)
#define CORE_2_VECTOR_ADDR 0x01400000U
#endif

void Reset_Handler(void);
void Core1_Reset_Handler(void);
void Core2_Reset_Handler(void);

const MultiCoreConfig_t MultiCoreConfig[] = {
    {
            .num = 0,
            .vector_base = ROM_START,
            .reset_handler =(uint32_t) Reset_Handler,
            .valid = true,
    },
    {
            .num = 1,
            .vector_base = 0x01200000U,
            .reset_handler =(uint32_t) Core1_Reset_Handler,
            .valid = true,
    },
    {
            .num = 2,
            .vector_base = 0x01400000U,
            .reset_handler =(uint32_t) Core2_Reset_Handler,
            .valid = true,
    }
};

MultiCoreHandle_t MultiCoreInstance[] = {
    { .num = 0, .valid = true, },
    { .num = 1, .valid = true, },
    { .num = 2, .valid = true, }
};

uint32_t multicore_get_cnt(void) {
    uint32_t cnt = 0;
    uint32_t cnt1 = 0;
    uint32_t cnt2 = 0;
    cnt1 = ARRAY_SIZE(MultiCoreInstance);
    cnt2 = ARRAY_SIZE(MultiCoreConfig);
    if (cnt1 == cnt2) {
        cnt = cnt1;
    }
    return cnt;
}
