#include "timer_mcal.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

//#include "c_defines_generated.h"
#include "at32_misc.h"
#include "bit_utils.h"
#include "clock.h"
#include "clock_custom_const.h"
#include "common_diag.h"
#include "core_driver.h"
#include "data_utils.h"
#include "float_utils.h"
#include "log.h"
#include "microcontroller_const.h"
#include "time_mcal.h"
#include "timer_custom_drv.h"
#include "timer_custom_types.h"
#include "timer_utils.h"
#include "utils_math.h"

const Reg32_t TimerReg[] = {
    {
        .valid = true,
        .name = "TMRx_CTRL1",
        .offset = 0x00,
    },
    {
        .valid = true,
        .name = "TMRx_CTRL2",
        .offset = 0x04,
    },
    {
        .valid = true,
        .name = "TMRx_STCTRL",
        .offset = 0x08,
    },
    {
        .valid = true,
        .name = "TMRx_IDEN",
        .offset = 0x0C,
    },
    {
        .valid = true,
        .name = "TMRx_ISTS",
        .offset = 0x10,
    },
    {
        .valid = true,
        .name = "TMRx_SWEVT",
        .offset = 0x14,
    },
    {
        .valid = true,
        .name = "TMRx_CM1",
        .offset = 0x18,
    },
    {
        .valid = true,
        .name = "TMRx_CM2",
        .offset = 0x1C,
    },
    {
        .valid = true,
        .name = "TMRx_CCTRL",
        .offset = 0x20,
    },
    {
        .valid = true,
        .name = "TMRx_CVAL",
        .offset = 0x24,
    },
    {
        .valid = true,
        .name = "TMRx_DIV",
        .offset = 0x28,
    },
    {
        .valid = true,
        .name = "TMRx_PR",
        .offset = 0x2C,
    },
    {
        .valid = true,
        .name = "TMRx_C1DT",
        .offset = 0x34,
    },
    {
        .valid = true,
        .name = "TMRx_C2DT",
        .offset = 0x38,
    },
    {
        .valid = true,
        .name = "TMRx_C3DT",
        .offset = 0x3C,
    },
    {
        .valid = true,
        .name = "TMRx_C4DT",
        .offset = 0x40,
    },
    {
        .valid = true,
        .name = "TMRx_DMACTRL",
        .offset = 0x48,
    },
    {
        .valid = true,
        .name = "TMRx_DMADT",
        .offset = 0x4C,
    },
    {
        .valid = true,
        .name = "TMR2/5_RMP",
        .offset = 0x50,
    },
};

uint32_t timer_reg_cnt(void) {
    uint32_t cnt = ARRAY_SIZE(TimerReg);
    return cnt;
}

static tmr_channel_select_type TimerChannelToArteryTimerChannel(TimerCapComChannel_t channel) {
    tmr_channel_select_type tmr_channel = TMR_SELECT_CHANNEL_1;
    switch((uint32_t)channel) {
    case TIMER_CC_CHAN_1:
        tmr_channel = TMR_SELECT_CHANNEL_1;
        break;
    case TIMER_CC_CHAN_2:
        tmr_channel = TMR_SELECT_CHANNEL_2;
        break;
    case TIMER_CC_CHAN_3:
        tmr_channel = TMR_SELECT_CHANNEL_3;
        break;
    case TIMER_CC_CHAN_4:
        tmr_channel = TMR_SELECT_CHANNEL_4;
        break;
    case TIMER_CC_CHAN_5:
#ifdef HAS_AT32F43X
        tmr_channel = TMR_SELECT_CHANNEL_5;
#endif // HAS_AT32F43X
        break;
    default:
        LOG_ERROR(TIMER, "ErrCh:%u", channel);
        break;
    }
    return tmr_channel;
}

uint8_t timer_get_width(uint32_t timer_base) {
    uint8_t width = 0;
    return width;
}

#define TIMER1_CHANNELS                                                                                                \
    {                                                                                                                  \
        .Pad =                                                                                                         \
            {                                                                                                          \
                .port = PORT_E,                                                                                        \
                .pin = 9,                                                                                              \
            },                                                                                                         \
        .timer_num = 1,                                                                                                \
        .out_channel = 1,                                                                                              \
        .valid = true,                                                                                                 \
    },                                                                                                                 \
        {                                                                                                              \
            .Pad =                                                                                                     \
                {                                                                                                      \
                    .port = PORT_E,                                                                                    \
                    .pin = 11,                                                                                         \
                },                                                                                                     \
            .timer_num = 1,                                                                                            \
            .out_channel = 2,                                                                                          \
            .valid = true,                                                                                             \
        },                                                                                                             \
        {                                                                                                              \
            .Pad =                                                                                                     \
                {                                                                                                      \
                    .port = PORT_E,                                                                                    \
                    .pin = 13,                                                                                         \
                },                                                                                                     \
            .timer_num = 1,                                                                                            \
            .out_channel = 3,                                                                                          \
            .valid = true,                                                                                             \
        },                                                                                                             \
        {                                                                                                              \
            .Pad =                                                                                                     \
                {                                                                                                      \
                    .port = PORT_E,                                                                                    \
                    .pin = 14,                                                                                         \
                },                                                                                                     \
            .timer_num = 1,                                                                                            \
            .out_channel = 4,                                                                                          \
            .valid = true,                                                                                             \
        },

#define TIMER2_CHANNELS                                                                                                \
    {                                                                                                                  \
        .Pad =                                                                                                         \
            {                                                                                                          \
                .port = PORT_A,                                                                                        \
                .pin = 0,                                                                                              \
            },                                                                                                         \
        .timer_num = 2,                                                                                                \
        .out_channel = 1,                                                                                              \
        .valid = true,                                                                                                 \
    },                                                                                                                 \
        {                                                                                                              \
            .Pad =                                                                                                     \
                {                                                                                                      \
                    .port = PORT_A,                                                                                    \
                    .pin = 1,                                                                                          \
                },                                                                                                     \
            .timer_num = 2,                                                                                            \
            .out_channel = 2,                                                                                          \
            .valid = true,                                                                                             \
        },                                                                                                             \
        {                                                                                                              \
            .Pad =                                                                                                     \
                {                                                                                                      \
                    .port = PORT_A,                                                                                    \
                    .pin = 2,                                                                                          \
                },                                                                                                     \
            .timer_num = 2,                                                                                            \
            .out_channel = 3,                                                                                          \
            .valid = true,                                                                                             \
        },                                                                                                             \
        {                                                                                                              \
            .Pad =                                                                                                     \
                {                                                                                                      \
                    .port = PORT_A,                                                                                    \
                    .pin = 3,                                                                                          \
                },                                                                                                     \
            .timer_num = 2,                                                                                            \
            .out_channel = 4,                                                                                          \
            .valid = true,                                                                                             \
        },

