#ifndef AUTO_BRIGHTNESS_TYPES_H
#define AUTO_BRIGHTNESS_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#include "auto_brightness_const.h"
#ifdef HAS_PWM
#include "pwm_types.h"
#define PWM_VALIABLES   PwmChannel_t channel;
#else
#define PWM_VALIABLES
#endif

#define AUTO_BRIGHTNESS_COMMON_VAR    \
    bool binary;                      \
    uint8_t num;                      \
    uint8_t pwm_num;                  \
    uint8_t led_num;                  \
    uint8_t dist_num;                 \
    uint8_t schmitt_trigger_num;      \
    uint32_t pwm_freq_hz;             \
    PWM_VALIABLES                     \
    bool valid;

typedef struct {
    AUTO_BRIGHTNESS_COMMON_VAR
    char* name;
} AutoBrightnessConfig_t;

typedef struct {
    AUTO_BRIGHTNESS_COMMON_VAR
    bool init;
    uint32_t err_cnt;
    bool on;
    double distance_m;
    double duty_cycle; /* % */
} AutoBrightnessHandle_t;

#ifdef __cplusplus
}
#endif

#endif /* AUTO_BRIGHTNESS_TYPES_H */
