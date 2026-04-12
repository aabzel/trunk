#include "pwm_config.h"

#ifndef HAS_PWM
#error "Add HAS_PWM"
#endif /*HAS_PWM*/

#include "data_utils.h"
#include "gpio_mcal.h"
#ifdef HAS_I2S_FULL_DUPLEX
#include "i2s_full_duplex.h"
#endif

#define PWM_CONFIG_ONE(NUM_X, TIMER_NUM_X, TIMER_CHANNEL_X, FREQ_HZ, DUTY_P, NAME, ON_X, COMP_ISR, DONE_ISR)           \
    {                                                                                                                  \
        .num = NUM_X,                                                                                                  \
        .timer_num = TIMER_NUM_X,                                                                                      \
        .channel = TIMER_CHANNEL_X,                                                                                    \
        .channel_on = true,                                                                                            \
        .frequency_hz = FREQ_HZ,                                                                                       \
        .duty = DUTY_P,                                                                                                \
        .phase_us = 0,                                                                                                 \
        .name = #NAME,                                                                                                 \
        .valid = true,                                                                                                 \
        .ComparatorHandler = COMP_ISR,                                                                                 \
        .PulseDoneHandler = DONE_ISR,                                                                                  \
        .on = ON_X,                                                                                                    \
    },

static bool PwmI2s2ComparatorIsr(void) {
    bool res = false;
#ifdef HAS_I2S_FULL_DUPLEX_DEBUG
    Pad_t DebugPad = {.port=PORT_B, .pin=8,};
    res = gpio_logic_level_set(DebugPad.byte, GPIO_LVL_HI);
#endif

#ifdef HAS_I2S_FULL_DUPLEX
    I2sFullDuplexHandle_t* Node = I2sFullDuplexGetNode(1);
    if(Node) {
        res = i2s_full_duplex_data_proc_ll(Node, 2);
    }
#endif
    return res;
}

static bool PwmI2s2PulseDoneIsr(void) {
    bool res = false;
#ifdef HAS_I2S_FULL_DUPLEX_DEBUG
    Pad_t DebugPad = {.port=PORT_B, .pin=8,};
    res = gpio_logic_level_set(DebugPad.byte, GPIO_LVL_LOW);
#endif

#ifdef HAS_I2S_FULL_DUPLEX
    I2sFullDuplexHandle_t* Node = I2sFullDuplexGetNode(1);
    if(Node){
        res = i2s_full_duplex_data_proc_ll(Node,   0);
    }
#endif

    return res;
}


#ifdef HAS_TIMER9
#define PWM_CONFIG_TIMER9   \
    PWM_CONFIG_ONE(PWM_NUM_ENS, 9, 1, 500.0, 50.0, PWM1, false, NULL, NULL)
#else
#define PWM_CONFIG_TIMER9
#endif

#ifdef HAS_TIMER20
#define PWM_CONFIG_TIMER20     \
    PWM_CONFIG_ONE(PWM_NUM_TEST, 20, 2, 20000.0, 44.0, TEST, true, NULL, NULL)                                         \
    PWM_CONFIG_ONE(PWM_NUM_EXT1, 20, 4, 20000.0, 11.0, PWM_ADC2, true, NULL, NULL)                                     \
    PWM_CONFIG_ONE(PWM_NUM_EXT2, 20, 1, 20000.0, 33.0, DIGIT_EXT1, true, NULL, NULL)                                   \
    PWM_CONFIG_ONE(PWM_NUM_ADC2, 20, 3, 20000.0, 22.0, PWM_ADC1, true, NULL, NULL)
#else
#define PWM_CONFIG_TIMER20
#endif

#define PWM_CONFIG_ALL   \
    PWM_CONFIG_TIMER9    \
    PWM_CONFIG_TIMER20   \
    PWM_CONFIG_ONE(PWM_NUM_MCLK, 1, 1, 12288000.0, 50.0, MCLK, true, NULL, NULL)

const PwmConfig_t PwmConfig[] = {
    PWM_CONFIG_ALL

        {
            .num = PWM_NUM_I2S2,
            .timer_num = 8,
            .channel = 1,
            .frequency_hz = 46.875, /*46.875,  11.71875  46.875 Hz is T=21.333 ms */
            .DebugPad = { .port = PORT_B, .pin = 8,},
            .duty = 50.0,
            .phase_us = 0,
            .name = "I2S2",
            .valid = true,
            .ComparatorHandler = PwmI2s2ComparatorIsr,
            .PulseDoneHandler = PwmI2s2PulseDoneIsr,
            .on = true,
            .channel_on = true,
        },
};

PwmHandle_t PwmInstance[] = {
#ifdef HAS_TIMER9
    {
        .num = PWM_NUM_ENS,
        .valid = true,
    },
#endif
    {
        .num = PWM_NUM_MCLK,
        .valid = true,
    },
#ifdef HAS_TIMER20
    {
        .num = PWM_NUM_TEST,
        .valid = true,
    },
    {
        .num = PWM_NUM_ADC2,
        .valid = true,
    },
    {
        .num = PWM_NUM_EXT1,
        .valid = true,
    },
    {
        .num = PWM_NUM_EXT2,
        .valid = true,
    },
#endif
    {
        .num = PWM_NUM_I2S2,
        .valid = true,
    },
};

uint32_t pwm_get_cnt(void) {
    uint32_t cnt = 0;
    uint32_t cnt1 = 0;
    uint32_t cnt2 = 0;
    cnt1 = ARRAY_SIZE(PwmInstance);
    cnt2 = ARRAY_SIZE(PwmConfig);
    if(cnt1 == cnt2) {
        cnt = cnt1;
    }
    return cnt;
}