#define TIMER3_CHANNELS                                                                                                \
    {                                                                                                                  \
        .Pad =                                                                                                         \
            {                                                                                                          \
                .port = PORT_C,                                                                                        \
                .pin = 6,                                                                                              \
            },                                                                                                         \
        .timer_num = 3,                                                                                                \
        .out_channel = 1,                                                                                              \
        .valid = true,                                                                                                 \
    },                                                                                                                 \
        {                                                                                                              \
            .Pad =                                                                                                     \
                {                                                                                                      \
                    .port = PORT_C,                                                                                    \
                    .pin = 7,                                                                                          \
                },                                                                                                     \
            .timer_num = 3,                                                                                            \
            .out_channel = 2,                                                                                          \
            .valid = true,                                                                                             \
        },                                                                                                             \
        {                                                                                                              \
            .Pad =                                                                                                     \
                {                                                                                                      \
                    .port = PORT_C,                                                                                    \
                    .pin = 8,                                                                                          \
                },                                                                                                     \
            .timer_num = 3,                                                                                            \
            .out_channel = 3,                                                                                          \
            .valid = true,                                                                                             \
        },                                                                                                             \
        {                                                                                                              \
            .Pad =                                                                                                     \
                {                                                                                                      \
                    .port = PORT_C,                                                                                    \
                    .pin = 9,                                                                                          \
                },                                                                                                     \
            .timer_num = 3,                                                                                            \
            .out_channel = 4,                                                                                          \
            .valid = true,                                                                                             \
        },

#define TIMER4_CHANNELS                                                                                                \
    {                                                                                                                  \
        .Pad =                                                                                                         \
            {                                                                                                          \
                .port = PORT_D,                                                                                        \
                .pin = 12,                                                                                             \
            },                                                                                                         \
        .timer_num = 4,                                                                                                \
        .out_channel = 1,                                                                                              \
        .valid = true,                                                                                                 \
    },                                                                                                                 \
        {                                                                                                              \
            .Pad =                                                                                                     \
                {                                                                                                      \
                    .port = PORT_D,                                                                                    \
                    .pin = 13,                                                                                         \
                },                                                                                                     \
            .timer_num = 4,                                                                                            \
            .out_channel = 2,                                                                                          \
            .valid = true,                                                                                             \
        },                                                                                                             \
        {                                                                                                              \
            .Pad =                                                                                                     \
                {                                                                                                      \
                    .port = PORT_D,                                                                                    \
                    .pin = 14,                                                                                         \
                },                                                                                                     \
            .timer_num = 4,                                                                                            \
            .out_channel = 3,                                                                                          \
            .valid = true,                                                                                             \
        },                                                                                                             \
        {                                                                                                              \
            .Pad =                                                                                                     \
                {                                                                                                      \
                    .port = PORT_D,                                                                                    \
                    .pin = 15,                                                                                         \
                },                                                                                                     \
            .timer_num = 4,                                                                                            \
            .out_channel = 4,                                                                                          \
            .valid = true,                                                                                             \
        },

#define TIMER5_CHANNELS                                                                                                \
    {                                                                                                                  \
        .Pad =                                                                                                         \
            {                                                                                                          \
                .port = PORT_H,                                                                                        \
                .pin = 2,                                                                                              \
            },                                                                                                         \
        .timer_num = 5,                                                                                                \
        .out_channel = 1,                                                                                              \
        .valid = true,                                                                                                 \
    },                                                                                                                 \
        {                                                                                                              \
            .Pad =                                                                                                     \
                {                                                                                                      \
                    .port = PORT_C,                                                                                    \
                    .pin = 10,                                                                                         \
                },                                                                                                     \
            .timer_num = 5,                                                                                            \
            .out_channel = 2,                                                                                          \
            .valid = true,                                                                                             \
        },                                                                                                             \
        {                                                                                                              \
            .Pad =                                                                                                     \
                {                                                                                                      \
                    .port = PORT_C,                                                                                    \
                    .pin = 11,                                                                                         \
                },                                                                                                     \
            .timer_num = 5,                                                                                            \
            .out_channel = 3,                                                                                          \
            .valid = true,                                                                                             \
        },                                                                                                             \
        {                                                                                                              \
            .Pad =                                                                                                     \
                {                                                                                                      \
                    .port = PORT_F,                                                                                    \
                    .pin = 10,                                                                                         \
                },                                                                                                     \
            .timer_num = 5,                                                                                            \
            .out_channel = 4,                                                                                          \
            .valid = true,                                                                                             \
        },

#define TIMER8_CHANNELS                                                                                                \
    {                                                                                                                  \
        .Pad =                                                                                                         \
            {                                                                                                          \
                .port = PORT_C,                                                                                        \
                .pin = 6,                                                                                              \
            },                                                                                                         \
        .timer_num = 8,                                                                                                \
        .out_channel = 1,                                                                                              \
        .valid = true,                                                                                                 \
    },                                                                                                                 \
        {                                                                                                              \
            .Pad =                                                                                                     \
                {                                                                                                      \
                    .port = PORT_C,                                                                                    \
                    .pin = 7,                                                                                          \
                },                                                                                                     \
            .timer_num = 8,                                                                                            \
            .out_channel = 2,                                                                                          \
            .valid = true,                                                                                             \
        },                                                                                                             \
        {                                                                                                              \
            .Pad =                                                                                                     \
                {                                                                                                      \
                    .port = PORT_C,                                                                                    \
                    .pin = 8,                                                                                          \
                },                                                                                                     \
            .timer_num = 8,                                                                                            \
            .out_channel = 3,                                                                                          \
            .valid = true,                                                                                             \
        },                                                                                                             \
        {                                                                                                              \
            .Pad =                                                                                                     \
                {                                                                                                      \
                    .port = PORT_C,                                                                                    \
                    .pin = 9,                                                                                          \
                },                                                                                                     \
            .timer_num = 8,                                                                                            \
            .out_channel = 4,                                                                                          \
            .valid = true,                                                                                             \
        },

