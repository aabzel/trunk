#ifndef LED_GENERAL_CONST_H
#define LED_GENERAL_CONST_H

#include "std_includes.h"
#include "led_dep.h"

#ifndef HAS_MICROCONTROLLER
#error "+HAS_MICROCONTROLLER"
#endif

#ifndef HAS_LED
#error "+HAS_LED"
#endif

#define LED_POLL_PERIOD_US 5
#define LED_ALARM_PERIOD_MS 100
#define LED_HEARTBEAT_PERIOD_MS 1000
#define LED_NAME_SIZE 20

typedef enum {
    LED_MCAL_MODE_OFF = 1,
    LED_MCAL_MODE_ON = 2,
    LED_MCAL_MODE_PWM = 3,
    LED_MCAL_MODE_NONE = 4,
    LED_MCAL_MODE_BLINK = 5,
    LED_MCAL_MODE_BAM = 6,
    LED_MCAL_MODE_UNDEF = 0,
} LedMode_t;

/*Do not change constants*/
typedef enum {

    COLOR_BLACK = 8,
    COLOR_RED = 4,
    COLOR_GREEN = 2,
    COLOR_BLUE = 1,
    COLOR_PURPLE = 5,
    COLOR_YELLOW = 6,
    COLOR_CYANIC = 3,
    COLOR_WHITE = 7,

    COLOR_CNT = 9,
    
    COLOR_UNDEF = 0,
} Color_t;

#endif /* LED_GENERAL_CONST_H  */
