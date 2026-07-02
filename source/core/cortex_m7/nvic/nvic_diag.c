#include "nvic_diag.h"

#include <stdint.h>

#include "data_utils.h"
#include "nvic_types.h"

static const IntPriorityName_t IntPriorityLut[] = {
    {
        .priority = 0,
        .name = "Highest",
    },
    {
        .priority = 1,
        .name = "High6",
    },
    {
        .priority = 2,
        .name = "High5",
    },
    {
        .priority = 3,
        .name = "High4",
    },
    {
        .priority = 4,
        .name = "High3",
    },
    {
        .priority = 5,
        .name = "High2",
    },
    {
        .priority = 6,
        .name = "High1",
    },
    {
        .priority = 7,
        .name = "MedH",
    },
    {
        .priority = 8,
        .name = "MedL",
    },
    {
        .priority = 9,
        .name = "low1",
    },
    {
        .priority = 10,
        .name = "low2",
    },
    {
        .priority = 11,
        .name = "low3",
    },
    {
        .priority = 12,
        .name = "low4",
    },
    {
        .priority = 13,
        .name = "low5",
    },
    {
        .priority = 14,
        .name = "low6",
    },
    {
        .priority = 15,
        .name = "Lowest",
    },
};

#define CORTEX_M7_IRQ_NUM_DIAG                                                                                         \
    {                                                                                                                  \
        .name = "NMI",                                                                                                 \
        .int_n = -14,                                                                                                  \
    }, /*  */                                                                                                          \
        {                                                                                                              \
            .name = "HardFault",                                                                                       \
            .int_n = -13,                                                                                              \
        }, /*  */                                                                                                      \
        {                                                                                                              \
            .name = "MemoryManagement",                                                                                \
            .int_n = -12,                                                                                              \
        }, /* */                                                                                                       \
        {                                                                                                              \
            .name = "BusFault",                                                                                        \
            .int_n = -11,                                                                                              \
        }, /**/                                                                                                        \
        {                                                                                                              \
            .name = "UsageFault",                                                                                      \
            .int_n = -10,                                                                                              \
        }, /**/                                                                                                        \
        {                                                                                                              \
            .name = "SecureFault_Handler",                                                                             \
            .int_n = -9,                                                                                               \
        }, /**/                                                                                                        \
        {                                                                                                              \
            .name = "SVCall",                                                                                          \
            .int_n = -5,                                                                                               \
        }, /* */                                                                                                       \
        {                                                                                                              \
            .name = "DebugMonitor",                                                                                    \
            .int_n = -4,                                                                                               \
        }, /*  */                                                                                                      \
        {                                                                                                              \
            .name = "PendSV",                                                                                          \
            .int_n = -2,                                                                                               \
        }, /**/                                                                                                        \
        {                                                                                                              \
            .name = "SysTick",                                                                                         \
            .int_n = -1,                                                                                               \
        },

static const IntName_t IntNameLut[] = {CORTEX_M7_IRQ_NUM_DIAG};

const char* NvicToStr(int8_t int_n) {
    const char* name = "?";
    uint32_t i = 0;
    for(i = 0; i < ARRAY_SIZE(IntNameLut); i++) {
        if(int_n == IntNameLut[i].int_n) {
            name = IntNameLut[i].name;
            break;
        }
    }
    return name;
}

const char* IntPriToStr(int8_t priority) {
    const char* name = "?";
    uint32_t i = 0;
    for(i = 0; i < ARRAY_SIZE(IntPriorityLut); i++) {
        if(priority == IntPriorityLut[i].priority) {
            name = IntPriorityLut[i].name;
            break;
        }
    }
    return name;
}
