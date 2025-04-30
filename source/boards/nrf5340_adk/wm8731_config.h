
#ifndef WM8731_CONFIG_H
#define WM8731_CONFIG_H

#include <stdbool.h>
#include <stdint.h>

#include "wm8731_types.h"

#ifndef HAS_WM8731
#error "+HAS_WM8731"
#endif


#define WM8731_I2C_NUM 1
#define WM8731_I2S_NUM 0

extern const Wm8731RegConfig_t Wm8731RegConfigLut[];
extern Wm8731RegConfig_t Wm8731RegConfig[];

uint32_t wm8731_get_config_cnt(void);

#endif /* WM8731_CONFIG_H */