#define TIMER9_CHANNELS                                                                                                \
    {                                                                                                                  \
        .Pad =                                                                                                         \
            {                                                                                                          \
                .port = PORT_E,                                                                                        \
                .pin = 5,                                                                                              \
            },                                                                                                         \
        .timer_num = 9,                                                                                                \
        .out_channel = 1,                                                                                              \
        .valid = true,                                                                                                 \
    },                                                                                                                 \
        {                                                                                                              \
            .Pad =                                                                                                     \
                {                                                                                                      \
                    .port = PORT_E,                                                                                    \
                    .pin = 6,                                                                                          \
                },                                                                                                     \
            .timer_num = 9,                                                                                            \
            .out_channel = 2,                                                                                          \
            .valid = true,                                                                                             \
        },

#define TIMER10_CHANNELS                                                                                               \
    {                                                                                                                  \
        .Pad =                                                                                                         \
            {                                                                                                          \
                .port = PORT_F,                                                                                        \
                .pin = 6,                                                                                              \
            },                                                                                                         \
        .timer_num = 10,                                                                                               \
        .out_channel = 1,                                                                                              \
        .valid = true,                                                                                                 \
    },

#define TIMER11_CHANNELS                                                                                               \
    {                                                                                                                  \
        .Pad =                                                                                                         \
            {                                                                                                          \
                .port = PORT_F,                                                                                        \
                .pin = 7,                                                                                              \
            },                                                                                                         \
        .timer_num = 11,                                                                                               \
        .out_channel = 1,                                                                                              \
        .valid = true,                                                                                                 \
    },                                                                                                                 \
        {                                                                                                              \
            .Pad =                                                                                                     \
                {                                                                                                      \
                    .port = PORT_C,                                                                                    \
                    .pin = 12,                                                                                         \
                },                                                                                                     \
            .timer_num = 11,                                                                                           \
            .out_channel = 1,                                                                                          \
            .valid = true,                                                                                             \
        },                                                                                                             \
        {                                                                                                              \
            .Pad =                                                                                                     \
                {                                                                                                      \
                    .port = PORT_B,                                                                                    \
                    .pin = 9,                                                                                          \
                },                                                                                                     \
            .timer_num = 11,                                                                                           \
            .out_channel = 1,                                                                                          \
            .valid = true,                                                                                             \
        },

#define TIMER12_CHANNELS                                                                                               \
    {                                                                                                                  \
        .Pad =                                                                                                         \
            {                                                                                                          \
                .port = PORT_B,                                                                                        \
                .pin = 14,                                                                                             \
            },                                                                                                         \
        .timer_num = 12,                                                                                               \
        .out_channel = 1,                                                                                              \
        .valid = true,                                                                                                 \
    },                                                                                                                 \
        {                                                                                                              \
            .Pad =                                                                                                     \
                {                                                                                                      \
                    .port = PORT_B,                                                                                    \
                    .pin = 15,                                                                                         \
                },                                                                                                     \
            .timer_num = 12,                                                                                           \
            .out_channel = 2,                                                                                          \
            .valid = true,                                                                                             \
        },

#define TIMER13_CHANNELS                                                                                               \
    {                                                                                                                  \
        .Pad =                                                                                                         \
            {                                                                                                          \
                .port = PORT_F,                                                                                        \
                .pin = 8,                                                                                              \
            },                                                                                                         \
        .timer_num = 13,                                                                                               \
        .out_channel = 1,                                                                                              \
        .valid = true,                                                                                                 \
    },                                                                                                                 \
        {                                                                                                              \
            .Pad =                                                                                                     \
                {                                                                                                      \
                    .port = PORT_A,                                                                                    \
                    .pin = 6,                                                                                          \
                },                                                                                                     \
            .timer_num = 13,                                                                                           \
            .out_channel = 1,                                                                                          \
            .valid = true,                                                                                             \
        },

#define TIMER14_CHANNELS                                                                                               \
    {                                                                                                                  \
        .Pad =                                                                                                         \
            {                                                                                                          \
                .port = PORT_F,                                                                                        \
                .pin = 9,                                                                                              \
            },                                                                                                         \
        .timer_num = 14,                                                                                               \
        .out_channel = 1,                                                                                              \
        .valid = true,                                                                                                 \
    },                                                                                                                 \
        {                                                                                                              \
            .Pad =                                                                                                     \
                {                                                                                                      \
                    .port = PORT_A,                                                                                    \
                    .pin = 7,                                                                                          \
                },                                                                                                     \
            .timer_num = 14,                                                                                           \
            .out_channel = 1,                                                                                          \
            .valid = true,                                                                                             \
        },

// TMR20_CH1
#define TIMER20_1_CHANNELS                                                                                             \
    {                                                                                                                  \
        .Pad =                                                                                                         \
            {                                                                                                          \
                .port = PORT_E,                                                                                        \
                .pin = 2,                                                                                              \
            },                                                                                                         \
        .timer_num = 20,                                                                                               \
        .out_channel = 1,                                                                                              \
        .valid = true,                                                                                                 \
    },                                                                                                                 \
        {                                                                                                              \
            .Pad =                                                                                                     \
                {                                                                                                      \
                    .port = PORT_B,                                                                                    \
                    .pin = 2,                                                                                          \
                },                                                                                                     \
            .timer_num = 20,                                                                                           \
            .out_channel = 1,                                                                                          \
            .valid = true,                                                                                             \
        },                                                                                                             \
        {                                                                                                              \
            .Pad =                                                                                                     \
                {                                                                                                      \
                    .port = PORT_F,                                                                                    \
                    .pin = 12,                                                                                         \
                },                                                                                                     \
            .timer_num = 20,                                                                                           \
            .out_channel = 1,                                                                                          \
            .valid = true,                                                                                             \
        },

