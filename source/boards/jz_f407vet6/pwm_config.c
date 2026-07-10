#include "pwm_config.h"

#include "data_utils.h"
#include "gpio_mcal.h"

#ifndef HAS_PWM
#error "Add HAS_PWM"
#endif

#ifdef HAS_DRV8870
#define PWM_CONFIG_IN1                                     \
     {  .num = PWM_NUM_DRV8870_CH1_IN1,                    \
        .PhaseComparator={.timer = 0, .channel = 0, },     \
        .TimChan={.timer = 5, .channel = 1},               \
        .Pad={.port = PORT_A, .pin=0, },                   \
        .pin_mux = 2,                                      \
        .polarity = PWM_POLARITY_HIGH,                     \
        .frequency_hz = 400.0f,                            \
        .ComparatorHandler = NULL,                         \
        .PeriodDoneHandler = NULL,                         \
        .duty = 00.0f,                                     \
        .phase_s = 0.0f,                                   \
        .name="DRV8870_IN1",                               \
        .valid = true,                                     \
        .on = true,                                        \
     },

#define PWM_CONFIG_IN2                                    \
     {  .num = PWM_NUM_DRV8870_CH1_IN2,                   \
        .polarity = PWM_POLARITY_HIGH,                    \
        .Pad={.port = PORT_A, .pin=3, },                  \
        .TimChan={.timer = 9, .channel = 2,},             \
        .pin_mux = 3,                                     \
        .PhaseComparator = {.timer = 0, .channel = 0, },  \
        .frequency_hz = 400.0f,                           \
        .ComparatorHandler = NULL,                        \
        .PeriodDoneHandler = NULL,                        \
        .duty = 0.0f,                                     \
        .phase_s = 0.0f,                                  \
        .name="DRV8870_IN2",                              \
        .valid = true,                                    \
        .on = true,                                       \
     },

#define PWM_CONFIG_DRV8870     \
          PWM_CONFIG_IN1       \
          PWM_CONFIG_IN2
#else
#define PWM_CONFIG_DRV8870
#endif


#ifdef HAS_HOMING_LASER
#define PWM_CONFIG_HOMING_LASER                         \
     {  .num = PWM_NUM_HOMING_LASER,                        \
        .polarity = PWM_POLARITY_HIGH,                  \
        .TimChan={.timer = 3, .channel = 1},            \
        .PhaseComparator={.timer = 1, .channel = 1, },  \
        .pin_mux = 2,                                   \
        .Pad={.port = PORT_A, .pin=6, },                \
        .frequency_hz = 1000.0f,                        \
        .ComparatorHandler=NULL,                        \
        .PeriodDoneHandler=NULL,                        \
        .duty = 50.0f,                                  \
        .phase_s = 0.0f,                                \
        .name="TxLaserCarrier",                         \
        .valid = true,                                  \
        .on = true,                                     \
     },
#else
#define PWM_CONFIG_HOMING_LASER
#endif

const PwmConfig_t PwmConfig[] = {
        PWM_CONFIG_HOMING_LASER
        PWM_CONFIG_DRV8870

        /*carrier*/

#if 0
#ifdef HAS_TIMER8
     //    PC7 TIM8_CH2
     {  .num = 2,
        .polarity = PWM_POLARITY_HIGH,
        .pin_mux = 3,
        .TimChan={.timer = 8, .channel = 2,},
        .PhaseComparator={.timer=0, .channel=0, },
        .Pad={.port = PORT_C, .pin=7, },
        .frequency_hz = 1000.0f,
        .ComparatorHandler = NULL,
        .PeriodDoneHandler = NULL,
        .duty = 50.0f,
        .phase_s = 0.0f,
        .name="Base",
        .valid = true,
        .on = true,
     },
#endif

     /* lo PB7 TIM4_CH2 AF2   */
     {  .num = 3,
        .polarity = PWM_POLARITY_HIGH,
        .pin_mux = 2,
        .TimChan = { .timer = 4, .channel = 2 },
        .PhaseComparator = { .timer = 8, .channel = 1, },
        .Pad = { .port = PORT_B, .pin = 7, },
        .frequency_hz = 1000.0f,
        .ComparatorHandler = NULL,
        .PeriodDoneHandler = NULL,
        .duty = 50.0f,
        .phase_s = 0.0f,
        .name = "Lo",
        .valid = true,
        .on = true,
     },



     {  .num = 3,
             .timer_num = 9,
             .timer_channel = 1,
             .Polarity = PWM_POLARITY_HIGH,
             .pin_mux = 2,
             .Pad={.port = PORT_E, .pin=5, },
             .frequency_hz = 10.0,
             .ComparatorHandler=NULL,
             .PeriodDoneHandler=NULL,
             .duty = 50, .phase_s = 0.0f,  .name="Laser3", .valid = true, .on = true,},
#endif
};

PwmHandle_t PwmInstance[] = {
#ifdef HAS_DRV8870
    {.num = PWM_NUM_DRV8870_CH1_IN1,  .valid = true,},
    {.num = PWM_NUM_DRV8870_CH1_IN2,  .valid = true,},
#endif

#ifdef HAS_HOMING_LASER
    {.num = PWM_NUM_HOMING_LASER,  .valid = true,},
#endif
};

COMPONENT_GET_CNT(Pwm, pwm)


