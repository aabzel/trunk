#ifndef PWM_MCAL_TYPES_H
#define PWM_MCAL_TYPES_H

#include "std_includes.h"
#include "pwm_const.h"
#include "gpio_types.h"
#include "timer_types.h"

#ifdef HAS_PWM_CUSTOM
#include "pwm_custom_types.h"
#else
#define PWM_CUSTON_VARIABLES
#endif

#define PWM_SIGNAL_VARIABLES   \
    float duty;                \
    float frequency_hz;        \
    float phase_s;

typedef struct {
    PWM_SIGNAL_VARIABLES
    // float amplitude;
} PwmSignalBinary_t;

typedef bool (*PwmIsrHandler_t)(void);


#define PWM_COMMON_VARIABLES  \
    PWM_SIGNAL_VARIABLES      \
    Pad_t Pad;                \
    uint8_t channel_cnt;      \
    uint8_t num;                  \
    uint8_t pin_mux;              \
    char* name;                   \
    TimerChannel_t TimChan;       \
    float init_phase;  /*0Deg...360Deg*/ \
    PwmPolarity_t polarity; /*TimerChannel*/\
    TimerChannel_t PhaseComparator;       \
    PwmIsrHandler_t ComparatorHandler;     \
    PwmIsrHandler_t PeriodDoneHandler;     \
    bool valid;                           \
    bool on;

typedef struct {
    PWM_COMMON_VARIABLES
} PwmConfig_t;

typedef struct {
    uint32_t period; /*define frequency*/
    uint32_t pulse_diration; /*duty control*/
} PwmSignal_t;

typedef struct {
    PwmSignal_t Signal[2];
    uint32_t period_cnt;/* signal duration*/
    uint8_t cur_signal;
    uint32_t impulse_cnt;
} PwmModulation_t;

#define PWM_ISR_VARIABLES                           \
    volatile uint32_t int_cnt; /*Period counter*/   \
    volatile uint32_t pulse_fin_cnt;                \
    volatile uint32_t pulse_fin_half_cnt;           \
    volatile uint32_t period_elapse_cnt;

typedef struct {
    PWM_COMMON_VARIABLES
    PWM_CUSTON_VARIABLES
    PWM_ISR_VARIABLES
    uint32_t error_cnt;
    bool init_done;
    PwmMode_t mode;
    PwmModulation_t Modulation;
} PwmHandle_t;

#endif /* PWM_MCAL_TYPES_H */
