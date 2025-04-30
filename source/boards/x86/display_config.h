
#ifndef GRAPHIC_DISPLAY_SIMULATOR_CONFIG_H
#define GRAPHIC_DISPLAY_SIMULATOR_CONFIG_H

#include <stdbool.h>
#include <stdint.h>

#include "display_types.h"

extern const DisplayConfig_t DisplayConfig[];
extern DisplayHandle_t DisplayInstance[];

uint32_t display_get_cnt(void);

#endif /* GRAPHIC_DISPLAY_SIMULATOR_CONFIG_H */
