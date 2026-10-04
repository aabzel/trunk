#include "i2c_config.h"

#include "data_utils.h"




/*constant compile-time known settings*/
const I2cConfig_t I2cConfig[] = {
#ifdef HAS_I2C1
    { .num=1,
            .clock_speed=100000,
            .name = "I2C1",
            .valid=true,},
#endif

#ifdef HAS_I2C2
    { .num=2,
            .clock_speed=100000,
            .name = "I2C2",
            .valid=true,},
#endif

#ifdef HAS_I2C3
    { .num = 3,
      .clock_speed = 100000,
      .name = "AudioCodec",
      .interrupt_priority = 2,
      .interrupt_on = true,
      .own_addr = 0,
      .valid = true,
      .PadSda = { .port=PORT_H, .pin=8,},
      .PadScl = { .port=PORT_H, .pin=7,},
    },
#endif
};

I2cHandle_t I2cInstance[]={
#ifdef HAS_I2C1
    {.num=1, .valid=true, },
#endif

#ifdef HAS_I2C2
    {.num=2, .valid=true, },
#endif

#ifdef HAS_I2C3
    {.num=3,  .valid=true,},
#endif
};

COMPONENT_GET_CNT(I2c, i2c)
