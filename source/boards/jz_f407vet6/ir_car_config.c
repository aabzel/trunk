#include "ir_car_config.h"

#include "data_utils.h"

const IrCarConfig_t IrCarConfig[] = {
    {
        .num = 1,
        .valid = true,
        .ir_samsung_num = 1,
        .motor_trottle_num = 1,
        .motor_steering_num = 2,
        .gear = 50.0,
        .name = "IR_CAR1",
    },
};

IrCarHandle_t IrCarInstance[] = {
    {
        .num = 1,
        .valid = true,
    },
};

COMPONENT_GET_CNT(IrCar, ir_car)


