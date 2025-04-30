#ifndef INDICATION_H
#define INDICATION_H

#include <stdbool.h>
#include <stdint.h>

#include "indication_types.h"

#ifndef HAS_SYSTEM
#error "+HAS_SYSTEM"
#endif

#ifndef HAS_INDICATION
#error "+HAS_INDICATION"
#endif

#ifndef HAS_LED
#error "+ HAS_LED"
#endif

bool indication_init(void);
bool indication_alarm(uint8_t led_num);

#endif /* INDICATION_H  */
