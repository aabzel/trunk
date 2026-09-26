#ifndef WM8731_CONFIG_H
#define WM8731_CONFIG_H


#include "std_includes.h"
#include "wm8731_types.h"

#ifndef HAS_WM8731
#error "+HAS_WM8731"
#endif

#ifndef HAS_I2C
#error "+HAS_I2C"
#endif

#ifndef HAS_I2S
#warning "+HAS_I2S"
#endif

#define WM8731_I2C_NUM 2
#define WM8731_I2S_NUM 2

extern const Wm8731Config_t Wm8731Config[];
extern Wm8731Handle_t Wm8731Instance[];

extern const Wm8731RegConfig_t Wm8731RegisterConfiguration[];

uint32_t wm8731_get_config_cnt(void);
uint32_t wm8731_get_cnt(void);

#endif /* WM8731_CONFIG_H */
