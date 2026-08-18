
#ifndef SI4737_CONFIG_H
#define SI4737_CONFIG_H

#include <stdbool.h>
#include <stdint.h>

#include "gpio_bsp.h"
#include "si4737_types.h"

#define SI4737_MAIN 1

#define PAD_SI4737_RST 0x40

extern const Si4737Config_t Si4737Config;
extern Si4737Handler_t Si4737Handler;

#endif /* SI4737_CONFIG_H */
