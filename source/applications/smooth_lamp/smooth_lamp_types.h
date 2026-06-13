#ifndef SMOOTH_LAMP_TYPES_H
#define SMOOTH_LAMP_TYPES_H

#include "std_includes.h"
#include "smooth_lamp_const.h"

#ifdef HAS_SMOOTH_LAMP_CUSTOM
#include "smooth_lamp_custom_types.h"
#else
#define SMOOTH_LAMP_CUSTOM_VARIABLES
#endif

//    float mult;

#define SMOOTH_LAMP_COMMON_VARIABLES                  \
    char* name;                                       \
    uint8_t pid_num;                                  \
    uint8_t num;                                      \
    float logistic_shift_s;                           \
    float pwm_freq_hz;                                \
    float sample_rate_hz;                             \
    float scale;                                      \
    float limit_up;                                   \
    float limit_down;                                 \
    uint8_t delta_sigma_num;                          \
    uint8_t type_num;                                 \
    SmoothLampCmd_t cmd;                              \
    SmoothLampType_t lamp_type;                       \
    bool valid;

typedef struct {
    SMOOTH_LAMP_COMMON_VARIABLES
}SmoothLampConfig_t;

typedef struct {
    SMOOTH_LAMP_COMMON_VARIABLES
    SMOOTH_LAMP_CUSTOM_VARIABLES
    bool init;
    float scale_real;
    float off_time_s;
    float on_time_s;
    //float signal_in;
    float signal_out;
    uint8_t state;
    uint64_t up_time_us;
    uint64_t start_up_time_us;
    uint32_t spin;
}SmoothLampHandle_t;


#endif /* SMOOTH_LAMP_TYPES_H */
