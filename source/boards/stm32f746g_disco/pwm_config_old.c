#include "pwm_config.h"

#include "data_utils.h"
#include "gpio_mcal.h"

#ifdef HAS_LED_MONO_PWM
#include "led_mono_pwm_mcal.h"
#endif

static const Pad_t PadStatusLed = {.port = PORT_C, .pin=10,};

static bool StatusLedComparatorHandler(void) {
    bool res = false ;
    res= gpio_logic_level_set(PadStatusLed, GPIO_LVL_HI);
    return res;
}

static bool StatusLedPulseDoneHandler(void) {
    bool res = false ;
    res = gpio_logic_level_set(PadStatusLed, GPIO_LVL_LOW);
    return res;
}

const PwmConfig_t PwmConfig[] = {
     {  .num = PWM_NUM_TX1_LED,  .duty = 50.0, .on = true, .timer_num = 2, .timer_channel = 3, .Pad={.port = PORT_A, .pin = 2, }, .frequency_hz = 400.0, .ComparatorHandler=NULL,  .PulseDoneHandler=NULL,   .phase_us = 0,  .name="TX1_LED", .valid = true, },
     {  .num = PWM_NUM_RX1_LED,  .duty = 50.0, .on = true, .timer_num = 2, .timer_channel = 4, .Pad={.port = PORT_A, .pin = 3, }, .frequency_hz = 400.0, .ComparatorHandler=NULL,  .PulseDoneHandler=NULL,   .phase_us = 0,  .name="RX1_LED", .valid = true,  },
     {  .num = PWM_NUM_RX2_LED,  .duty = 50.0, .on = true, .timer_num = 8, .timer_channel = 2, .Pad={.port = PORT_C, .pin = 7, }, .frequency_hz = 400.0, .ComparatorHandler=NULL,  .PulseDoneHandler=NULL,   .phase_us = 0,  .name="RX2_LED", .valid = true,  },
     {  .num = PWM_NUM_TX2_LED,  .duty = 50.0, .on = true, .timer_num = 8, .timer_channel = 1, .Pad={.port = PORT_C, .pin = 6, }, .frequency_hz = 400.0, .ComparatorHandler=NULL,  .PulseDoneHandler=NULL,   .phase_us = 0,  .name="TX2_LED", .valid = true,  },
     {  .num = PWM_NUM_STATUS_LED,  .duty = 50.0, .on = true,  .timer_num = 4, .timer_channel = 1, .Pad={.port = PORT_C, .pin=10, }, .frequency_hz = 300.0, .ComparatorHandler=StatusLedComparatorHandler,  .PulseDoneHandler=StatusLedPulseDoneHandler,   .phase_us = 0,  .name="STATUS_LED", .valid = true,  },
};

PwmHandle_t PwmInstance[] = {
    {.num = PWM_NUM_RX1_LED,  .valid = true,},
    {.num = PWM_NUM_TX1_LED,  .valid = true,},
    {.num = PWM_NUM_RX2_LED,  .valid = true,},
    {.num = PWM_NUM_TX2_LED,  .valid = true,},
    {.num = PWM_NUM_STATUS_LED,  .valid = true,},
};

uint32_t pwm_get_cnt(void) {
    uint32_t cnt = 0;
    uint32_t cnt1 = 0;
    uint32_t cnt2 = 0;
    cnt1 = ARRAY_SIZE(PwmInstance);
    cnt2 = ARRAY_SIZE(PwmConfig); 
    if(cnt1==cnt2){
        cnt = cnt1;
    }
    return cnt;
} 
