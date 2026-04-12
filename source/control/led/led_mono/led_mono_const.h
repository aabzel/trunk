#ifndef LED_MONO_CONST_H
#define LED_MONO_CONST_H

#include "led_mono_dep.h"
#include "led_general_const.h"

#define LED_MONO_POLL_PERIOD_US 100
#define LED_NAME_SIZE 20

typedef enum{
   LED_PHY_GPIO = 1,
   LED_PHY_PWM = 2,
   LED_PHY_PDM = 3,
   LED_PHY_RELAY = 4,

   LED_PHY_UNDEF = 0,
}LedPhy_t;

#endif /* LED_MONO_CONST_H  */