// TMR20_CH2
#define TIMER20_2_CHANNELS                                                                                             \
    {                                                                                                                  \
        .Pad =                                                                                                         \
            {                                                                                                          \
                .port = PORT_F,                                                                                        \
                .pin = 13,                                                                                             \
            },                                                                                                         \
        .timer_num = 20,                                                                                               \
        .out_channel = 2,                                                                                              \
        .valid = true,                                                                                                 \
    },                                                                                                                 \
        {                                                                                                              \
            .Pad =                                                                                                     \
                {                                                                                                      \
                    .port = PORT_E,                                                                                    \
                    .pin = 3,                                                                                          \
                },                                                                                                     \
            .timer_num = 20,                                                                                           \
            .out_channel = 2,                                                                                          \
            .valid = true,                                                                                             \
        },                                                                                                             \
        {                                                                                                              \
            .Pad =                                                                                                     \
                {                                                                                                      \
                    .port = PORT_C,                                                                                    \
                    .pin = 2,                                                                                          \
                },                                                                                                     \
            .timer_num = 20,                                                                                           \
            .out_channel = 2,                                                                                          \
            .valid = true,                                                                                             \
        },

// TMR20_CH3
#define TIMER20_3_CHANNELS                                                                                             \
    {                                                                                                                  \
        .Pad =                                                                                                         \
            {                                                                                                          \
                .port = PORT_F,                                                                                        \
                .pin = 2,                                                                                              \
            },                                                                                                         \
        .timer_num = 20,                                                                                               \
        .out_channel = 3,                                                                                              \
        .valid = true,                                                                                                 \
    },                                                                                                                 \
        {                                                                                                              \
            .Pad =                                                                                                     \
                {                                                                                                      \
                    .port = PORT_F,                                                                                    \
                    .pin = 14,                                                                                         \
                },                                                                                                     \
            .timer_num = 20,                                                                                           \
            .out_channel = 3,                                                                                          \
            .valid = true,                                                                                             \
        },                                                                                                             \
        {                                                                                                              \
            .Pad =                                                                                                     \
                {                                                                                                      \
                    .port = PORT_C,                                                                                    \
                    .pin = 8,                                                                                          \
                },                                                                                                     \
            .timer_num = 20,                                                                                           \
            .out_channel = 3,                                                                                          \
            .valid = true,                                                                                             \
        },

// TMR20_CH4
#define TIMER20_4_CHANNELS                                                                                             \
    {                                                                                                                  \
        .Pad =                                                                                                         \
            {                                                                                                          \
                .port = PORT_F,                                                                                        \
                .pin = 3,                                                                                              \
            },                                                                                                         \
        .timer_num = 20,                                                                                               \
        .out_channel = 4,                                                                                              \
        .valid = true,                                                                                                 \
    },                                                                                                                 \
        {                                                                                                              \
            .Pad =                                                                                                     \
                {                                                                                                      \
                    .port = PORT_F,                                                                                    \
                    .pin = 6,                                                                                          \
                },                                                                                                     \
            .timer_num = 20,                                                                                           \
            .out_channel = 4,                                                                                          \
            .valid = true,                                                                                             \
        },                                                                                                             \
        {                                                                                                              \
            .Pad =                                                                                                     \
                {                                                                                                      \
                    .port = PORT_F,                                                                                    \
                    .pin = 15,                                                                                         \
                },                                                                                                     \
            .timer_num = 20,                                                                                           \
            .out_channel = 4,                                                                                          \
            .valid = true,                                                                                             \
        },                                                                                                             \
        {                                                                                                              \
            .Pad =                                                                                                     \
                {                                                                                                      \
                    .port = PORT_E,                                                                                    \
                    .pin = 1,                                                                                          \
                },                                                                                                     \
            .timer_num = 20,                                                                                           \
            .out_channel = 4,                                                                                          \
            .valid = true,                                                                                             \
        },

#define TIMER20_CHANNELS                                                                                               \
    TIMER20_1_CHANNELS                                                                                                 \
    TIMER20_2_CHANNELS                                                                                                 \
    TIMER20_3_CHANNELS                                                                                                 \
    TIMER20_4_CHANNELS

#define TIMER_CHANNELS_ALL                                                                                             \
    TIMER1_CHANNELS                                                                                                    \
    TIMER2_CHANNELS                                                                                                    \
    TIMER3_CHANNELS                                                                                                    \
    TIMER4_CHANNELS                                                                                                    \
    TIMER5_CHANNELS                                                                                                    \
    TIMER8_CHANNELS                                                                                                    \
    TIMER9_CHANNELS                                                                                                    \
    TIMER10_CHANNELS                                                                                                   \
    TIMER11_CHANNELS                                                                                                   \
    TIMER12_CHANNELS                                                                                                   \
    TIMER13_CHANNELS                                                                                                   \
    TIMER14_CHANNELS                                                                                                   \
    TIMER20_CHANNELS

static const TimerChannelInfo_t TimerChannelInfo[] = {TIMER_CHANNELS_ALL};

const TimerChannelInfo_t* TimerChannelGetInfo(uint8_t num, TimerCapComChannel_t channel) {
    TimerChannelInfo_t* ChannelInfo = NULL;
    uint16_t i = 0;
    for(i = 0; i < ARRAY_SIZE(TimerChannelInfo); i++) {
        if(TimerChannelInfo[i].valid) {
            if(num == TimerChannelInfo[i].timer_num) {
                if(channel == TimerChannelInfo[i].out_channel) {
                    ChannelInfo = &TimerChannelInfo[i];
                    break;
                }
            }
        }
    }
    return ChannelInfo;
}

