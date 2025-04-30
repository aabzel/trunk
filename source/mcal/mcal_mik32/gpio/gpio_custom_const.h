#ifndef GPIO_MIK32_CONST_H
#define GPIO_MIK32_CONST_H

#ifdef __cplusplus
extern "C" {
#endif

//#include "mik32_hal.h"

#define GPIO_PIN_COUNT 15

typedef enum {
    SPEED_LOW_SPEED = 0,
    SPEED_MEDIUM_SPEED = 1,
    SPEED_FAST_SPEED = 2,
    SPEED_HIGH_SPEED = 3,
    SPEED_UNDEF = 4,
} GpioMik32Speed_t;

typedef enum {
    OUT_TYPE_PUSH_PULL = 0,
    OUT_TYPE_OPEN_DRAIN = 1,
    OUT_TYPE_UNDEF = 2,
} OutType_t;


typedef enum {
    PORT_0= 0,
    PORT_1= 1,
    PORT_2= 2,
    PORT_UNDEF = 3,
} Port_t;


#ifdef __cplusplus
}
#endif

#endif /* GPIO_MIK32_CONST_H  */
