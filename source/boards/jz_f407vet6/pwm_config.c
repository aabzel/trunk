#include "pwm_config.h"

#include "data_utils.h"
#include "led_mono_pwm_mcal.h"
#include "gpio_mcal.h"

#ifndef HAS_PWM
#error "Add HAS_PWM"
#endif

static  bool PwmIsrHandler(void) {
    bool res = false ;
    return res;
}

static  bool PwmLedOn(void) {
    bool res = false ;
    Pad_t Pad={.port = PORT_C, .pin=13, };
    res = led_mono_pwm_ctrl( Pad, true);
    return res;
}

static  bool PwmLedOff(void) {
    bool res = false ;
    Pad_t Pad={.port = PORT_C, .pin=13, };
    res = led_mono_pwm_ctrl( Pad, false);
    return res;
}

static bool PwmTro1_OnIsrHandler(void) {
    bool res = false;
#ifdef HAS_PWM_GPIO
    Pad_t Pad = { .port = PORT_E, .pin = 13, };
    res = gpio_logic_level_set(Pad, GPIO_LVL_HI);
#endif
    return res;
}

static bool PwmTro1_OffIsrHandler(void) {
    bool res = false;
#ifdef HAS_PWM_GPIO
    Pad_t Pad = { .port = PORT_E, .pin = 13, };
    res = gpio_logic_level_set(Pad, GPIO_LVL_LOW);
#endif
    return res;
}

static bool PwmTro2_OnIsrHandler(void) {
    bool res = false;
#ifdef HAS_PWM_GPIO
    Pad_t Pad = { .port = PORT_E, .pin = 14, };
    res = gpio_logic_level_set(Pad, GPIO_LVL_HI);
#endif
    return res;
}
static bool PwmTro2_OffIsrHandler(void) {
    bool res = false;
#ifdef HAS_PWM_GPIO
    Pad_t Pad = { .port = PORT_E, .pin = 14, };
    res = gpio_logic_level_set(Pad, GPIO_LVL_LOW);
#endif
    return res;
}

static bool PwmSreerOn1IsrHandler(void){return true;}
static bool PwmSreerOn2IsrHandler(void){return true;}
static bool PwmSreer1OffIsrHandler(void){return true;}
static bool PwmSreer2OffIsrHandler(void){return true;}

const PwmConfig_t PwmConfig[] = {
     {  .num = 1, .timer_num = 0, .channel = 1, .Pad={.port = PORT_F, .pin=15, }, .frequency_hz = 100,   .ComparatorHandler=PwmIsrHandler,  .PulseDoneHandler=PwmIsrHandler,  .duty = 10, .phase_us = 0,  .name="",      .valid = true, .on = true,},
#ifdef HAS_TIMER1
     {  .num = 2, .timer_num = 1, .channel = 3, .Pad={.port = PORT_E, .pin=13, }, .frequency_hz = 400.0, .ComparatorHandler=PwmTro1_OnIsrHandler,  .PulseDoneHandler=PwmTro1_OffIsrHandler,  .duty = 50, .phase_us = 0,  .name="IN1_T", .valid = true, .on = true,},
     {  .num = 3, .timer_num = 1, .channel = 4, .Pad={.port = PORT_E, .pin=14, }, .frequency_hz = 400.0, .ComparatorHandler=PwmTro2_OnIsrHandler,  .PulseDoneHandler=PwmTro2_OffIsrHandler,  .duty = 50, .phase_us = 0,  .name="IN2_T", .valid = true, .on = true,},
#endif

#ifdef HAS_TIMER3
     {  .num = 4, .timer_num = 3, .channel = 1, .Pad={.port = PORT_A, .pin=6, }, .frequency_hz = 400, .ComparatorHandler=PwmSreerOn1IsrHandler,  .PulseDoneHandler=PwmSreer1OffIsrHandler,  .duty = 50, .phase_us = 0,  .name="IN1_S", .valid = true, .on = true,},
     {  .num = 5, .timer_num = 3, .channel = 2, .Pad={.port = PORT_A, .pin=7, }, .frequency_hz = 400, .ComparatorHandler=PwmSreerOn2IsrHandler,  .PulseDoneHandler=PwmSreer2OffIsrHandler,  .duty = 50, .phase_us = 0,  .name="IN2_S", .valid = true, .on = true,},
#endif
     {  .num = 6, .timer_num = 9, .channel = 1, .Pad={.port = PORT_C, .pin=13, }, .frequency_hz = 5000,  .ComparatorHandler=PwmLedOn,  .PulseDoneHandler=PwmLedOff,  .duty = 50, .phase_us = 0,  .name="LED",   .valid = true, .on = true,},
};

PwmHandle_t PwmInstance[] = {
    {.num = 1,  .valid = true,},
#ifdef HAS_TIMER1
    {.num = 2,  .valid = true,},
    {.num = 3,  .valid = true,},
#endif

#ifdef HAS_TIMER3
    {.num = 4,  .valid = true,},
    {.num = 5,  .valid = true,},
#endif
    {.num = 6,  .valid = true,},
};

COMPONENT_GET_CNT(Pwm, pwm)