/*Info from datasheet*/
static const TimerInfo_t TimerInfo[] = {
#ifdef TMR1
    {
        .resolution_bit = 16,
        .clock_bus = CLOCK_BUS_APB2,
        .num = 1,
        .TMRx = TMR1,
        .valid = true,
        .irq_n = TMR1_OVF_TMR10_IRQn,
        .clock_type = CRM_TMR1_PERIPH_CLOCK,
    },
#endif /**/

#ifdef TMR2
    {
        .clock_bus = CLOCK_BUS_APB1,
        .num = 2,
        .TMRx = TMR2,
        .valid = true,
        .resolution_bit = 32,
        .irq_n = TMR2_GLOBAL_IRQn,
        .clock_type = CRM_TMR2_PERIPH_CLOCK,
    },
#endif /**/

#ifdef TMR3
    {
        .clock_bus = CLOCK_BUS_APB1,
        .num = 3,
        .TMRx = TMR3,
        .valid = true,
        .resolution_bit = 16,
        .irq_n = TMR3_GLOBAL_IRQn,
        .clock_type = CRM_TMR3_PERIPH_CLOCK,
    },
#endif /**/

#ifdef TMR4
    {
        .clock_bus = CLOCK_BUS_APB1,
        .num = 4,
        .TMRx = TMR4,
        .valid = true,
        .resolution_bit = 16,
        .irq_n = TMR4_GLOBAL_IRQn,
        .clock_type = CRM_TMR4_PERIPH_CLOCK,
    },
#endif /**/

#ifdef TMR5
    {
        .clock_bus = CLOCK_BUS_APB1,
        .num = 5,
        .TMRx = TMR5,
        .valid = true,
        .resolution_bit = 32,
        .irq_n = TMR5_GLOBAL_IRQn,
        .clock_type = CRM_TMR5_PERIPH_CLOCK,
    },
#endif /**/

#ifdef TMR6
    {
        .clock_bus = CLOCK_BUS_APB1,
        .num = 6,
        .TMRx = TMR6,
        .valid = true,
        .resolution_bit = 16,
        .irq_n = TMR6_DAC_GLOBAL_IRQn,
        .clock_type = CRM_TMR6_PERIPH_CLOCK,
    },
#endif /**/

#ifdef TMR7
    {
        .clock_bus = CLOCK_BUS_APB1,
        .num = 7,
        .TMRx = TMR7,
        .resolution_bit = 16,
        .valid = true,
        .irq_n = TMR7_GLOBAL_IRQn,
        .clock_type = CRM_TMR7_PERIPH_CLOCK,
    },
#endif /**/

#ifdef TMR8
    {
        .num = 8,
        .clock_bus = CLOCK_BUS_APB2,
        .resolution_bit = 16,
        .TMRx = TMR8,
        .valid = true,
#ifdef HAS_AT32F43X
        .irq_n = TMR8_OVF_TMR13_IRQn,
#endif // HAS_AT32F43X
        .clock_type = CRM_TMR8_PERIPH_CLOCK,
    },
#endif /**/

#ifdef TMR9
    {
        .clock_bus = CLOCK_BUS_APB2,
        .num = 9,
        .TMRx = TMR9,
        .valid = true,
        .resolution_bit = 16,
        .irq_n = TMR1_BRK_TMR9_IRQn,
        .clock_type = CRM_TMR9_PERIPH_CLOCK,
    },
#endif /**/

#ifdef TMR10
    {
        .clock_bus = CLOCK_BUS_APB2,
        .num = 10,
        .TMRx = TMR10,
        .resolution_bit = 16,
        .valid = true,
        .irq_n = TMR1_OVF_TMR10_IRQn,
        .clock_type = CRM_TMR10_PERIPH_CLOCK,
    },
#endif /**/

#ifdef TMR11
    {
        .clock_bus = CLOCK_BUS_APB2,
        .num = 11,
        .TMRx = TMR11,
        .valid = true,
        .resolution_bit = 16,
        .irq_n = TMR1_TRG_HALL_TMR11_IRQn,
        .clock_type = CRM_TMR11_PERIPH_CLOCK,
    },
#endif /**/

#ifdef TMR12
    {
        .clock_bus = CLOCK_BUS_APB1,
        .num = 12,
        .TMRx = TMR12,
        .valid = true,
        .resolution_bit = 16,
        .irq_n = TMR8_BRK_TMR12_IRQn,
        .clock_type = CRM_TMR12_PERIPH_CLOCK,
    },
#endif /**/

#ifdef TMR13
    {
        .clock_bus = CLOCK_BUS_APB1,
        .num = 13,
        .TMRx = TMR13,
        .valid = true,
        .resolution_bit = 16,
        .irq_n = TMR8_OVF_TMR13_IRQn,
        .clock_type = CRM_TMR13_PERIPH_CLOCK,
    },
#endif /**/

#ifdef TMR14
    {
        .clock_bus = CLOCK_BUS_APB1,
        .num = 14,
        .TMRx = TMR14,
        .valid = true,
        .resolution_bit = 16,
        .irq_n = TMR8_TRG_HALL_TMR14_IRQn,
        .clock_type = CRM_TMR14_PERIPH_CLOCK,
    },
#endif /**/

#ifdef TMR20
    {
        .clock_bus = CLOCK_BUS_APB2,
        .num = 20,
        .TMRx = TMR20,
        .valid = true,
        .resolution_bit = 16,
        .irq_n = TMR20_OVF_IRQn,
        .clock_type = CRM_TMR20_PERIPH_CLOCK,
    },
#endif /**/

};

TimerInfo_t* TimerGetInfo(uint8_t num) {
    TimerInfo_t* Info = NULL;
    uint16_t i = 0;
    for(i = 0; i < ARRAY_SIZE(TimerInfo); i++) {
        if(TimerInfo[i].valid) {
            if(num == TimerInfo[i].num) {
                Info = &TimerInfo[i];
                break;
            }
        }
    }
    return Info;
}

static bool timer_is_valid_period(uint8_t num, uint32_t period) {
    bool res = false;
    TimerInfo_t* Info = TimerGetInfo(num);
    if(Info) {
        uint32_t max_val = (uint32_t)(ipow(2, (uint32_t)Info->resolution_bit) - 2);
        if(period < max_val) {
            res = true;
        } else {
            LOG_ERROR(TIMER, "TIMER%u,TooBigPeriod,period:%u,MaxVal:%u", num, period, max_val);
            res = false;
        }
    }
    return res;
}

bool timer_out_channel_pad_get(uint8_t num, TimerCapComChannel_t channel, Pad_t* const Pad) {
    bool res = false;
    const TimerChannelInfo_t* ChannelNode = TimerChannelGetInfo(num, channel);
    if(ChannelNode) {
        *Pad = ChannelNode->Pad;
        res = true;
    }

    return res;
}

