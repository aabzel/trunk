#ifndef K1948BK018_H
#define K1948BK018_H

#include "k1948bk018_const.h"
#include "mcu32_memory_map.h"

#ifdef HAS_DIAG
#include "k1948bk018_diag.h"
#endif

#ifdef HAS_GPIO
#include "gpio_types.h"
#endif


bool mik32_launch_eeprom(void);


#endif /* K1948BK018_H */
