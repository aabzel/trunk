#ifndef INDICATION_TYPES_H
#define INDICATION_TYPES_H

#include <std_includes.h>

#include "sys_constants.h"
#include "led_general_const.h"

#ifdef HAS_LED_RGB
#include "led_rgb_const.h"
#endif

#ifndef HAS_SYSTEM
#error "+HAS_SYSTEM"
#endif

#ifndef HAS_LED
#error "+HAS_LED"
#endif

typedef struct {
	BuildType_t fw_type;
	double freq;
	uint8_t duty;
	Color_t color;
}Intication_t;

#endif /* INDICATION_TYPES_H  */