/*called from ISR*/
bool timer_compare_set(uint8_t num, TimerCapComChannel_t channel, uint32_t compare_value) {
    bool res = false;
    // LOG_INFO(TIMER, "TIMER%u CompareSet Channel:%u,Compare:%u", num, channel, compare_value);
    TimerInfo_t* Info = TimerGetInfo(num);
    if(Info) {
        if(Info->TMRx) {
            TimerHandle_t* Node = TimerGetNode(num);
            if(Node) {

                // tmr_counter_enable(Info->TMRx, FALSE);
                // tmr_period_buffer_enable(Info->TMRx, FALSE);
                // tmr_output_enable(Info->TMRx, FALSE);

                // tmr_output_config_type tmr_oc_init_structure;

                tmr_output_default_para_init(&Node->tmr_oc_init_structure);

                Node->tmr_oc_init_structure.oc_mode = TMR_OUTPUT_CONTROL_PWM_MODE_A;
                Node->tmr_oc_init_structure.oc_idle_state = TRUE; // FALSE
                Node->tmr_oc_init_structure.oc_output_state = TRUE;
                Node->tmr_oc_init_structure.oc_polarity = TMR_OUTPUT_ACTIVE_HIGH;
                Node->tmr_oc_init_structure.occ_output_state = FALSE;
                Node->tmr_oc_init_structure.occ_polarity = TMR_OUTPUT_ACTIVE_HIGH;

                tmr_channel_select_type tmr_channel = TimerChannelToArteryTimerChannel(channel);
                tmr_output_channel_config(Info->TMRx, tmr_channel, &Node->tmr_oc_init_structure);
                tmr_channel_value_set(Info->TMRx, tmr_channel, compare_value);

                tmr_output_enable(Info->TMRx, TRUE);
                // tmr_period_buffer_enable(Info->TMRx, TRUE);

                tmr_counter_enable(Info->TMRx, TRUE);

                res = true;
                //  res = timer_channel_ctrl(  num,   channel, true);
            }
        }
    }
    return res;
}

int32_t timer_bus_clock_get(uint8_t num) {
    int32_t clock_hz = -1;
    TimerInfo_t* Info = TimerGetInfo(num);
    if(Info) {
        crm_clocks_freq_type clocks_struct = {0};
        crm_clocks_freq_get(&clocks_struct);
        switch(Info->clock_bus) {
        case CLOCK_BUS_APB1:
            clock_hz = (int32_t)(2 * clocks_struct.apb1_freq);
            break;
        case CLOCK_BUS_APB2:
            clock_hz = (int32_t)(2 * clocks_struct.apb2_freq);
            break; /*!< apb2 bus clock frequency */
        default:
            break;
        }
    }
    LOG_PARN(TIMER, "TIMER%u BusClck:%u Hz", num, clock_hz);
    return clock_hz;
}

tmr_type* timer_get_ptr(uint8_t num) {
    tmr_type* TMRx = NULL;
    TimerInfo_t* Info = TimerGetInfo(num);
    if(Info) {
        TMRx = Info->TMRx;
    }

    return TMRx;
}

uint32_t timer_period_get(uint8_t num) {
    uint32_t period = 0;
    TimerInfo_t* Info = TimerGetInfo(num);
    if(Info) {
        period = tmr_period_value_get(Info->TMRx);
    }
    return period;
}

uint64_t timer_period_get_us(uint8_t num) {
    uint64_t real_period_us = 0;
    double period_s = timer_period_get_s(num);
    real_period_us = sec_to_usec(period_s);
    return real_period_us;
}

#if 0
static bool timer_period_set_ll(TimerHandle_t* Node, uint32_t period) {
    bool res = false;
    res = timer_is_valid_period(Node->num, period);
    if(res) {

        if(Node) {
            tmr_period_value_set(Node->TMRx, period);
            res = true;
        } else {
            LOG_ERROR(TIMER, "TIMER%u InfoErr", Node->num);
        }
    } else {
        LOG_ERROR(TIMER, "TIMER%u InvalidPeriod", Node->num, period);
    }
    return res;
}
#endif

bool timer_period_set_ll(TimerHandle_t* const Node, uint32_t period) {
    bool res = false;
    if(Node) {
        res = timer_is_valid_period(Node->num, period);
        if(res) {
            TimerInfo_t* Info = TimerGetInfo(Node->num);
            if(Info) {
                tmr_period_value_set(Info->TMRx, period);
                res = true;
            } else {
                res = false;
                LOG_ERROR(TIMER, "TIMER%u,InfoErr", Node->num);
            }
        } else {
            res = false;
            LOG_ERROR(TIMER, "TIMER%u,InvalidPeriod:%u", Node->num, period);
        }
    }
    return res;
}

bool timer_period_set(uint8_t num, uint32_t period) {
    bool res = false;
    TimerHandle_t* Node = TimerGetNode(num);
    if(Node) {
        res = timer_period_set_ll(Node, period);
    } else {
        res = false;
        LOG_ERROR(TIMER, "TIMER%u,NodeErr", num);
    }
    return res;
}
#if 0
bool timer_period_set_s(uint8_t num, double period_s) {
    bool res = false;
    double tick_s = timer_tick_get_s(num);
    uint32_t value = (uint32_t)(period_s / tick_s);
    LOG_INFO(TIMER, "TIMER%u SetPeriod:%f s,Tick:%f s,Period:%u", num, period_s, tick_s, value);
    res = timer_period_set(num, value);
    if(res) {
        LOG_INFO(TIMER, "TIMER%u Period %f SetOk", num, period_s);
    } else {
        LOG_ERROR(TIMER, "TIMER%u Period %f SetErr", num, period_s);
    }
    return res;
}
#endif

uint32_t timer_prescaler_get(uint8_t num) {
    uint32_t prescaler = 0xFF;
    TimerInfo_t* Info = TimerGetInfo(num);
    if(Info) {
        prescaler = tmr_div_value_get(Info->TMRx);
    }
    return prescaler;
}

static tmr_channel_select_type TimerChannelToArteryChannel(TimerCapComChannel_t channel) {
    tmr_channel_select_type tmr_channel = TMR_SELECT_CHANNEL_1;
    switch(channel) {
    case TIMER_CC_CHAN_1:
        tmr_channel = TMR_SELECT_CHANNEL_1;
        break;
    case TIMER_CC_CHAN_2:
        tmr_channel = TMR_SELECT_CHANNEL_2;
        break;
    case TIMER_CC_CHAN_3:
        tmr_channel = TMR_SELECT_CHANNEL_3;
        break;
    case TIMER_CC_CHAN_4:
        tmr_channel = TMR_SELECT_CHANNEL_4;
        break;
    case TIMER_CC_CHAN_5:
#ifdef HAS_AT32F43X
        tmr_channel = TMR_SELECT_CHANNEL_5;
#endif // HAS_AT32F43X
        break;
    default:
        break;
    }
    return tmr_channel;
}

