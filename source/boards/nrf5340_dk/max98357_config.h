#ifndef MAX98357_CONFIG_GENERAL_H
#define MAX98357_CONFIG_GENERAL_H

#include <stdbool.h>
#include <stdint.h>

#include "max98357_types.h"

#ifndef HAS_MAX98357
#error "+ HAS_MAX98357"
#endif

#ifndef HAS_GPIO
#error "+ HAS_GPIO"
#endif

#ifndef HAS_MCU
#error "+ HAS_MCU"
#endif

extern Max98357Config_t Max98357Config[];
extern Max98357Handle_t Max98357Instance[];

uint32_t max98357_get_cnt(void);

#endif /* MAX98357_CONFIG_GENERAL_H  */
