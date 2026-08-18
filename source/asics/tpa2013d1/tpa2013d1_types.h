#ifndef TPA2013D1_TYPES_H
#define TPA2013D1_TYPES_H

#include <stdbool.h>
#include <stdint.h>

#include "tpa2013d1_const.h"
#include "gpio_types.h"

#define TPA2013_COMMON_VAR \
    Pad_t enable;    \
    Pad_t boost;

typedef struct{
	TPA2013_COMMON_VAR
	GpioLogicLevel_t def_enable; /*Shutdown terminal for the Class D Amplifier*/
	GpioLogicLevel_t def_boost; /*Shutdown terminal for the Boost Converter*/
}Tpa2013Config_t;

typedef struct{
	TPA2013_COMMON_VAR
	GpioLogicLevel_t enable_ll; /*Shutdown terminal for the Class D Amplifier*/
	GpioLogicLevel_t boost_ll; /*Shutdown terminal for the Boost Converter*/
	bool init;
}Tpa2013Item_t;

#endif /* TPA2013D1_TYPES_H */