static tmr_channel_select_type TimerChannelToArteryChannelComplimentary(TimerCapComChannel_t channel) {
    tmr_channel_select_type tmr_channel = TMR_SELECT_CHANNEL_1;
    switch(channel) {
    case TIMER_CC_CHAN_1:
        tmr_channel = TMR_SELECT_CHANNEL_1C;
        break;
    case TIMER_CC_CHAN_2:
        tmr_channel = TMR_SELECT_CHANNEL_2C;
        break;
    case TIMER_CC_CHAN_3:
        tmr_channel = TMR_SELECT_CHANNEL_3C;
        break;
    default:
        break;
    }
    return tmr_channel;
}

uint32_t timer_ccc_val_get(uint8_t num, TimerCapComChannel_t channel) {
    uint32_t channel_value = 0;
    TimerInfo_t* Info = TimerGetInfo(num);
    if(Info) {
        tmr_channel_select_type tmr_channel = TMR_SELECT_CHANNEL_1C;
        tmr_channel = TimerChannelToArteryChannelComplimentary(channel);
        channel_value = tmr_channel_value_get(Info->TMRx, tmr_channel);
    }
    return channel_value;
}

uint32_t timer_cc_val_get(uint8_t num, TimerCapComChannel_t channel) {
    uint32_t channel_value = 0;
    TimerInfo_t* Info = TimerGetInfo(num);
    if(Info) {
        tmr_channel_select_type tmr_channel = TMR_SELECT_CHANNEL_1;
        tmr_channel = TimerChannelToArteryChannel(channel);
        channel_value = tmr_channel_value_get(Info->TMRx, tmr_channel);
    }
    return channel_value;
}

#if 0
static bool timer_out_channel_stop(uint8_t num, TimerOutChannel_t channel) {
    bool res = false;
    return res;
}
static bool timer_out_channel_start(uint8_t num, TimerOutChannel_t channel) {
    bool res = false;

    return res;
}
#endif

// bool timer_set_status(uint8_t num, bool on_off) { return 0; }

uint8_t timer_get_bitness(uint8_t num) { return 0; }

bool timer_get_status(uint8_t num) {
    uint8_t status = 0xFF;
    return status;
}

uint32_t timer_get_auto_reload(uint8_t num) {
    uint32_t auto_reload = 0;

    return auto_reload;
}

uint32_t timer_get_us32(uint8_t num) {
    uint32_t up_time_us = 0;
    TimerHandle_t* Node = TimerGetNode(num);
    if(Node) {
        double up_time_s = 0.0;
        up_time_s = timer_get_s(num);
        up_time_us = (uint32_t)sec_to_usec(up_time_s);
    }
    return up_time_us;
}

TimerDir_t timer_get_dir(uint8_t num) {
    TimerDir_t dir = CNT_DIR_UNDEF;

    return dir;
}

#if 0
static int8_t TimInstance2Num(tmr_type* Instance) {
    int8_t num = -1;
#ifdef TIM1
    if(TIM1 == Instance) {
        num = 1;
    }
#endif /**/

#ifdef TIM2
    if(TIM2 == Instance) {
        num = 2;
    }
#endif /**/

#ifdef TIM3
    if(TIM3 == Instance) {
        num = 3;
    }
#endif /**/

#ifdef TIM4
    if(TIM4 == Instance) {
        num = 4;
    }
#endif /**/

#ifdef TIM5
    if(TIM5 == Instance) {
        num = 5;
    }
#endif /**/

#ifdef TIM6
    if(TIM6 == Instance) {
        num = 6;
    }
#endif /**/

#ifdef TIM7
    if(TIM7 == Instance) {
        num = 7;
    }
#endif /**/

#ifdef TIM8
    if(TIM8 == Instance) {
        num = 8;
    }
#endif /**/

#ifdef TIM9
    if(TIM9 == Instance) {
        num = 9;
    }
#endif /**/

#ifdef TIM10
    if(TIM10 == Instance) {
        num = 10;
    }
#endif /**/

#ifdef TIM11
    if(TIM11 == Instance) {
        num = 11;
    }
#endif /**/

    return num;
}
#endif

bool timer_ctrl(uint8_t num, bool on_off) {
    bool res = false;
    LOG_WARNING(TIMER, "TIMER%u,%s", num, OnOffToStr(on_off));
    TimerInfo_t* Info = TimerGetInfo(num);
    if(Info) {
        confirm_state new_state = OnOffToConfirmState(on_off);
        tmr_counter_enable(Info->TMRx, new_state);
        res = true;
    }
    return res;
}

bool timer_counter_set(uint8_t num, uint32_t counter) {
    bool res = false;
    TimerInfo_t* Info = TimerGetInfo(num);
    if(Info) {
        tmr_counter_value_set(Info->TMRx, counter);
        res = true;
    }
    return res;
}
/*
 * counter_percent 0....100
 */
bool timer_counter_set_percent_u(uint8_t num, uint8_t counter_percent) {
    bool res = false;
    if(counter_percent <= 100) {
        uint32_t counter = 0;
        (void)counter;
        uint32_t period = timer_period_get(num); /*returns 0 */
        (void)period;
        if(period) {
            counter = period * counter_percent / 100;
            res = timer_counter_set(num, counter);
        }
    }
    return res;
}

