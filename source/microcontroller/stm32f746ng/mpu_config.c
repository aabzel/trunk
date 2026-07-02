#include "mpu_config.h"

#include "data_utils.h"
#include "macro_utils.h"
#include "cortex_m7_const.h"

char gMpuTestDataBanRead[64] = {64};
char gMpuTestDataBanAll[128] = {126};
char gMpuTestDataBanWrite[32] = {32};

extern void __Core0_StackLimit;
extern void __Core0_HeapLimit;

#ifdef HAS_MULTICORE
extern void __Core1_StackLimit;
extern void __Core2_StackLimit;

extern void __Core1_HeapLimit;
extern void __Core2_HeapLimit;
#endif

#ifdef HAS_MULTICORE
#define MPU_REGIONS_MULTICORE_STACK                                                                   \
        {                                                                                             \
        .num = 10, .Cores = { .core1 = 1,  },                                                         \
        .start = (uint32_t)&__Core1_StackLimit, .size = MPU_STACK_HEAP_REGION_SIZE,                             \
        .on_off = true, .valid = true, .name = "Stack1Lim",                                           \
        .permission = {.read=1, .write=0, .execute=0,.bufferable=0, .cached=0, .shareable=0,},        \
        },                                                                                            \
        {                                                                                             \
        .num = 9, .Cores = { .core2 = 1,  },                                                          \
        .start =(uint32_t) &__Core2_StackLimit, .size =MPU_STACK_HEAP_REGION_SIZE,                              \
        .on_off = true, .valid = true, .name = "Stack2Lim",                                           \
        .permission = {.read=1, .write=0, .execute=0,.bufferable=0, .cached=0, .shareable=0,},        \
        },
#else
#define MPU_REGIONS_MULTICORE_STACK
#endif

#define MPU_REGIONS_STACK                                                                                              \
        MPU_REGIONS_MULTICORE_STACK                                                                                    \
        {                                                                                                              \
        .num = 8, .Cores = { .core0 = 1,  },                                                                           \
        .start = (uint32_t) &__Core0_StackLimit, .size =MPU_STACK_HEAP_REGION_SIZE,                                               \
        .on_off = true, .valid = true, .name = "Stack0Lim",                                                            \
        .permission = {.read=1, .write=0, .execute=0,.bufferable=0, .cached=0, .shareable=0,},                         \
        },


#ifdef HAS_MULTICORE
#define MPU_REGIONS_PROTECT_PERIPHERAL                                                                                 \
        {                                                                                                              \
        .num = 11,                                                                                                     \
        .Cores = { .core0 = 0,  .core1 = 1, .core2 = 1,},                                                              \
        .start = (uint32_t)ARM_CORTEX_M7_PERIPHERAL, .size = ARM_CORTEX_M7_PERIPHERAL_SIZE,                            \
        .on_off = true, .valid = true,                                                                                 \
        .name = "ProtPeriph",                                                                                          \
        .permission = {.read=0, .write=0, .execute=0, .bufferable=0, .cached=0, .shareable=0,},                        \
        },

#else
#define MPU_REGIONS_PROTECT_PERIPHERAL
#endif

#define MPU_REGIONS_TEST_ONLY                                                                                          \
        {                                                                                                              \
        .num = 7,                                                                                                      \
        .Cores = { .core0 = 1,},                                                                                       \
        .start = (uint32_t) gMpuTestDataBanWrite, .size = sizeof(gMpuTestDataBanWrite),                                \
        .on_off = true, .valid = true,                                                                                 \
        .name = "BanWrite",                                                                                            \
        .permission = {.read=1, .write=0, .execute=1, .bufferable=0, .cached=0, .shareable=0,},                        \
        },                                                                                                             \
        {                                                                                                              \
        .num = 6,                                                                                                      \
        .Cores = { .core0 = 1, },                                                                                      \
        .start = (uint32_t) gMpuTestDataBanRead, .size = sizeof(gMpuTestDataBanRead),                                  \
        .on_off = true, .valid = true, .name = "BanRead",                                                              \
        .permission = {.read=0, .write=1, .execute=1,.bufferable=0, .cached=0, .shareable=0,},                         \
        },                                                                                                             \
        {                                                                                                              \
        .num = 5,                                                                                                      \
        .Cores = { .core0 = 1, },                                                                                      \
        .start = (uint32_t) gMpuTestDataBanAll, .size = sizeof(gMpuTestDataBanAll),                                    \
        .on_off = true, .valid = true, .name = "BanAll",                                                               \
        .permission = {.read=0, .write=0, .execute=0,.bufferable=0, .cached=0, .shareable=0,},                         \
        },

