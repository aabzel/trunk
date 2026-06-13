#ifndef ENCODER_LAMP_TYPES_H
#define ENCODER_LAMP_TYPES_H

#include "std_includes.h"
#include "encoder_lamp_const.h"

#define ENCODER_LAMP_COMMON_VARIABLES                  \
    char* name;                                        \
    float pwm_frequency_hz;                            \
    uint8_t pid_num;                               \
    uint8_t encoder_num;                               \
    uint8_t delta_sigma_num;                           \
    uint8_t pwm_num;                                   \
    uint8_t num;                                       \
    bool valid;

typedef struct {
    ENCODER_LAMP_COMMON_VARIABLES
}EncoderLampConfig_t;

typedef struct {
    ENCODER_LAMP_COMMON_VARIABLES
    bool init;
    int32_t duty;
    int32_t duty_prev;
    uint32_t spin;
}EncoderLampHandle_t;


#endif /* ENCODER_LAMP_TYPES_H */
