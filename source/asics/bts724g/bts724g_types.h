#ifndef BTS724G_TYPES_H
#define BTS724G_TYPES_H

#include "std_includes.h"
#include "bts724g_const.h"
#include "gpio_types.h"
#include "control_const.h"
#include "pwm_types.h"

#define BTS724G_COMMON_GPIO_VARIABLES       \
    Pad_t pad_diag;                         \
    Pad_t pad_set;                          \
    Pad_t pad_feedback;

#define BTS724G_COMMON_VARIABLES            \
    PWM_SIGNAL_VARIABLES                    \
    BTS724G_COMMON_GPIO_VARIABLES           \
    Bts724gPinMode_t mode;                  \
    Bts724gFeedBackMode_t feedback_mode;    \
    ControlMode_t ctrl_mode;                \
    float feedback_scaler;                  \
    bool valid;                             \
    char* con_name;                         \
    char* name;                             \
    uint8_t num;                            \
    uint8_t chip_id;                        \
    uint8_t opposite_num;                   \
    uint8_t pwm_num;                        \
    uint8_t shared_num;                     

typedef struct {
    BTS724G_COMMON_VARIABLES
}Bts724gConfig_t;

typedef struct {
    BTS724G_COMMON_VARIABLES
    bool init;
    uint32_t spin;
    uint32_t rest_duration_ms;
    uint32_t duration_ms;
    uint32_t error_cnt;
    GpioLogicLevel_t prev_pad_diag_ll;
}Bts724gHandle_t;


#endif /* BTS724G_TYPES_H */
