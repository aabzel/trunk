#ifndef SENSITIVITY_TASKS_H
#define SENSITIVITY_TASKS_H

#ifdef __cplusplus
extern "C" {
#endif

#ifdef HAS_ADC_IF_PROC
#include "adc_if_mcal.h"
#define ADC_IF_TASK {.name="ADC_IF", .period_us=ADC_IF_POLL_PERIOD_US, .limiter.function=adc_if_proc,},
#else
#define ADC_IF_TASK
#endif

#ifdef HAS_DCF77_PROC
#include "dcf77_mcal.h"
#define DCF77_TASK {.name="DCF77", .period_us=DCF77_PERIOD_US, .limiter.function=dcf77_proc,},
#else
#define DCF77_TASK
#endif

#ifdef HAS_JUMPER_CODE_PROC
#include "jumper_code_mcal.h"
#define JUMPER_CODE_TASK {                                         \
                          .name = "JumperCode",                    \
                          .period_us = JUMPER_CODE_PERIOD_US,      \
                          .limiter.function = jumper_code_proc,    \
                         },
#else
#define JUMPER_CODE_TASK
#endif

#ifdef HAS_BUTTON_PROC
#include "button_mcal.h"
#define BUTTON_TASK { .name="BUTTON", .period_us=BUTTON_POLL_PERIOD_US, .limiter.function=button_proc,},
#else
#define BUTTON_TASK
#endif

#ifdef HAS_CROSS_DETECT_PROC
#include "cross_detect_mcal.h"
#define CROSS_DETECT_TASK {.name="CROSS_DETECT", .period_us=CROSS_DETECT_POLL_PERIOD_US, .limiter.function=cross_detect_proc,},
#else
#define CROSS_DETECT_TASK
#endif

#ifdef HAS_DISTANCE_PROC
#include "distance_mcal.h"
#define DISTANCE_TASK {.name="DISTANCE", .period_us=DISTANCE_POLL_PERIOD_US, .limiter.function=distance_proc,},
#else
#define DISTANCE_TASK
#endif

#ifdef HAS_GAME_PAD_PS2_PROC
#include "game_pad_ps2.h"
#define GAME_PAD_PS2_TASK {.name="GamePadPs2", .period_us=GAME_PAD_PS2_POLL_PERIOD_US, .limiter.function=game_pad_ps2_proc,},
#else
#define GAME_PAD_PS2_TASK
#endif

#ifdef HAS_HEALTH_MONITOR_PROC
#include "health_monitor.h"
#define HEALTH_MONITOR_TASK {.name="HEAL_MON", .period_us=HEAL_MON_PERIOD_US, .limiter.function=health_monotor_proc,},
#else
#define HEALTH_MONITOR_TASK
#endif

#ifdef HAS_INCREMENTAL_ENCODER_PROC
#include "incremental_encoder_mcal.h"
#define INCREMENTAL_ENCODER_TASK                              \
        {                                                     \
          .num = TASK_INCREMENTAL_ENCODER,                    \
          .name = "IncEncoder",                               \
          .period_us = INCREMENTAL_ENCODER_POLL_PERIOD_US,    \
         .limiter.function = incremental_encoder_proc,        \
        },                                                    \
        {                                                     \
          .num = TASK_INCREMENTAL_ENCODER_SHOW,               \
          .name = "IncEncoderShow",                           \
          .period_us = INCREMENTAL_ENCODER_POLL_PERIOD_US,    \
         .limiter.function = incremental_encoder_show_proc,   \
        },
#else
#define INCREMENTAL_ENCODER_TASK
#endif

#ifdef HAS_GNSS_PROC
#define GNSS_TASK
#else
#define GNSS_TASK
#endif

#ifdef HAS_LOAD_DETECT_PROC
#include "load_detect_mcal.h"
#define LOAD_DETECT_TASK {.name="LOAD_DETECT", .period_us=LOAD_DETECT_PERIOD_US, .limiter.function=load_detect_proc,},
#else
#define LOAD_DETECT_TASK
#endif

#ifdef HAS_TIME_PROC
#include "time_mcal.h"
#define TIME_TASK {.name="TIME", .period_us=TIME_POLL_PERIOD_US, .limiter.function=time_proc,},
#else
#define TIME_TASK
#endif

#ifdef HAS_PDM_PROC
#include "pdm_mcal.h"
#define PDM_TASK {.name="PDM", .period_us=PDM_POLL_PERIOD_US, .limiter.function=pdm_proc,},
#else
#define PDM_TASK
#endif

#ifdef HAS_PHOTORESISTOR_PROC
#include "photoresistor.h"
#define PHOTORESISTOR_TASK {.name="PHOTORESISTOR", .period_us=PHOTORESISTOR_POLL_PERIOD_US, .limiter.function=photoresistor_proc,},
#else
#define PHOTORESISTOR_TASK
#endif

#ifdef HAS_SOFTWARE_TIMER_PROC
#include "software_timer.h"
#define SOFTWARE_TIMER_TASK    {                          \
                      .name = "SwTimer",                  \
                      .period_us = SW_TIMER_PERIOD_US,    \
                      .limiter.function = sw_timer_poll,  \
                  },
#else
#define SOFTWARE_TIMER_TASK
#endif

#ifdef HAS_IR_RECEIVER_PROC
#include "ir_receiver_mcal.h"
#define IR_RECEIVER_TASK {.name="IR_RECEIVER", .period_us=IR_RECEIVER_PERIOD_US, .limiter.function=ir_receiver_proc,},
#else
#define IR_RECEIVER_TASK
#endif

#ifdef HAS_UNIT_TEST_PROC
#include "unit_test.h"
#define UNIT_TEST_TASK {                                         \
                        .name = "uTest",                         \
                        .period_us = UNIT_TEST_PERIOD_US,        \
                        .limiter.function = unit_test_proc,      \
                       },
#else
#define UNIT_TEST_TASK
#endif


#define SENSITIVITY_TASKS     \
    ADC_IF_TASK               \
    BUTTON_TASK               \
    HEALTH_MONITOR_TASK       \
    CROSS_DETECT_TASK         \
    IR_RECEIVER_TASK          \
    DCF77_TASK                \
    JUMPER_CODE_TASK          \
    DISTANCE_TASK             \
    INCREMENTAL_ENCODER_TASK  \
    GAME_PAD_PS2_TASK         \
    GNSS_TASK                 \
    LOAD_DETECT_TASK          \
    PDM_TASK                  \
    PHOTORESISTOR_TASK        \
    SOFTWARE_TIMER_TASK       \
    UNIT_TEST_TASK            \
    TIME_TASK

#ifdef __cplusplus
}
#endif


#endif /* SENSITIVITY_TASKS_H */
