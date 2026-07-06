#ifndef BUTTON_CONFIG_H
#define BUTTON_CONFIG_H

#include "std_includes.h"
#include "button_types.h"

#ifndef HAS_BUTTON
#error "Add HAS_BUTTON"
#endif

#define BUTTON_COUNT 1

extern const ButtonConfig_t ButtonConfig[];
extern ButtonHandle_t ButtonInstance[];

uint32_t button_get_cnt(void);

#endif /* BUTTON_CONFIG_H  */
