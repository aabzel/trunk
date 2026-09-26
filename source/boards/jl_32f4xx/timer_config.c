#include "timer_config.h"


#include "data_utils.h"
#include "time_mcal.h"
#include "physics_utils.h"

#ifndef HAS_TIMER
#error "Add HAS_TIMER"
#endif



#ifdef HAS_TIMER1
#define TIMER1_CONFIG                                                       \
          {                                                                 \
              .interrupt_on = false,                                        \
              .role = TIMER_ROLE_MASTER,                                    \
              .dir = TIMER_CNT_DIR_UP,                                      \
              .valid = true,                                                \
              .on_off = true,                                               \
              .num = 1 ,                                                    \
              .name = "SW_UART_TX_DMA_TG",                                  \
              .period_s = FREQ_HZ_TO_PERIOD_S(9600),                        \
              .cnt_period_ns = 25,                                          \
              .master_out_trigger = TIMER_MASTER_OUT_TRG_UPDATE,            \
              .PeriodDoneHandler = NULL,                                    \
              .ComparatorHandler = NULL,                                    \
              .slave_mode = TIMER_SLAVE_MODE_UNDEF,                         \
              .slave_trigger_prescaler = 0,                                 \
              .slave_trigger_filter = 0,                                    \
              .slave_input_trigger = TIMER_SLAVE_IN_TRIG_UNDEF,             \
              .slave_trigger_polarity = TIMER_SLAVE_TRIGGER_POLARITY_UNDEF, \
              },
#else
#define TIMER1_CONFIG
#endif

#ifdef HAS_TIMER8
#define TIMER8_CONFIG                                                       \
          {                                                                 \
              .interrupt_on = false,                                        \
              .role = TIMER_ROLE_MASTER,                                    \
              .dir = TIMER_CNT_DIR_UP,                                      \
              .valid = true,                                                \
              .on_off = true,                                               \
              .num = 8 ,                                                    \
              .name = "UART_RX_DMA_TG",                                     \
              .period_s = FREQ_HZ_TO_PERIOD_S(8*9600),                      \
              .cnt_period_ns = 25,                                          \
              .master_out_trigger = TIMER_MASTER_OUT_TRG_UPDATE,            \
              .PeriodDoneHandler = NULL,                                    \
              .ComparatorHandler = NULL,                                    \
              .slave_mode = TIMER_SLAVE_MODE_UNDEF,                         \
              .slave_trigger_prescaler = 0,                                 \
              .slave_trigger_filter = 0,                                    \
              .slave_input_trigger = TIMER_SLAVE_IN_TRIG_UNDEF,             \
              .slave_trigger_polarity = TIMER_SLAVE_TRIGGER_POLARITY_UNDEF, \
              },
#else
#define TIMER8_CONFIG
#endif

const TimerConfig_t TimerConfig[] = {
        TIMER1_CONFIG
        TIMER8_CONFIG

#ifdef HAS_TIMER2
    {.num = 2 , .on_off = true, .role=TIMER_ROLE_MASTER, .dir = TIMER_CNT_DIR_UP, .valid=true, .interrupt_on = false, .cnt_period_ns = 3000, .period_s = MSEC_2_SEC(160), .name="IrFrame",  },
#endif

#ifdef HAS_TIMER3
    {.num = 3,  .on_off = true,  .role=TIMER_ROLE_MASTER, .dir = TIMER_CNT_DIR_UP, .valid=true, .interrupt_on = false, .cnt_period_ns = 50, .period_s = FREQ_HZ_TO_PERIOD_S(21000) , .name="DRV8870_2",  },
#endif

#ifdef HAS_TIMER4
    {.num = 4 , .on_off = true,  .role=TIMER_ROLE_MASTER,.dir=TIMER_CNT_DIR_UP, .valid=true, .interrupt_on = false, .cnt_period_ns = 100, .period_s = MSEC_2_SEC(1000), .name="Beep",  },
#endif

#ifdef HAS_TIMER5
    {.num = 5 , .on_off = true, .role=TIMER_ROLE_MASTER, .dir=TIMER_CNT_DIR_UP, .valid=true, .interrupt_on = false, .cnt_period_ns = 20000, .period_s = MSEC_2_SEC(1), .name="1ms",  },
#endif

#ifdef HAS_TIMER6
    {.num = 6 , .on_off = true, .role=TIMER_ROLE_MASTER, .dir=TIMER_CNT_DIR_UP, .valid=true, .interrupt_on = false, .cnt_period_ns = 3000, .period_s = MSEC_2_SEC(160), .name="spare", },
#endif

#ifdef HAS_TIMER10
    {.num = 10 , .on_off = true, .role=TIMER_ROLE_MASTER, .dir=TIMER_CNT_DIR_UP, .valid=true, .interrupt_on = false, .cnt_period_ns = 500, .period_s = FREQ_HZ_TO_PERIOD_S(5000), .name="LED",  },
#endif

#ifdef HAS_TIMER11
    {.num = 11 , .on_off = true, .role=TIMER_ROLE_MASTER, .dir=TIMER_CNT_DIR_UP, .valid=true, .interrupt_on = false, .cnt_period_ns = 500, .period_s = FREQ_HZ_TO_PERIOD_S(5000), .name="spare",  },
#endif

#ifdef HAS_TIMER14
    {.num = 14 , .on_off = true, .role=TIMER_ROLE_MASTER, .dir=TIMER_CNT_DIR_UP, .valid=true, .interrupt_on = false, .cnt_period_ns = 500, .period_s = FREQ_HZ_TO_PERIOD_S(5000), .name="spare",  },
#endif
};

TimerHandle_t TimerInstance[] = {
#ifdef HAS_TIMER1
    {.num = 1, .valid = true,},
#endif

#ifdef HAS_TIMER2
    {.num = 2, .valid = true,},
#endif

#ifdef HAS_TIMER3
    {.num = 3, .valid = true,},
#endif

#ifdef HAS_TIMER4
    {.num = 4, .valid = true,},
#endif

#ifdef HAS_TIMER5
    {.num = 5, .valid = true,},
#endif

#ifdef HAS_TIMER6
    {.num = 6, .valid = true,},
#endif

#ifdef HAS_TIMER8
    {.num = 8, .valid = true,},
#endif

#ifdef HAS_TIMER10
    {.num = 10, .valid = true,},
#endif

#ifdef HAS_TIMER11
    {.num = 11, .valid = true,},
#endif

#ifdef HAS_TIMER14
    {.num = 14, .valid = true,},
#endif
};

COMPONENT_GET_CNT(Timer, timer)
