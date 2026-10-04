#include "led_rgb_config.h"

#include "data_utils.h"

#ifndef HAS_LED_RGB
#error "Add HAS_LED_RGB"
#endif


const LedRgbConfig_t LedRgbConfig[]  =  {
       {.num = 1,
        .Pads = {    .red =   {.port = PORT_E , .pin = 3, },
                     .green = {.port = PORT_E,  .pin = 4, },
                     .blue =  {.port = PORT_E,  .pin = 2, },
              },
        .set_color = COLOR_YELLOW,
        .period_ms = 1000,
        .phase_ms = 0,
        .duty = 50.0f,
        .name = "VD1",
        .mode = LED_MCAL_MODE_PWM,
        .active = GPIO_LVL_LOW,
        .valid = true,
       },
};

LedRgbHandle_t LedRgbInstance[] = {
     {.num = 1,   .valid = true,},
};


COMPONENT_GET_CNT(LedRgb, led_rgb)


