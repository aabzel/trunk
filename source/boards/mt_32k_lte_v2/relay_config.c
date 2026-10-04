#include "relay_config.h"

#include "data_utils.h"
#include "pwm_config.h"


#ifdef HAS_UART1_HW_HOT_FIX
#define RELAY_CONFIG_OUT2_3_PWM_PIN
#define RELAY_CONFIG_OUT2_4_PWM_PIN
#else

#define RELAY_CONFIG_OUT2_3_PWM_PIN                               \
    {                                                             \
     .active = GPIO_LVL_HI,                                       \
     .name = "OUT24_2_3",                                         \
     .con_name="XP3.4",                                           \
     .pwm_num = PWM_NUM_OUT2_3,                                   \
     .num = RELAY_NUM_OUT2_3,                                     \
     .mode = RELAY_MODE_OFF,                                      \
     .duty = 50.0f,                                               \
     .frequency_hz = 1000.0f,                                     \
     .ctrl_mode = CONTROL_MODE_PWM,                               \
     .pad_set = {.port = PORT_A, .pin = 9,},    /* OUT2_3  */     \
     .pad_get = {.port = PORT_C, .pin = 9,},  /*"DIAG2_3/4" */    \
     .valid = true,  },

#define RELAY_CONFIG_OUT2_4_PWM_PIN                             \
    {                                                           \
     .active = GPIO_LVL_HI,                                     \
     .name = "OUT24_2_4",                                       \
     .con_name="XP3.12",                                        \
     .pwm_num = PWM_NUM_OUT2_4,                                 \
     .num = RELAY_NUM_OUT2_4,                                   \
     .mode = RELAY_MODE_OFF,                                    \
     .duty = 50.0f,                                             \
     .frequency_hz = 1000.0f,                                   \
     .ctrl_mode = CONTROL_MODE_PWM,                             \
     .pad_set = {.port = PORT_A, .pin = 10,},   /* OUT2_4  */   \
     .pad_get = {.port = PORT_C, .pin = 9,},  /*"DIAG2_3/4" */  \
     .valid = true,  },

#endif