bool timer_init_one(uint8_t num) {
    bool res = false;
    const TimerConfig_t* Config = TimerGetConfig(num);
    if(Config) {
        LOG_WARNING(TIMER, "Init:%u", num);
#ifdef HAS_TIMER_DIAG
        LOG_WARNING(TIMER, "Config:%s", TimerConfigToStr(Config));
#endif
        TimerHandle_t* Node = TimerGetNode(num);
        if(Node) {
            TimerInfo_t* Info = TimerGetInfo(num);
            if(Info) {
                LOG_WARNING(TIMER, "SpotInfo:%u", num);
                Node->TMRx = Info->TMRx;
                /* enable tmr clock */
                crm_periph_clock_enable(Info->clock_type, TRUE);

                uint32_t period = 0;
                uint32_t bus_clock_hz = timer_bus_clock_get(num);
                LOG_INFO(TIMER, "TIMER%u TimerBusClck:%u Hz", num, bus_clock_hz);

                uint32_t prescaler = timer_calc_prescaler(bus_clock_hz, Config->cnt_period_ns, PRESCALER_MAX);
                LOG_INFO(TIMER, "TIMER%u prescaler:%u", num, prescaler);

                uint32_t max_val = (uint32_t)(ipow(2, (uint32_t)Info->resolution_bit) - 2);
                LOG_INFO(TIMER, "TIMER%u MaxVal:%u,Resol:%u bit", num, max_val, Info->resolution_bit);

                res = timer_calc_registers(Config->period_ms, Config->period_us, Config->period_ns, bus_clock_hz,
                                           prescaler, &period, max_val);
                if(res) {
                    LOG_DEBUG(TIMER, "TIMER%u,PeriodOk", num);
                } else {
                    res = false;
                    LOG_ERROR(TIMER, "TIMER%u,PeriodErr", num);
                }
                LOG_INFO(TIMER, "TIMER%u prescaler:%u,period:%u", num, prescaler, period);
                tmr_base_init(Info->TMRx, period, prescaler);

                tmr_count_mode_type tmr_cnt_dir = TMR_COUNT_UP;
                tmr_cnt_dir_set(Info->TMRx, tmr_cnt_dir);

                tmr_clock_source_div_set(Info->TMRx, TMR_CLOCK_DIV1);

                if(Config->interrupt_on) {
                    LOG_INFO(TIMER, "TIMER%u DeployISRs", num);
                    /* overflow interrupt enable */
                    tmr_interrupt_enable(Info->TMRx, TMR_OVF_INT, TRUE);
                    tmr_interrupt_enable(Info->TMRx, TMR_C1_INT, TRUE);
                    tmr_interrupt_enable(Info->TMRx, TMR_C2_INT, TRUE);
                    tmr_interrupt_enable(Info->TMRx, TMR_C3_INT, TRUE);
                    tmr_interrupt_enable(Info->TMRx, TMR_C4_INT, TRUE);
                    tmr_interrupt_enable(Info->TMRx, TMR_HALL_INT, TRUE);
                    tmr_interrupt_enable(Info->TMRx, TMR_TRIGGER_INT, TRUE);
                    tmr_interrupt_enable(Info->TMRx, TMR_BRK_INT, TRUE);

                    /* tmr1 hall interrupt nvic init */
                    LOG_INFO(TIMER, "TIMER%u IRQn:%u", num, Info->irq_n);
                    nvic_irq_enable(Info->irq_n, 10, 10);
                }

                /* enable tmr1 */
                //  tmr_counter_enable(Info->TMRx, TRUE);
                res = timer_ctrl(num, Config->on_off);
            } else {
                res = false;
                LOG_ERROR(TIMER, "TIMER%u NoInfo", num);
            }
        } else {
            res = false;
            LOG_ERROR(TIMER, "TIMER%u NoNode", num);
        }
    } else {
        res = false;
        LOG_DEBUG(TIMER, "TIMER%u NoConfig", num);
    }
    return res;
}

bool timer_wait_us(uint32_t pause_us) {
    bool res = false;
    uint32_t start_us = timer_get_us32(TIME_TIMER_NUM);
    uint32_t cur_us = 0;
    uint32_t diff_us = 0;
    while(1) {
        cur_us = timer_get_us32(TIME_TIMER_NUM);
        diff_us = cur_us - start_us;
        if(pause_us < diff_us) {
            res = true;
            break;
        }
    }
    return res;
}

#if 0
static bool timer_compare_get(uint8_t num, TimerOutChannel_t channel, uint32_t* out_compare) {
    bool res = false;
    return res;
}
static bool timer_set_compare(uint8_t num, TimerOutChannel_t channel, uint32_t compare) {
    bool res = false;
    LOG_DEBUG(TIMER, "SetCompare T:%u C:%u Compare:%u", num, channel, compare);
    return res;
}
#endif
static uint32_t TimerChannelToInterruptFlag(TimerCapComChannel_t channel) {
    uint32_t tmr_interrupt = 0;
    switch((uint32_t)channel) {
    case TIMER_CC_CHAN_1: {
        tmr_interrupt = TMR_C1_INT;
    } break;
    case TIMER_CC_CHAN_2: {
        tmr_interrupt = TMR_C2_INT;
    } break;
    case TIMER_CC_CHAN_3: {
        tmr_interrupt = TMR_C3_INT;
    } break;
    case TIMER_CC_CHAN_4: {
        tmr_interrupt = TMR_C4_INT;
    } break;
    default: {
        LOG_ERROR(TIMER, "Error");
    } break;
    }
    return tmr_interrupt;
}

bool timer_channel_ctrl(uint8_t num, TimerCapComChannel_t channel, bool on_off) {
    bool res = false;
    LOG_DEBUG(TIMER, "TIMER%u,CH%u,%s", num, channel, OnOffToStr(on_off));
    TimerInfo_t* Info = TimerGetInfo(num);
    if(Info) {
        TimerHandle_t* Node = TimerGetNode(num);
        if(Node) {
            confirm_state new_state = OnOffToConfirmState(on_off);
            tmr_channel_select_type tmr_channel = TimerChannelToArteryTimerChannel(channel);

            uint32_t tmr_interrupt = TimerChannelToInterruptFlag(channel);
            tmr_interrupt_enable(Info->TMRx, tmr_interrupt, new_state);

            tmr_channel_enable(Info->TMRx, tmr_channel, new_state);
            res = true;
        }
    } else {
        res = false;
        LOG_DEBUG(TIMER, "TIMER%u,NoInfo", num);
    }
    return res;
}

uint32_t timer_counter_get(uint8_t num) {
    uint32_t counter_value = 0;
    TimerInfo_t* Info = TimerGetInfo(num);
    if(Info) {
        if(Info->TMRx) {
            counter_value = tmr_counter_value_get(Info->TMRx);
        }
    }
    return counter_value;
}
