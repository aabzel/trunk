#ifndef DRV8870_TYPES_H
#define DRV8870_TYPES_H

#include "std_includes.h"
#include "drv8870_const.h"

#define DRV8870_COMMON_VARIABLES                               \
    char* name;                                                \
    float duty;                                       \
    float pwm_frequency_hz;                                    \
    uint8_t num;                                               \
    uint8_t in1_pwm_num;                                       \
    uint8_t in2_pwm_num;                                       \
    bool valid;

typedef struct {
    DRV8870_COMMON_VARIABLES
}Drv8870Config_t;

typedef struct {
    DRV8870_COMMON_VARIABLES
    bool init;
    Drv8870Mode_t mode;
    uint32_t spin;
}Drv8870Handle_t;


#endif /* DRV8870_TYPES_H */