const RelayConfig_t RelayConfig[] = {
    {.name = "OUT24_1_1",  .num=RELAY_NUM_OUT1_1,  .mode=RELAY_MODE_OFF, .duty=50.0f, .pad_set={.port=PORT_D, .pin=5,},   .pad_get={.port=PORT_D, .pin=4,},  .valid=true,  .active=GPIO_LVL_HI,},
    {.name = "OUT24_1_2",  .num=RELAY_NUM_OUT1_2,  .mode=RELAY_MODE_OFF, .duty=50.0f, .pad_set={.port=PORT_D, .pin=3,},   .pad_get={.port=PORT_D, .pin=4,},  .valid=true,  .active=GPIO_LVL_HI,},
    {.name = "OUT24_1_3",  .num=RELAY_NUM_OUT1_3,  .mode=RELAY_MODE_OFF, .duty=50.0f, .pad_set={.port=PORT_D, .pin=2,},   .pad_get={.port=PORT_D, .pin=1,},  .valid=true,  .active=GPIO_LVL_HI,},
    {.name = "OUT24_1_4",  .num=RELAY_NUM_OUT1_4,  .mode=RELAY_MODE_OFF, .duty=50.0f, .pad_set={.port=PORT_D, .pin=0,},   .pad_get={.port=PORT_D, .pin=1,}, .valid=true,  .active=GPIO_LVL_HI,},

    {.name = "OUT24_2_1",  .num=RELAY_NUM_OUT2_1,  .mode=RELAY_MODE_OFF, .duty=50.0f, .pad_set={.port=PORT_C,  .pin=7,},   .pad_get={.port=PORT_C, .pin=8,}, .valid=true,  .active=GPIO_LVL_HI,},
    {.name = "OUT24_2_2",  .num=RELAY_NUM_OUT2_2,  .mode=RELAY_MODE_OFF, .duty=50.0f, .pad_set={.port=PORT_A, .pin=8,},   .pad_get={.port=PORT_C, .pin=8,}, .valid=true,  .active=GPIO_LVL_HI,},
    RELAY_CONFIG_OUT2_3_PWM_PIN
    RELAY_CONFIG_OUT2_4_PWM_PIN
    {.name = "OUT24_3_1",  .num=RELAY_NUM_OUT3_1,  .mode=RELAY_MODE_OFF, .duty=0.0f,  .pad_set={.port=PORT_C, .pin=6,},   .pad_get={.port=PORT_D, .pin=15,}, .valid=true,  .active=GPIO_LVL_HI,},
    {.name = "OUT24_3_2",  .num=RELAY_NUM_OUT3_2,  .mode=RELAY_MODE_OFF, .duty=0.0f,  .pad_set={.port=PORT_D, .pin=14,},  .pad_get={.port=PORT_D, .pin=15,},  .valid=true,  .active=GPIO_LVL_HI,},
    {.name = "OUT24_3_3",  .num=RELAY_NUM_OUT3_3,  .mode=RELAY_MODE_OFF, .duty=50.0f, .pad_set={.port=PORT_D, .pin=13,},  .pad_get={.port=PORT_D, .pin=12,}, .valid=true,  .active=GPIO_LVL_HI,},
    {.name = "OUT24_3_4",  .num=RELAY_NUM_OUT3_4,  .mode=RELAY_MODE_OFF, .duty=0.0f,  .pad_set={.port=PORT_D, .pin=11,},  .pad_get={.port=PORT_D, .pin=12,},  .valid=true,  .active=GPIO_LVL_HI,},

    {.name = "OUT24_4_1",  .num=RELAY_NUM_OUT4_1,  .mode=RELAY_MODE_OFF, .duty=0.0f,  .pad_set={.port=PORT_D, .pin=10,},  .pad_get={.port=PORT_D, .pin=9,},  .valid=true,  .active=GPIO_LVL_HI,},
    {.name = "OUT24_4_2",  .num=RELAY_NUM_OUT4_2,  .mode=RELAY_MODE_OFF, .duty=0.0f,  .pad_set={.port=PORT_D, .pin=8,},   .pad_get={.port=PORT_D, .pin=9,},  .valid=true,  .active=GPIO_LVL_HI,},
    {.name = "OUT24_4_3",  .num=RELAY_NUM_OUT4_3,  .mode=RELAY_MODE_OFF, .duty=0.0f,  .pad_set={.port=PORT_B, .pin=15,},  .pad_get={.port=PORT_D, .pin=6,},  .valid=true,  .active=GPIO_LVL_HI,},
    {.name = "OUT24_4_4",  .num=RELAY_NUM_OUT4_4,  .mode=RELAY_MODE_OFF, .duty=0.0f,  .pad_set={.port=PORT_D, .pin=7,},   .pad_get={.port=PORT_D, .pin=6,},  .valid=true,  .active=GPIO_LVL_HI,},
};

RelayHandle_t RelayInstance[] = {
    {.num=RELAY_NUM_OUT1_1, .valid=true, },
    {.num=RELAY_NUM_OUT1_2, .valid=true, },
    {.num=RELAY_NUM_OUT1_3, .valid=true, },
    {.num=RELAY_NUM_OUT1_4, .valid=true, },

    {.num=RELAY_NUM_OUT2_1, .valid=true, },
    {.num=RELAY_NUM_OUT2_2, .valid=true, },

#ifndef HAS_UART1_HW_HOT_FIX
    {.num=RELAY_NUM_OUT2_3, .valid=true, },
    {.num=RELAY_NUM_OUT2_4, .valid=true, },
#endif

    {.num=RELAY_NUM_OUT3_1, .valid=true, },
    {.num=RELAY_NUM_OUT3_2, .valid=true, },
    {.num=RELAY_NUM_OUT3_3, .valid=true, },
    {.num=RELAY_NUM_OUT3_4, .valid=true, },

    {.num=RELAY_NUM_OUT4_1, .valid=true, },
    {.num=RELAY_NUM_OUT4_2, .valid=true, },
    {.num=RELAY_NUM_OUT4_3, .valid=true, },
    {.num=RELAY_NUM_OUT4_4, .valid=true, },

};


COMPONENT_GET_CNT(Relay, relay)
