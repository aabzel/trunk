#include "pwm_config.h"

#include "data_utils.h"
#include "gpio_mcal.h"
#include "timer_mcal.h"

#ifdef HAS_LED_MONO_PWM
#include "led_mono_pwm_mcal.h"
#endif

#ifndef HAS_PWM
#error "Add HAS_PWM"
#endif

const PwmConfig_t SECTION_CFG_DATA PwmConfig[] = {
     {
         .num = PWM_NUM_OUT2_1,
         .Pad = {.port = PORT_C, .pin = 7, },
         .pin_mux = 2,
         .TimChPad = {.timer = 3, .channel = 3, },
         .PhaseComparator = {.timer = 2, .channel = 1, },
         .duty = 50.0,
         .on = false,
         .Polarity = PWM_POLARITY_HIGH,
         .frequency_hz = 1000.0,
         .ComparatorHandler = NULL,
         .PeriodDoneHandler = NULL,
         .phase_s = 0.0f,
         .name = "OUT2_1",
         .valid = true,
     },
     {
         .num = PWM_NUM_OUT2_2,
         .Pad = {.port = PORT_A, .pin = 8, },
         .pin_mux = 1,
         .PhaseComparator = {.timer = 5, .channel = 1, },
         .TimChPad = {.timer = 1, .channel = 1, },
         .duty = 50.0,
         .on = false,
         .Polarity = PWM_POLARITY_HIGH,
         .frequency_hz = 1000.0,
         .ComparatorHandler = NULL,
         .PeriodDoneHandler = NULL,
         .phase_s = 0.0f,
         .name = "OUT2_2",
         .valid = true,
     },
#ifndef HAS_UART1_HW_HOT_FIX
     {
         .num = PWM_NUM_OUT2_3,
         .Pad = {.port = PORT_A, .pin = 9, },
         .pin_mux = 1,  /* TIM1_CH2 */
         .PhaseComparator = {.timer = 5, .channel = 1, },
         .TimChPad = {.timer = 1, .channel = 2, },
         .duty = 50.0,
         .on = false,
         .Polarity = PWM_POLARITY_HIGH,
         .frequency_hz = 1000.0,
         .ComparatorHandler = NULL,
         .PeriodDoneHandler = NULL,
         .phase_s = 0.0f,
         .name = "OUT2_3",
         .valid = true,
     },
#endif

#ifndef HAS_UART1_HW_HOT_FIX
     {
         .num = PWM_NUM_OUT2_4,
         .name = "OUT2_4",
         .Pad = {.port = PORT_A, .pin = 10, },
         .pin_mux = 1, /* TIM1_CH3 */
         .PhaseComparator = {.timer = 5, .channel = 1, },
         .TimChPad = {.timer = 1, .channel = 3, },
         .duty = 50.0,
         .on = false,
         .Polarity = PWM_POLARITY_HIGH,
         .frequency_hz = 1000.0,
         .ComparatorHandler = NULL,
         .PeriodDoneHandler = NULL,
         .phase_s = 0.0f,
         .valid = true,
     },
#endif


     {
         .num = PWM_NUM_OUT3_1,
         .Pad = {.port = PORT_C, .pin = 6, },
         .pin_mux = 3,
         .PhaseComparator = {.timer = 5, .channel = 1, },
         .TimChPad = {.timer = 8, .channel = 1, },
         .duty = 50.0,
         .on = false,
         .Polarity = PWM_POLARITY_HIGH,
         .frequency_hz = 1000.0,
         .ComparatorHandler = NULL,
         .PeriodDoneHandler = NULL,
         .phase_s = 0.0f,
         .name = "OUT3_1",
         .valid = true,  },

     {  .num = PWM_NUM_OUT3_2,
        .Pad = {.port = PORT_D, .pin = 14, },
        .pin_mux = 2,
        .PhaseComparator = {.timer = 2, .channel = 2, },
        .TimChPad = {.timer = 4, .channel = 3, },
        .duty = 50.0,
        .on = false,
        .Polarity = PWM_POLARITY_HIGH,
        .frequency_hz = 1000.0,
        .ComparatorHandler = NULL,
        .PeriodDoneHandler = NULL,
        .phase_s = 0.0f,
        .name = "OUT3_2",
        .valid = true,  },

     {  .num = PWM_NUM_OUT3_3,
        .Pad = {.port = PORT_D, .pin=13, },
        .pin_mux = 2,
        .PhaseComparator = {.timer = 2, .channel = 2, },
        .TimChPad = {.timer = 4, .channel = 2, },
        .duty = 50.0,
        .on = false,
        .Polarity = PWM_POLARITY_HIGH,
        .frequency_hz = 1000.0,
        .ComparatorHandler = NULL,
        .PeriodDoneHandler = NULL,
        .phase_s = 0.0f,
        .name = "OUT3_3",
        .valid = true,  },
};

PwmHandle_t PwmInstance[] = {
    {.num = PWM_NUM_OUT2_1,  .valid = true,},
    {.num = PWM_NUM_OUT2_2,  .valid = true,},
#ifndef HAS_UART1_HW_HOT_FIX
    {.num = PWM_NUM_OUT2_3,  .valid = true,},
    {.num = PWM_NUM_OUT2_4,  .valid = true,},
#endif
    {.num = PWM_NUM_OUT3_1,  .valid = true,},
    {.num = PWM_NUM_OUT3_2,  .valid = true,},
    {.num = PWM_NUM_OUT3_3,  .valid = true,},

};

COMPONENT_GET_CNT(Pwm, pwm)
