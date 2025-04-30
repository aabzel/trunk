#ifndef PWM_NRFX_TYPES_H
#define PWM_NRFX_TYPES_H

#include <stdbool.h>
#include <stdint.h>

#include "nrf_pwm.h"
#include "nrfx_pwm.h"
#include "pwm_custom_const.h"

#define PWM_CUSTON_VARIABLES       \
    uint16_t count_period;         \
    uint16_t comparator15bit;      \
    nrf_pwm_sequence_t sequence;   \
    nrfx_pwm_t h_pwm;


typedef struct{
    uint8_t num;
    nrfx_pwm_handler_t handler;
    NRF_PWM_Type* registers;
    uint8_t drv_inst_idx;
    bool valid;
}PwmStaticInfo_t;

#endif /* PWM_NRFX_TYPES_H  */