#ifdef HAS_MULTICORE
#define MPU_REGIONS_HEAP_MULTICORE                                                                                     \
        {                                                                                                              \
        .num = 4, .Cores = { .core1 = 1,  },                                                                           \
        .start =(uint32_t) &__Core1_HeapLimit, .size =MPU_STACK_HEAP_REGION_SIZE,                                                \
        .on_off = true, .valid = true, .name = "Heap1Lim",                                                             \
        .permission = {.read=0, .write=0, .execute=0,.bufferable=0, .cached=0, .shareable=0,},                         \
        },                                                                                                             \
        {                                                                                                              \
        .num = 3, .Cores = { .core2 = 1,  },                                                                           \
        .start = (uint32_t)&__Core2_HeapLimit, .size =MPU_STACK_HEAP_REGION_SIZE,                                                \
        .on_off = true, .valid = true, .name = "Heap2Lim",                                                             \
        .permission = {.read=0, .write=0, .execute=0,.bufferable=0, .cached=0, .shareable=0,},                         \
        },
#else
#define MPU_REGIONS_HEAP_MULTICORE
#endif

#define MPU_REGIONS_HEAP     MPU_REGIONS_HEAP_MULTICORE                                                                \
        {                                                                                                              \
        .num = 2, .Cores = { .core0 = 1,  },                                                                           \
        .start = (uint32_t) (&__Core0_HeapLimit)-MPU_STACK_HEAP_REGION_SIZE, .size = MPU_STACK_HEAP_REGION_SIZE,                  \
        .on_off = true, .valid = true, .name = "Heap0Lim",                                                             \
        .permission = {.read=0, .write=0, .execute=0,.bufferable=0, .cached=0, .shareable=0,},                         \
        },

static const MpuRegionConfig_t MpuRegions[] = {
        MPU_REGIONS_STACK
        MPU_REGIONS_HEAP
        MPU_REGIONS_TEST_ONLY
        MPU_REGIONS_PROTECT_PERIPHERAL
        {
        .num = 1, .start =(uint32_t) 0x00000000, .size =64*1024,
        .Cores = { .core0 = 1, .core1 = 1, .core2 = 1, },
        .on_off = true, .valid = true, .name = "ITCM",
        .permission = {.read = 0, .write = 0, .execute = 0, .bufferable = 0, .cached = 0, .shareable = 0,},
        },
        {
        .num = 0, .Cores = { .core0 = 1, .core1 = 1, .core2 = 1, },
        .start = (uint32_t)DFLASH_START , .size = DFLASH_SIZE,
        .on_off = true, .valid = true, .name = "DFLASH",
        .permission = {.read = 1, .write = 1, .execute = 0, .bufferable = 0, .cached = 0, .shareable = 0,},
        },
};

const MpuConfig_t SECTION_CFG_DATA MpuConfig[] = {
    { .num = 0, .Region = MpuRegions, .region_cnt = ARRAY_SIZE(MpuRegions), .valid = true, .name = "MPU0", },

};

MpuHandle_t MpuInstance[] = {
    { .num = 0, .valid = true, },

};

COMPONENT_GET_CNT(Mpu, mpu)
