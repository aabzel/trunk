#ifndef BUTTON_CONFIG_H
#define BUTTON_CONFIG_H

#include <stdbool.h>
#include <stdint.h>

#include "button_types.h"

#ifndef HAS_BUTTON
#error "Add HAS_BUTTON"
#endif /*HAS_BUTTON*/

extern const ButtonConfig_t ButtonConfig[];
extern ButtonHandle_t ButtonInstance[];

uint32_t button_get_cnt(void);

#endif /* BUTTON_CONFIG_H  */
