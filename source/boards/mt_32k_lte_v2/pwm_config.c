#include "pwm_config.h"

#include "data_utils.h"
#include "gpio_mcal.h"

#ifndef HAS_PWM
#error "Add HAS_PWM"
#endif


const PwmConfig_t PwmConfig[] = {
        /*carrier*/
     {  .num = 1,
        .polarity = PWM_POLARITY_HIGH,
        .TimChan={.timer = 3, .channel = 1},
        .PhaseComparator={.timer = 1, .channel = 1, },
        .pin_mux = 2,
        .Pad={.port = PORT_A, .pin=6, },
        .frequency_hz = 1000.0f,
        .ComparatorHandler=NULL,
        .PeriodDoneHandler=NULL,
        .duty = 50.0f,
        .phase_s = 0.0f,
        .name="TxLaserCarrier",
        .valid = true,
        .on = true,
     },
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



#if 0
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
    {.num = 1,  .valid = true,},
#ifdef HAS_TIMER8
    {.num = 2,  .valid = true,},
#endif
    {.num = 3,  .valid = true,},
    //{.num = 3,  .valid = true,},
};

COMPONENT_GET_CNT(Pwm, pwm)


