#ifndef PWM_PHASE_DEMO_TYPES_H
#define PWM_PHASE_DEMO_TYPES_H

#include "std_includes.h"
#include "pwm_phase_demo_const.h"


#define PWM_PHASE_DEMO_COMMON_VARIABLES                \
    float signal_amplitude;                            \
    float signal_offset;                               \
    float signal_frequency;                            \
    uint32_t signal_phase_ms;                          \
    uint8_t pwm_num;                                   \
    char* name;                                        \
    uint8_t num;                                       \
    bool valid;

typedef struct {
    PWM_PHASE_DEMO_COMMON_VARIABLES
}PwmPhaseDemoConfig_t;

typedef struct {
    PWM_PHASE_DEMO_COMMON_VARIABLES
    bool init;
    uint32_t spin;
}PwmPhaseDemoHandle_t;


#endif /* PWM_PHASE_DEMO_TYPES_H */
