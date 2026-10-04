#include "drv8870_config.h"

#include "data_utils.h"

const Drv8870Config_t Drv8870Config[] = {
#ifdef HAS_DRV8870_1
    {
        .num = 1,
        .valid = true,
        .duty = 50.0,
        .in1_pwm_num = 2,
        .in2_pwm_num = 3,
        .pwm_frequency_hz = 100.0,
        .name = "DRV88701_Trottle",
    },
#endif

#ifdef HAS_DRV8870_2
    {
        .num = 2,
        .valid = true,
        .duty = 10.0,
        .in1_pwm_num = 4,
        .in2_pwm_num = 5,
        .pwm_frequency_hz = 100.0,
        .name = "DRV88702_steering",
    },
#endif
};


Drv8870Handle_t Drv8870Instance[] = {
#ifdef HAS_DRV8870_1
    {
        .num = 1,
        .valid = true,
    },
#endif

#ifdef HAS_DRV8870_2
    {
        .num = 2,
        .valid = true,
    },
#endif

};


COMPONENT_GET_CNT(Drv8870, drv8870)


