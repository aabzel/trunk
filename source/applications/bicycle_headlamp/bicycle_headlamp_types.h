#ifndef BICYCLE_HEADLAMP_TYPES_H
#define BICYCLE_HEADLAMP_TYPES_H

#include "std_includes.h"
#include "bicycle_headlamp_const.h"

#define BICYCLE_HEADLAMP_COMMON_VARIABLES              \
    char* name;                                        \
    float mult;                                        \
    float limit_down;                                  \
    float limit_up;                                    \
    uint8_t ir_samsung_num;                            \
    uint8_t smooth_lamp_num;                           \
    uint8_t num;                                       \
    bool valid;

typedef struct {
    BICYCLE_HEADLAMP_COMMON_VARIABLES
}BicycleHeadLampConfig_t;

typedef struct {
    BICYCLE_HEADLAMP_COMMON_VARIABLES
    bool init;
    uint32_t cmd_start_ms;
    uint32_t spin;
}BicycleHeadLampHandle_t;


#endif /* BICYCLE_HEADLAMP_TYPES_H */
